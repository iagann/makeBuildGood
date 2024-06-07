#include "BuildMaker.h"
#include "PassiveCombination.h"

#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>

#include <set>
#include <list>


BuildMaker::BuildMaker()
	: num_threads(get_num_threads())
{
	verbose = 1;
	stacks = true;
	reversePassiveSearch = true;
	disableCriticalVulnerability = false;
	allowSameItems = true;

	usedItemsInit = {
		{ HELM, std::set<int>() },
		{ AMULET, std::set<int>() },
		{ BOW, std::set<int>() },
		{ QUIVER, std::set<int>() },
		{ BODY, std::set<int>() },
		{ RING, std::set<int>() },
		{ BELT, std::set<int>() },
		{ GLOVES, std::set<int>() },
		{ BOOTS, std::set<int>() },
		{ RELIC, std::set<int>() },
		{ BIG_IDOL, std::set<int>() },
		{ SMALL_IDOL, std::set<int>() },
		{ BLESSING_BLACK_SUN, std::set<int>() },
		{ BLESSING_REIGN_OF_DRAGONS, std::set<int>() },
		{ BLESSING_SPIRITS_OF_FIRE, std::set<int>() },
		{ BLESSING_THE_AGE_OF_WINTER, std::set<int>() },
		{ BLESSING_ENDING_THE_STORM, std::set<int>() },
	};

	init();
}

void BuildMaker::makeGoodBuild() {
	using std::chrono::high_resolution_clock;
	using std::chrono::duration_cast;
	using std::chrono::duration;
	using std::chrono::milliseconds;
	auto t1 = high_resolution_clock::now();

	passivePoints = (realPassives == PassiveCombination<PASSIVE_NAME>()) ? 113 : realPassives.totalPoints();

	// literally anything
	{
		std::cout << "Generating initial build to start with" << std::endl;
		currentItemSet.clear();
		/*
		currentItemSet.addItem(HELM_SLOT, items.getItem(HELM_SLOT));
		currentItemSet.addItem(AMULET_SLOT, items.getItem(AMULET_SLOT));
		currentItemSet.addItem(BOW_SLOT, items.getItem(BOW_SLOT));
		currentItemSet.addItem(QUIVER_SLOT, items.getItem(QUIVER_SLOT));
		currentItemSet.addItem(BODY_SLOT, items.getItem(BODY_SLOT));
		currentItemSet.addItem(RING_LEFT_SLOT, items.getItem(RING_LEFT_SLOT));
		currentItemSet.addItem(RING_RIGHT_SLOT, items.getItem(RING_RIGHT_SLOT));
		currentItemSet.addItem(BELT_SLOT, items.getItem(BELT_SLOT));
		currentItemSet.addItem(GLOVES_SLOT, items.getItem(GLOVES_SLOT));
		currentItemSet.addItem(BOOTS_SLOT, items.getItem(BOOTS_SLOT));
		currentItemSet.addItem(RELIC_SLOT, items.getItem(RELIC_SLOT));
		currentItemSet.addItem(BIG_IDOL_1_SLOT, items.getItem(BIG_IDOL_1_SLOT));
		currentItemSet.addItem(BIG_IDOL_2_SLOT, items.getItem(BIG_IDOL_2_SLOT));
		currentItemSet.addItem(BIG_IDOL_3_SLOT, items.getItem(BIG_IDOL_3_SLOT));
		currentItemSet.addItem(BIG_IDOL_4_SLOT, items.getItem(BIG_IDOL_4_SLOT));
		currentItemSet.addItem(SMALL_IDOL_1_SLOT, items.getItem(SMALL_IDOL_1_SLOT));
		currentItemSet.addItem(SMALL_IDOL_2_SLOT, items.getItem(SMALL_IDOL_2_SLOT));
		currentItemSet.addItem(SMALL_IDOL_3_SLOT, items.getItem(SMALL_IDOL_3_SLOT));
		currentItemSet.addItem(SMALL_IDOL_4_SLOT, items.getItem(SMALL_IDOL_4_SLOT));
		currentItemSet.addItem(BLESSING_BLACK_SUN_SLOT, items.getItem(BLESSING_BLACK_SUN_SLOT));
		currentItemSet.addItem(BLESSING_REIGN_OF_DRAGONS_SLOT, items.getItem(BLESSING_REIGN_OF_DRAGONS_SLOT));
		currentItemSet.addItem(BLESSING_SPIRITS_OF_FIRE_SLOT, items.getItem(BLESSING_SPIRITS_OF_FIRE_SLOT));
		currentItemSet.addItem(BLESSING_THE_AGE_OF_WINTER_SLOT, items.getItem(BLESSING_THE_AGE_OF_WINTER_SLOT));
		currentItemSet.addItem(BLESSING_ENDING_THE_STORM_SLOT, items.getItem(BLESSING_ENDING_THE_STORM_SLOT));
		*/
		bool isKestrel = currentItemSet.getAllStats().count(STAT_NAME::LEVEL_OF_BALLISTA) > 0 ? 25 : 24;
		currentSkills = isKestrel ? *skillSetKestrel.begin() : *skillSet.begin();

		bestItemSet = currentItemSet;
		bestSkills = currentSkills;
		bestPassives = minimumPassives;
	}
	double prevDps = 0;
	//findBestPassives();
	//findBestSkills();
	currentDps = calculateDpsIf(currentItemSet);
	if (verbose >= 1) std::cout << "Current DPS: " << currentDps << std::endl;
	bestDps = currentDps;
	int iteration = 1;
	while (prevDps < bestDps) {
		if (verbose >= 1) std::cout << std::endl << "=========================== FINDING BEST BUILD, iteration " << iteration++ << "===========================" << std::endl;
		prevDps = bestDps;
		findBestItems();
	}
	if (verbose >= 1) std::cout << std::endl << "NO POSSIBLE CHANGES FOR DPS INCREASE" << std::endl;
	
	std::cout << std::endl << "CALCULATION OF ITEM DPS CONTRIBUTION" << std::endl;
	std::map<Item, double> dpsWithout;
	std::map<Item, std::map<Item, double>> dpsCompare;
	auto bestItemSetCopy = bestItemSet;
	auto bestPassivesCopy = bestPassives;
	bool wasAllowingSameItems = allowSameItems;
	allowSameItems = true;
	for (auto item : bestItemSet.getAllItemSet()) {
		/*if (item.first != SMALL_IDOL_1_SLOT)
			continue;*/
		bestItemSet = bestItemSetCopy;
		if (!bestItemSet.hasItem(item.first))
			continue;
		ItemSet withoutSet = bestItemSet;
		Item withoutItem = withoutSet.getItem(item.first);
		withoutSet.unequipItem(item.first);
		currentItemSet = withoutSet;

		auto dps1 = calculateDpsIf(bestPassives);
		dpsWithout.insert(std::make_pair(withoutItem, dps1));

		
		dpsCompare.insert(std::make_pair(withoutItem, std::map<Item, double>()));
		for (auto comparedItem : items.getItems(item.first)) {
			if (comparedItem == withoutItem)
				continue;
			currentItemSet = bestItemSet;
			auto dps = calculateDpsIf(bestPassives);
			bestItemSet = bestItemSetCopy;
			ItemSet comparedSet = bestItemSet;
			comparedSet.changeItem(item.first, comparedItem);
			currentItemSet = comparedSet;
			auto dps2 = calculateDpsIf(bestPassives);
			if (dps2 < dps)
				dpsCompare.at(withoutItem).insert(std::make_pair(comparedItem, dps / dps2));
		}
	}
	allowSameItems = wasAllowingSameItems;
	currentItemSet = bestItemSetCopy;
	//bestItemSet = bestItemSetCopy;
	findBestPassives();
	
	std::cout << std::endl << "BEST BUILD:" << std::endl;
	for (auto item : bestItemSet.getAllItems()) {
		std::cout << item.toString() << std::endl;
		//std::cout << "\t-" << (1 - dpsWithout.at(item) / bestDps) * 100 << "% if deequip - " << item.toString() << std::endl;
		//std::cout << item.toString() << std::endl;
		for (auto comparedItem : dpsCompare.at(item)) {
			if (comparedItem.second < bestDps)
				std::cout << "\t" << (1 - comparedItem.second) * 100 << "% if change - " << comparedItem.first.toString() << std::endl;
		}
	}

	std::cout << std::endl;
	printPassiveCombination(STRINGS::SKILL_PASSIVE_NAME_MAP, bestSkills);

	std::cout << std::endl;
	printPassiveCombination(STRINGS::PASSIVE_NAME_MAP, bestPassives);
	std::cout << "If passive would change: " << std::endl;
	const auto allPassives = bestPassives.getPassives();
	std::vector<std::tuple<double, PASSIVE_NAME, bool>> passiveChanges;
	for (const auto& passive : allPassives) {
		PassiveCombination<PASSIVE_NAME> changedPassive;
		changedPassive = bestPassives;
		if (passive.second > passives.at(passive.first).getAbsoluteMinimum()) {
			changedPassive.substractPassivePoint(passive.first, passives.at(passive.first).getClass());
			auto dps = calculateDpsIf(changedPassive);
			if (dps != bestDps)
				passiveChanges.push_back(std::make_tuple(dps, passive.first, false));
		}
		if (passive.second < passives.at(passive.first).getMaximumPoints()) {
			changedPassive.addPassivePoint(passive.first, passives.at(passive.first).getClass());
			auto dps = calculateDpsIf(changedPassive);
			if (dps != bestDps)
				passiveChanges.push_back(std::make_tuple(dps, passive.first, true));
		}
	}
	std::sort(passiveChanges.begin(), passiveChanges.end(), [](const auto& a, const auto& b) { return std::get<0>(a) < std::get<0>(b); });
	for (const auto& passiveChange : passiveChanges) {
		auto dps = std::get<0>(passiveChange);
		auto passive = std::get<1>(passiveChange);
		auto passiveCount = allPassives.at(passive);
		auto added = std::get<2>(passiveChange);
		if (added)
			std::cout << "\t+" << (dps / bestDps  - 1) * 100 << "% - "
				<< passiveCount << " -> " << (passiveCount + 1)
				<< " " << STRINGS::PASSIVE_NAME_MAP.at(passive) << std::endl;
		else
			std::cout << "\t-" << (bestDps / dps - 1) * 100 << "% - "
				<< passiveCount << " -> " << (passiveCount - 1)
				<< " " << STRINGS::PASSIVE_NAME_MAP.at(passive) << std::endl;
	}
	
	calculateDpsIf(bestPassives);
	std::cout << std::endl << "DPS: " << bestDps << std::endl;
	std::cout << std::endl << "crit%: " << lastCritChance << std::endl;
	
	// passive recommendations
	if (realPassives != PassiveCombination<PASSIVE_NAME>() && realPassives != bestPassives) {
		auto realDps = calculateDpsIf(realPassives);
		std::cout << "Change passives NOW for more DPS " << realDps << " -> " << bestDps << " +" << (bestDps / realDps - 1) * 100 << "%: " << std::endl;
		for (auto passive : realPassives.getPassives()) {
			if (bestPassives.getPassivePoints(passive.first) != passive.second)
				std::cout << STRINGS::PASSIVE_NAME_MAP.at(passive.first) << ": " << passive.second
				<< " -> " << bestPassives.getPassivePoints(passive.first) << std::endl;
		}
		std::cout << std::endl;
	}

	auto t2 = high_resolution_clock::now();
	duration<double, std::milli> ms_double = t2 - t1;
	std::cout << "Total execution time: " << ms_double.count() << "ms" << std::endl << std::endl;

	std::cout << "Press any key to show detailed DPS calculation" << std::endl;
	system("pause");

	findBestPassives();
	verbose = 2;
	calculateDpsIf(bestPassives);
}

void BuildMaker::init() {
	initPassives();
	initSkills();
}

void BuildMaker::initPassives() {
	// VALUES
	{
		// BASE CLASS
		passives.insert(std::make_pair(
			PASSIVE_NAME::SWIFT_ASSASSIN, Passive<PASSIVE_NAME>(PASSIVE_CLASS_NAME::BASE, 8)
			.withStat(STAT_NAME::FLAT_PHYSICAL_DAMAGE, 1)
		));
		passives.insert(std::make_pair(
			PASSIVE_NAME::STEADY_HAND, Passive<PASSIVE_NAME>(PASSIVE_CLASS_NAME::BASE, 8)
			.withStat(STAT_NAME::DEXTERITY, 1)
		));
		passives.insert(std::make_pair(
			PASSIVE_NAME::GUILE, Passive<PASSIVE_NAME>(PASSIVE_CLASS_NAME::BASE, 1)
		));
		passives.insert(std::make_pair(
			PASSIVE_NAME::EVASION, Passive<PASSIVE_NAME>(PASSIVE_CLASS_NAME::BASE, 1)
			.withMinimumClassPoints(PASSIVE_CLASS_NAME::BASE, 5)
			.withDependency(PASSIVE_NAME::GUILE, 1)
		));
		passives.insert(std::make_pair(
			PASSIVE_NAME::AGILITY, Passive<PASSIVE_NAME>(PASSIVE_CLASS_NAME::BASE, 5)
			.withStat(STAT_NAME::INCREASED_DAMAGE_PER_MOVEMENT_SPEED, 0.2)
			.withMinimumClassPoints(PASSIVE_CLASS_NAME::BASE, 10)
			.withDependency(PASSIVE_NAME::EVASION, 1)
		));
		// BLADEDANCER
		passives.insert(std::make_pair(
			PASSIVE_NAME::CLOAK_OF_SHADOWS, Passive<PASSIVE_NAME>(PASSIVE_CLASS_NAME::BLADEDANCER, 8)
			.withStat(STAT_NAME::DEXTERITY, 1)
			.withMinimumClassPoints(PASSIVE_CLASS_NAME::BASE, 20)
		));
		passives.insert(std::make_pair(
			PASSIVE_NAME::PURSUIT, Passive<PASSIVE_NAME>(PASSIVE_CLASS_NAME::BLADEDANCER, 5)
			.withThresholdStat(5, STAT_NAME::INCREASED_MOVEMENT_SPEED, 8)
			.withMinimumClassPoints(PASSIVE_CLASS_NAME::BASE, 20)
			.withAbsoluteMinimum(5)
		));
		// MARKSMAN
		passives.insert(std::make_pair(
			PASSIVE_NAME::FOCUS_FIRE, Passive<PASSIVE_NAME>(PASSIVE_CLASS_NAME::MARKSMAN, 8)
			.withStat(STAT_NAME::DEXTERITY, 1)
			.withMinimumClassPoints(PASSIVE_CLASS_NAME::BASE, 20)
		));
		passives.insert(std::make_pair(
			PASSIVE_NAME::ASSASSINS_QUIVER, Passive<PASSIVE_NAME>(PASSIVE_CLASS_NAME::MARKSMAN, 5)
			.withStat(STAT_NAME::FLAT_PHYSICAL_DAMAGE, 1)
			.withStat(STAT_NAME::INCREASED_CRITICAL_STRIKE_CHANCE, 8)
			.withMinimumClassPoints(PASSIVE_CLASS_NAME::BASE, 20)
			.withAbsoluteMinimum(1)
		));
		passives.insert(std::make_pair(
			PASSIVE_NAME::MISSILE_MASTERY, Passive<PASSIVE_NAME>(PASSIVE_CLASS_NAME::MARKSMAN, 10)
			.withStat(STAT_NAME::INCREASED_DAMAGE, 5)
			.withStat(STAT_NAME::ARMOUR_SHRED_CHANCE, 5)
			.withMinimumClassPoints(PASSIVE_CLASS_NAME::MARKSMAN, 5)
		));
		passives.insert(std::make_pair(
			PASSIVE_NAME::CONCENTRATION, Passive<PASSIVE_NAME>(PASSIVE_CLASS_NAME::MARKSMAN, 8)
			.withStat(STAT_NAME::INCREASED_DAMAGE, 15)
			.withMinimumClassPoints(PASSIVE_CLASS_NAME::MARKSMAN, 5)
		));
		passives.insert(std::make_pair(
			PASSIVE_NAME::WOUND_MAKER, Passive<PASSIVE_NAME>(PASSIVE_CLASS_NAME::MARKSMAN, 2)
			.withStat(STAT_NAME::CRITICAL_VULNERABILITY_CHANCE, 10)
			.withMinimumClassPoints(PASSIVE_CLASS_NAME::MARKSMAN, 10)
			.withDependency(PASSIVE_NAME::ASSASSINS_QUIVER, 1)
			.withAbsoluteMinimum(2)
		));
		passives.insert(std::make_pair(
			PASSIVE_NAME::HEIGHTENED_SENCES, Passive<PASSIVE_NAME>(PASSIVE_CLASS_NAME::MARKSMAN, 5)
			.withStat(STAT_NAME::CRITICAL_STRIKE_AVOIDANCE, 7)
			.withStat(STAT_NAME::INCREASED_CRITICAL_STRIKE_MULTIPLIER, 5)
			.withMinimumClassPoints(PASSIVE_CLASS_NAME::MARKSMAN, 20)
			.withDependency(PASSIVE_NAME::WOUND_MAKER, 1)
			//.withAbsoluteMinimum(5)
		));
		// FALCONER
		passives.insert(std::make_pair(
			PASSIVE_NAME::HANDLER, Passive<PASSIVE_NAME>(PASSIVE_CLASS_NAME::FALCONER, 8)
			.withStat(STAT_NAME::INCREASED_MINION_DAMAGE, 7)
			.withThresholdStat(5, STAT_NAME::BASE_MINION_CRITICAL_STRIKE_CHANCE, 5)
			.withMinimumClassPoints(PASSIVE_CLASS_NAME::BASE, 20)
			.withAbsoluteMinimum(8)
		));
		passives.insert(std::make_pair(
			PASSIVE_NAME::AGILE_HUNT, Passive<PASSIVE_NAME>(PASSIVE_CLASS_NAME::FALCONER, 8)
			.withStat(STAT_NAME::DEXTERITY, 1)
			.withMinimumClassPoints(PASSIVE_CLASS_NAME::FALCONER, 5)
			.withAbsoluteMinimum(8)
		));
		passives.insert(std::make_pair(
			PASSIVE_NAME::RANGERS_MARK, Passive<PASSIVE_NAME>(PASSIVE_CLASS_NAME::FALCONER, 7)
			.withStat(STAT_NAME::INCREASED_DAMAGE, 6)
			.withMinimumClassPoints(PASSIVE_CLASS_NAME::FALCONER, 10)
			.withAbsoluteMinimum(3)
		));
		passives.insert(std::make_pair(
			PASSIVE_NAME::TACTITIAN, Passive<PASSIVE_NAME>(PASSIVE_CLASS_NAME::FALCONER, 6)
			.withStat(STAT_NAME::FLAT_MINION_PHYSICAL_DAMAGE, 3)
			.withStat(STAT_NAME::FLAT_MINION_PHYSICAL_DAMAGE_FALCON, 3)
			.withMinimumClassPoints(PASSIVE_CLASS_NAME::FALCONER, 15)
			.withDependency(PASSIVE_NAME::HANDLER, 1)
			.withAbsoluteMinimum(6)
		));
		// FALCONER part 2
		passives.insert(std::make_pair(
			PASSIVE_NAME::COORDINATED_FADE, Passive<PASSIVE_NAME>(PASSIVE_CLASS_NAME::FALCONER, 1)
			.withMinimumClassPoints(PASSIVE_CLASS_NAME::FALCONER, 25)
			.withAbsoluteMinimum(1)
		));
		passives.insert(std::make_pair(
			PASSIVE_NAME::EVASION_TACTICS, Passive<PASSIVE_NAME>(PASSIVE_CLASS_NAME::FALCONER, 6)
			.withStat(STAT_NAME::DEXTERITY, 1)
			.withMinimumClassPoints(PASSIVE_CLASS_NAME::FALCONER, 25)
			.withAbsoluteMinimum(4)
		));
		passives.insert(std::make_pair(
			PASSIVE_NAME::INTUITIVE_CONNECTION, Passive<PASSIVE_NAME>(PASSIVE_CLASS_NAME::FALCONER, 1)
			.withMinimumClassPoints(PASSIVE_CLASS_NAME::FALCONER, 30)
			.withAbsoluteMinimum(1)
		));
		passives.insert(std::make_pair(
			PASSIVE_NAME::RELENTLESS_TALONS, Passive<PASSIVE_NAME>(PASSIVE_CLASS_NAME::FALCONER, 5)
			.withStat(STAT_NAME::INCREASED_DAMAGE, 6)
			.withStat(STAT_NAME::INCREASED_MINION_DAMAGE, 6)
			.withMinimumClassPoints(PASSIVE_CLASS_NAME::FALCONER, 30)
			.withDependency(PASSIVE_NAME::EVASION_TACTICS, 1)
			.withAbsoluteMinimum(2)
		));
		passives.insert(std::make_pair(
			PASSIVE_NAME::NEEDLE_LIKE_PRECISION, Passive<PASSIVE_NAME>(PASSIVE_CLASS_NAME::FALCONER, 6)
			.withStat(STAT_NAME::INCREASED_CRITICAL_STRIKE_CHANCE, 6)
			.withStat(STAT_NAME::INCREASED_CRITICAL_STRIKE_MULTIPLIER, 6)
			.withStat(STAT_NAME::INCREASED_MINION_CRITICAL_STRIKE_CHANCE, 6)
			.withStat(STAT_NAME::INCREASED_MINION_CRITICAL_STRIKE_MULTIPLIER, 6)
			.withMinimumClassPoints(PASSIVE_CLASS_NAME::FALCONER, 35)
			.withAbsoluteMinimum(2)
		));
		passives.insert(std::make_pair(
			PASSIVE_NAME::EXPEDIENCY, Passive<PASSIVE_NAME>(PASSIVE_CLASS_NAME::FALCONER, 5)
			.withMinimumClassPoints(PASSIVE_CLASS_NAME::FALCONER, 40)
			.withAbsoluteMinimum(5)
		));
		passives.insert(std::make_pair(
			PASSIVE_NAME::FINESSE_THEM, Passive<PASSIVE_NAME>(PASSIVE_CLASS_NAME::FALCONER, 7)
			.withStat(STAT_NAME::CRITICAL_STRIKE_AVOIDANCE, 5)
			.withThresholdStat(5, STAT_NAME::INCREASED_MINION_CRITICAL_STRIKE_MULTIPLIER_PER_CRITICAL_STRIKE_AVOIDANCE, 1.5)
			.withMinimumClassPoints(PASSIVE_CLASS_NAME::FALCONER, 40)
			.withDependency(PASSIVE_NAME::NEEDLE_LIKE_PRECISION, 2)
			.withAbsoluteMinimum(5)
		));
		passives.insert(std::make_pair(
			PASSIVE_NAME::TAILWIND, Passive<PASSIVE_NAME>(PASSIVE_CLASS_NAME::FALCONER, 6)
			.withStat(STAT_NAME::INCREASED_MOVEMENT_SPEED, 2)
			.withMinimumClassPoints(PASSIVE_CLASS_NAME::FALCONER, 40)
			.withAbsoluteMinimum(6)
		));
	}

	if (reversePassiveSearch) {
		minimumPassives = PassiveCombination<PASSIVE_NAME>();
		for (auto passive : passives) {
			minimumPassives.setPassivePoints(passive.first, passive.second.getClass(), passive.second.getMaximumPoints());
		}
	}
	else {
		minimumPassives = calculatePassiveMinimums();
	}
}

void BuildMaker::initSkills() {
	//BASE
	{
		skills.insert(std::make_pair(
			SKILL_PASSIVE_NAME::BASE_SKILL, Passive<SKILL_PASSIVE_NAME>(PASSIVE_CLASS_NAME::BASE, 1)
			.withStat(STAT_NAME::FLAT_MINION_PHYSICAL_DAMAGE, 20) // actual is 40, but effectiveness is 40
			.withStat(STAT_NAME::BASE_MINION_CRITICAL_STRIKE_CHANCE, 5)
			.withStat(STAT_NAME::INCREASED_MINION_CRITICAL_STRIKE_MULTIPLIER, 200)
			.withStat(STAT_NAME::INCREASED_MINION_DAMAGE_PER_DEXTERITY, 4)
			.withStat(STAT_NAME::INCREASED_ATTACK_SPEED_PER_DEXTERITY, 1)
			.withStat(STAT_NAME::MORE_DAMAGE, 50)
			.withStat(STAT_NAME::INCREASED_ATTACK_SPEED, 20)
			// base character stats, easier to add here, hehehe
			.withStat(STAT_NAME::DEXTERITY, 16)
			.withStat(STAT_NAME::INTELLIGENCE, 1)
			// Aerial Assauilt
			.withStat(STAT_NAME::MORE_DAMAGE_PER_INTELLIGENCE, 2)
			.withStat(STAT_NAME::INCREASED_ATTACK_SPEED, 75)
			.withStat(STAT_NAME::DEXTERITY, 16)
			// haste
			.withStat(STAT_NAME::INCREASED_MOVEMENT_SPEED, 30*1.2)
			.withAbsoluteMinimum(1)
		));

		skills.insert(std::make_pair(
			SKILL_PASSIVE_NAME::SHARED_ENHANCEMENTS, Passive<SKILL_PASSIVE_NAME>(PASSIVE_CLASS_NAME::BASE, 3)
			.withStat(STAT_NAME::DAMAGE_STAT_RATIO, 25)
			.withAbsoluteMinimum(3)
		));
		skills.insert(std::make_pair(
			SKILL_PASSIVE_NAME::AGILE_ENGENEERING, Passive<SKILL_PASSIVE_NAME>(PASSIVE_CLASS_NAME::BASE, 1)
			.withStat(STAT_NAME::INCREASED_ATTACK_SPEED_PER_DEXTERITY, 0.2)
			.withAbsoluteMinimum(1)
		));
		skills.insert(std::make_pair(
			SKILL_PASSIVE_NAME::AGILE_ENGENEERING, Passive<SKILL_PASSIVE_NAME>(PASSIVE_CLASS_NAME::BASE, 1)
			.withStat(STAT_NAME::INCREASED_ATTACK_SPEED_PER_DEXTERITY, 0.2)
			.withAbsoluteMinimum(1)
		));
		skills.insert(std::make_pair(
			SKILL_PASSIVE_NAME::EFFICIENT_CONSTRUCTION, Passive<SKILL_PASSIVE_NAME>(PASSIVE_CLASS_NAME::BASE, 2)
			.withAbsoluteMinimum(2)
		));
		skills.insert(std::make_pair(
			SKILL_PASSIVE_NAME::PRACTICAL_BUILD, Passive<SKILL_PASSIVE_NAME>(PASSIVE_CLASS_NAME::BASE, 1)
			.withDependency(SKILL_PASSIVE_NAME::EFFICIENT_CONSTRUCTION, 2)
			.withAbsoluteMinimum(1)
		));
		skills.insert(std::make_pair(
			SKILL_PASSIVE_NAME::HEAVY_BOLTS, Passive<SKILL_PASSIVE_NAME>(PASSIVE_CLASS_NAME::BASE, 3)
			.withStat(STAT_NAME::MORE_DAMAGE, 12)
			.withStat(STAT_NAME::MORE_ATTACK_SPEED, -5)
		));
		skills.insert(std::make_pair(
			SKILL_PASSIVE_NAME::LIGHT_BOLTS, Passive<SKILL_PASSIVE_NAME>(PASSIVE_CLASS_NAME::BASE, 3)
			.withDependency(SKILL_PASSIVE_NAME::EFFICIENT_CONSTRUCTION, 1)
			.withStat(STAT_NAME::MORE_ATTACK_SPEED, 12)
			.withStat(STAT_NAME::MORE_DAMAGE, -5)
			.withAbsoluteMinimum(1)
		));
		skills.insert(std::make_pair(
			SKILL_PASSIVE_NAME::SHARPENED_TIPS, Passive<SKILL_PASSIVE_NAME>(PASSIVE_CLASS_NAME::BASE, 2)
			.withDependency(SKILL_PASSIVE_NAME::LIGHT_BOLTS, 1)
			.withStat(STAT_NAME::BASE_MINION_CRITICAL_STRIKE_CHANCE, 3)
			.withAbsoluteMinimum(1)
		));
		skills.insert(std::make_pair(
			SKILL_PASSIVE_NAME::PERFECT_AIM, Passive<SKILL_PASSIVE_NAME>(PASSIVE_CLASS_NAME::BASE, 4)
			.withDependency(SKILL_PASSIVE_NAME::SHARPENED_TIPS, 1)
			.withStat(STAT_NAME::CRITICAL_STAT_RATIO, 25)
			.withAbsoluteMinimum(4)
		));

		skills.insert(std::make_pair(
			SKILL_PASSIVE_NAME::RAPID_FIRE, Passive<SKILL_PASSIVE_NAME>(PASSIVE_CLASS_NAME::BASE, 4)
			.withDependency(SKILL_PASSIVE_NAME::AGILE_ENGENEERING, 1)
			.withStat(STAT_NAME::INCREASED_ATTACK_SPEED, 6)
			.withAbsoluteMinimum(1)
		));
		skills.insert(std::make_pair(
			SKILL_PASSIVE_NAME::CONTAMINATING_SHOTS, Passive<SKILL_PASSIVE_NAME>(PASSIVE_CLASS_NAME::BASE, 3)
			.withDependency(SKILL_PASSIVE_NAME::RAPID_FIRE, 2)
			.withStat(STAT_NAME::AILMENT_STAT_RATIO, 25)
			.withAbsoluteMinimum(0)
		));
		skills.insert(std::make_pair(
			SKILL_PASSIVE_NAME::STURDY_FOUNDATION, Passive<SKILL_PASSIVE_NAME>(PASSIVE_CLASS_NAME::BASE, 3)
			.withDependency(SKILL_PASSIVE_NAME::RAPID_FIRE, 1)
			.withAbsoluteMinimum(2)
		));
		skills.insert(std::make_pair(
			SKILL_PASSIVE_NAME::CARE_PACKAGE, Passive<SKILL_PASSIVE_NAME>(PASSIVE_CLASS_NAME::BASE, 2)
			.withDependency(SKILL_PASSIVE_NAME::STURDY_FOUNDATION, 1)
			.withAbsoluteMinimum(2)
		));
		skills.insert(std::make_pair(
			SKILL_PASSIVE_NAME::ELIXIR_OF_CONSTRUCTION, Passive<SKILL_PASSIVE_NAME>(PASSIVE_CLASS_NAME::BASE, 5)
			.withDependency(SKILL_PASSIVE_NAME::CARE_PACKAGE, 2)
			.withStat(STAT_NAME::MORE_DAMAGE, 20)
			.withAbsoluteMinimum(3)
		));
	}

	std::set<PassiveCombination<SKILL_PASSIVE_NAME>> basePassiveCombinationSet;
	auto initCombo = PassiveCombination<SKILL_PASSIVE_NAME>();
	for (auto skill : skills) {
		initCombo.setPassivePoints(skill.first, skill.second.getClass(), skill.second.getAbsoluteMinimum());
	}

	auto shared1 = initCombo;
	shared1.setPassivePoints(SKILL_PASSIVE_NAME::RAPID_FIRE, PASSIVE_CLASS_NAME::BASE, 2); // 1
	shared1.setPassivePoints(SKILL_PASSIVE_NAME::CONTAMINATING_SHOTS, PASSIVE_CLASS_NAME::BASE, 1); // 1
	shared1.setPassivePoints(SKILL_PASSIVE_NAME::ELIXIR_OF_CONSTRUCTION, PASSIVE_CLASS_NAME::BASE, 4); // 1
	skillSet.push_back(shared1);
	shared1.setPassivePoints(SKILL_PASSIVE_NAME::ELIXIR_OF_CONSTRUCTION, PASSIVE_CLASS_NAME::BASE, 5); // 2
	skillSetKestrel.push_back(shared1);

	auto shared2 = initCombo;
	shared2.setPassivePoints(SKILL_PASSIVE_NAME::RAPID_FIRE, PASSIVE_CLASS_NAME::BASE, 2); // 1
	shared2.setPassivePoints(SKILL_PASSIVE_NAME::CONTAMINATING_SHOTS, PASSIVE_CLASS_NAME::BASE, 2); //2
	skillSet.push_back(shared2);
	shared2.setPassivePoints(SKILL_PASSIVE_NAME::ELIXIR_OF_CONSTRUCTION, PASSIVE_CLASS_NAME::BASE, 4); // 1
	skillSetKestrel.push_back(shared2);
	/*
	auto shared0 = initCombo;
	shared0.setPassivePoints(SKILL_PASSIVE_NAME::ELIXIR_OF_CONSTRUCTION, PASSIVE_CLASS_NAME::BASE, 5); //2
	shared0.setPassivePoints(SKILL_PASSIVE_NAME::HEAVY_BOLTS, PASSIVE_CLASS_NAME::BASE, 1); // 1
	skillSet.push_back(shared0);
	shared0.setPassivePoints(SKILL_PASSIVE_NAME::HEAVY_BOLTS, PASSIVE_CLASS_NAME::BASE, 0); // 0
	shared0.setPassivePoints(SKILL_PASSIVE_NAME::LIGHT_BOLTS, PASSIVE_CLASS_NAME::BASE, 2); // 1
	skillSet.push_back(shared0);
	shared0.setPassivePoints(SKILL_PASSIVE_NAME::HEAVY_BOLTS, PASSIVE_CLASS_NAME::BASE, 1); // 1
	skillSetKestrel.push_back(shared0);
	*/
}

bool BuildMaker::tests() {
	auto combo = PassiveCombination<PASSIVE_NAME>();

	// actual spent skill points < minimum
	combo.addPassivePoint(PASSIVE_NAME::EVASION, passives.at(PASSIVE_NAME::EVASION).getClass());
	if (true == passiveCombinationOk(passives, combo))
		return false;

	// dependency not satistied
	combo = PassiveCombination<PASSIVE_NAME>();
	for (int i = 0; i < 5; ++i)
		combo.addPassivePoint(PASSIVE_NAME::STEADY_HAND, passives.at(PASSIVE_NAME::EVASION).getClass());
	combo.addPassivePoint(PASSIVE_NAME::EVASION, passives.at(PASSIVE_NAME::EVASION).getClass());
	if (true == passiveCombinationOk(passives, combo))
		return false;

	return true;
}

void BuildMaker::addItemCandidate(Item item) {
	//std::cout << item.toString() << std::endl << std::endl;
	switch (item.getType()) {
	case HELM: items.addItem(HELM_SLOT, item); break;
	case AMULET: items.addItem(AMULET_SLOT, item); break;
	case BOW: items.addItem(BOW_SLOT, item); break;
	case QUIVER: items.addItem(QUIVER_SLOT, item); break;
	case BODY: items.addItem(BODY_SLOT, item); break;
	case RING: items.addItem(RING_LEFT_SLOT, item); items.addItem(RING_RIGHT_SLOT, item); break;
	case BELT: items.addItem(BELT_SLOT, item); break;
	case GLOVES: items.addItem(GLOVES_SLOT, item); break;
	case BOOTS: items.addItem(BOOTS_SLOT, item); break;
	case RELIC: items.addItem(RELIC_SLOT, item); break;
	case BIG_IDOL: items.addItem(BIG_IDOL_1_SLOT, item); items.addItem(BIG_IDOL_2_SLOT, item); items.addItem(BIG_IDOL_3_SLOT, item); items.addItem(BIG_IDOL_4_SLOT, item); break;
	case SMALL_IDOL: items.addItem(SMALL_IDOL_1_SLOT, item); items.addItem(SMALL_IDOL_2_SLOT, item); items.addItem(SMALL_IDOL_3_SLOT, item); items.addItem(SMALL_IDOL_4_SLOT, item); break;
	case BLESSING_BLACK_SUN: items.addItem(BLESSING_BLACK_SUN_SLOT, item); break;
	case BLESSING_REIGN_OF_DRAGONS: items.addItem(BLESSING_REIGN_OF_DRAGONS_SLOT, item); break;
	case BLESSING_SPIRITS_OF_FIRE: items.addItem(BLESSING_SPIRITS_OF_FIRE_SLOT, item); break;
	case BLESSING_THE_AGE_OF_WINTER: items.addItem(BLESSING_THE_AGE_OF_WINTER_SLOT, item); break;
	case BLESSING_ENDING_THE_STORM: items.addItem(BLESSING_ENDING_THE_STORM_SLOT, item); break;
	}	
}

double BuildMaker::calculateDps() {
	return calculateDpsIf(currentItemSet);
}

double BuildMaker::calculateDpsIf(ItemSet ifItemSet) {
	auto it = dpsCacheItems.find(ifItemSet);
	if (it != dpsCacheItems.end()) {
		//std::cout << "Using cached items dps" << std::endl;
		return it->second;
	}

	currentItemSet = ifItemSet;
	int prevVerbose = verbose;
	//verbose = 0;
	findBestSkills();
	verbose = prevVerbose;

	auto result = calculateDpsIf(currentSkills);
	dpsCacheItems.insert(std::make_pair(ifItemSet, result));
	return result;
}

double BuildMaker::calculateDpsIf(PassiveCombination<SKILL_PASSIVE_NAME> ifSkills) {
	auto it = dpsCacheSkills.find(std::make_pair(currentItemSet, ifSkills));
	if (it != dpsCacheSkills.end()) {
		//std::cout << "Using cached skills dps" << std::endl;
		return it->second;
	}

	currentSkills = ifSkills;
	int prevVerbose = verbose;
	//verbose = 0;
	findBestPassives();
	verbose = prevVerbose;

	auto result = calculateDpsIf(bestPassives);
	dpsCacheSkills.insert(std::make_pair(std::make_pair(currentItemSet, ifSkills), result));
	return result;
}

double BuildMaker::calculateDpsIf(PassiveCombination<PASSIVE_NAME> ifPassives) {
	std::map<STAT_NAME, std::vector<std::pair<std::string, double>>> currentStats;
	// PASSIVES
	{
		auto allPassives = ifPassives.getPassives();
		for (auto passive : allPassives) {
			if (passive.first == PURSUIT)
				int fdsf = 1;
			Passive<PASSIVE_NAME>& passiveDefinition = passives.at(passive.first);
			auto stats = passiveDefinition.getStats(passive.second);
			for (auto stat : stats) {
				if (verbose >= 2) std::cout << STRINGS::PASSIVE_NAME_MAP.at(passive.first) << ": " << STRINGS::STAT_NAME_MAP.at(stat.first) << " = " << stat.second << std::endl;
				auto it = currentStats.find(stat.first);
				if (it == currentStats.end()) {
					currentStats.insert(std::make_pair(stat.first,
						std::vector<std::pair<std::string, double>>{
						std::make_pair(STRINGS::PASSIVE_NAME_MAP.at(passive.first), stat.second)
					}));
				}
				else {
					it->second.push_back(std::make_pair(STRINGS::PASSIVE_NAME_MAP.at(passive.first), stat.second));
				}
			}
		}
	}
	// SKILLS
	{
		auto allSkills = currentSkills.getPassives();
		for (auto skillPassive : currentSkills.getPassives()) {
			auto skillDefinition = skills.at(skillPassive.first);
			auto stats = skillDefinition.getStats(skillPassive.second);
			for (auto stat : stats) {
				if (verbose >= 2) std::cout << STRINGS::SKILL_PASSIVE_NAME_MAP.at(skillPassive.first) << ": " << STRINGS::STAT_NAME_MAP.at(stat.first) << " = " << stat.second << std::endl;
				auto it = currentStats.find(stat.first);
				if (it == currentStats.end()) {
					currentStats.insert(std::make_pair(stat.first,
						std::vector<std::pair<std::string, double>>{
						std::make_pair(STRINGS::SKILL_PASSIVE_NAME_MAP.at(skillPassive.first), stat.second)
					}));
				}
				else {
					it->second.push_back(std::make_pair(STRINGS::SKILL_PASSIVE_NAME_MAP.at(skillPassive.first), stat.second));
				}
			}
		}
	}
	// ITEMS
	{
		auto allItems = currentItemSet.getAllItems();
		for (auto item : allItems) {
			auto stats = item.getStats();
			for (auto stat : stats) {
				if (verbose >= 2) std::cout << item.getName() << ": " << STRINGS::STAT_NAME_MAP.at(stat.first) << " = " << stat.second << std::endl;
				auto it = currentStats.find(stat.first);
				if (it == currentStats.end()) {
					currentStats.insert(std::make_pair(stat.first,
						std::vector<std::pair<std::string, double>>{
						std::make_pair(item.getName(), stat.second)
					}));
				}
				else {
					it->second.push_back(std::make_pair(item.getName(), stat.second));
				}
			}
		}
	}
	if (verbose==2) std::cout << "==================================== CALCULATING DAMAGE ====================================" << std::endl;
	{
		double allStats = statSum(currentStats, ALL_ATRIBUTES);
		if (verbose >= 2) std::cout << "ALL ATTRIBUTES: " << allStats << std::endl << std::endl;
		double dex = statSum(currentStats, DEXTERITY) + allStats;
		if (verbose >= 2) std::cout << "DEXTERITY: " << dex << std::endl << std::endl;

		double damageRatio = statSum(currentStats, DAMAGE_STAT_RATIO) / 100;
		if (verbose >= 2) std::cout << "SHARED DAMAGE RATIO: " << (damageRatio * 100) << "%" << std::endl;
		double flatPhys = statSum(currentStats, FLAT_MINION_PHYSICAL_DAMAGE) + statSum(currentStats, FLAT_PHYSICAL_DAMAGE) * damageRatio;
		flatPhys *= 2;
		if (verbose >= 2) std::cout << "FLAT PHYSICAL DAMAGE: " << flatPhys << std::endl;
		double flatCold = (dex * statSum(currentStats, FLAT_COLD_PER_DEX)) * damageRatio;
		flatCold *= 2;
		if (verbose >= 2) std::cout << "FLAT COLD DAMAGE: " << flatCold << std::endl;
		double flatLight = statSum(currentStats, FLAT_LIGHTNING_DAMAGE) * damageRatio;
		flatLight *= 2;
		if (verbose >= 2) std::cout << "FLAT LIGHTNING DAMAGE: " << flatLight << std::endl << std::endl;

		double addedflatPhysFalcon = statSum(currentStats, FLAT_MINION_PHYSICAL_DAMAGE_FALCON);
		if (verbose >= 2) std::cout << "ADDED FLAT PHYSICAL DAMAGE FALCON: " << addedflatPhysFalcon << std::endl;
		double flatPhysFalcon = 30 + addedflatPhysFalcon * 1.5;
		if (verbose >= 2) std::cout << "ATTACK FLAT PHYSICAL DAMAGE FALCON: " << flatPhysFalcon << std::endl;
		double flatPhysDiveBomb = 170 + addedflatPhysFalcon * 8.5 + 80 + addedflatPhysFalcon * 4; // + feather
		if (verbose >= 2) std::cout << "DIVE BOMB PHYSICAL DAMAGE FALCON: " << flatPhysDiveBomb << std::endl << std::endl;

		double increasedAttackSpeed1 = statSum(currentStats, INCREASED_ATTACK_SPEED);
		if (verbose >= 2) std::cout << "INCREASED ATTACK SPEED FROM ITEMS: " << increasedAttackSpeed1 << std::endl;
		double increasedAttackSpeed2 = statSum(currentStats, INCREASED_ATTACK_SPEED_PER_DEXTERITY) * dex;
		if (verbose >= 2) std::cout << "INCREASED ATTACK SPEED FROM DEXTERITY: " << increasedAttackSpeed2 << std::endl;
		double increasedAttackSpeed = increasedAttackSpeed1 + increasedAttackSpeed2;
		if (verbose >= 2) std::cout << "INCREASED ATTACK SPEED: " << increasedAttackSpeed << std::endl;
		double moreAttackSpeed = statProduct(currentStats, MORE_ATTACK_SPEED);
		if (verbose >= 2) std::cout << "MORE ATTACK SPEED: " << moreAttackSpeed << "%" << std::endl;
		double hitsPerSecond = 6 * 0.717 * (100 + increasedAttackSpeed) / 100 * (100 + moreAttackSpeed) / 100;
		if (verbose >= 2) std::cout << "BALLISTA HITS PER SECOND: " << hitsPerSecond << std::endl;
		double hitsPerSecondFalcon = 1.257 * 1.2 * 1.16;
		if (verbose >= 2) std::cout << "FALCON HITS PER SECOND: " << hitsPerSecondFalcon << std::endl << std::endl;
		double hitsPerSecondDiveBomb = (1.0 + 0.12 * 4) / 5;
		if (verbose >= 2) std::cout << "DIVE BOMB HITS PER SECOND: " << hitsPerSecondDiveBomb << std::endl << std::endl;
		if (!stacks) hitsPerSecondFalcon = 0;
		if (!stacks) hitsPerSecondDiveBomb = 0;

		double increasedDamagePerDex = dex * statSum(currentStats, INCREASED_MINION_DAMAGE_PER_DEXTERITY);
		if (verbose >= 2) std::cout << "INCREASED DAMAGE PER DEXTERITY: " << increasedDamagePerDex << std::endl;
		double increasedDamagePerMs = statSum(currentStats, INCREASED_MOVEMENT_SPEED) * statSum(currentStats, INCREASED_DAMAGE_PER_MOVEMENT_SPEED);
		if (verbose >= 2) std::cout << "INCREASED DAMAGE PER MOVEMENT SPEED: " << increasedDamagePerMs << std::endl;
		double increasedDamage = statSum(currentStats, INCREASED_MINION_DAMAGE) + (statSum(currentStats, INCREASED_DAMAGE) + increasedDamagePerMs) * damageRatio + increasedDamagePerDex;
		if (verbose >= 2) std::cout << "INCREASED DAMAGE: " << increasedDamage << std::endl;
		double increasedDamageFalcon = statSum(currentStats, INCREASED_MINION_DAMAGE) + (statSum(currentStats, INCREASED_DAMAGE) + increasedDamagePerMs) * 0.75 + increasedDamagePerDex;
		if (verbose >= 2) std::cout << "INCREASED DAMAGE FALCON: " << increasedDamageFalcon << std::endl;
		double increasedMinionPhys = statSum(currentStats, INCREASED_MINION_PHYSICAL_DAMAGE) + statSum(currentStats, INCREASED_PHYSICAL_DAMAGE) * damageRatio / 100;
		if (verbose >= 2) std::cout << "INCREASED MINION PHYSICAL DAMAGE: " << increasedMinionPhys << std::endl;
		double increasedCold = statSum(currentStats, INCREASED_COLD_DAMAGE) * damageRatio / 100;
		if (verbose >= 2) std::cout << "INCREASED COLD DAMAGE: " << increasedCold << std::endl;
		double intelligence = statSum(currentStats, INTELLIGENCE) + allStats;
		if (verbose >= 2) std::cout << "INTELLIGENCE: " << intelligence << std::endl;
		double moreDamage = (100 + statProduct(currentStats, MORE_DAMAGE)) / 100 * (100 + intelligence * statSum(currentStats, MORE_DAMAGE_PER_INTELLIGENCE));
		if (verbose >= 2) std::cout << "MORE DAMAGE: " << moreDamage << "%" << std::endl;
		double moreDamageFalcon = (1.75 * 2 * (dex + 100) / 100 * 1.15 * 1.1) * 100;
		if (verbose >= 2) std::cout << "MORE DAMAGE FALCON: " << moreDamageFalcon << "%" << std::endl << std::endl;
		double moreDamageDiveBomb = ((moreDamageFalcon + 100) / 100 * (1 + 0.04 * 4) * (1 + 0.04 * 4)) * 100;
		if (verbose >= 2) std::cout << "MORE DAMAGE DIVE BOMB: " << moreDamageDiveBomb << "%" << std::endl << std::endl;

		double ailmentRatio = statSum(currentStats, AILMENT_STAT_RATIO) / 100;
		if (verbose >= 2) std::cout << "SHARED AILMENTS RATIO: " << (ailmentRatio * 100) << "%" << std::endl;
		double averageStacks = 4 * (ailmentRatio * hitsPerSecond + 2 * hitsPerSecondFalcon) / 100;
		if (!stacks) averageStacks = 0;
		if (verbose >= 2) std::cout << "AVERAGE AILMENT STACKS FOR 1% chance: " << averageStacks << std::endl;
		
		double averageCritVulnerabilityStacks = 0;
		if (!disableCriticalVulnerability) {
			double critVulnerabilityChance = statSum(currentStats, CRITICAL_VULNERABILITY_CHANCE);
			if (verbose >= 2) std::cout << "CHANCE TO APPLY CRIT VULNERABILITY: " << critVulnerabilityChance << "%" << std::endl;
			averageCritVulnerabilityStacks = std::min<double>(10, averageStacks * critVulnerabilityChance + hitsPerSecondDiveBomb * 4 * 3);
			if (verbose >= 2) std::cout << "AVERAGE CRIT VULNERABILITY STACKS: " << averageCritVulnerabilityStacks << std::endl;
		}
		
		double physShredChance = statSum(currentStats, CHANCE_TO_SHRED_PHYS_RES);
		if (verbose >= 2) std::cout << "CHANCE TO SHRED PHYSICAL RESISTANCE: " << physShredChance << "%" << std::endl;
		double averagePhysShredStacks = std::min<double>(10, averageStacks * physShredChance + hitsPerSecondDiveBomb * 4 * 5);
		if (verbose >= 2) std::cout << "AVERAGE PHYSICAL SHRED STACKS: " << averagePhysShredStacks << std::endl;
		double physPen = statSum(currentStats, PHYSICAL_PENETRATION) + averagePhysShredStacks * 2;
		if (verbose >= 2) std::cout << "TOTAL PHYSICAL PENETRATION: " << physPen << "%" << std::endl;
		double lightShredChance = statSum(currentStats, CHANCE_TO_SHRED_LIGHTNING_RES);
		if (verbose >= 2) std::cout << "CHANCE TO SHRED LIGHTNING RESISTANCE: " << lightShredChance << "%" << std::endl;
		double averageLightShredStacks = std::min<double>(10, averageStacks * lightShredChance);
		if (verbose >= 2) std::cout << "AVERAGE LIGHTNING SHRED STACKS: " << averageLightShredStacks << std::endl;
		double shockChance = statSum(currentStats, SHOCK_CHANCE);
		if (verbose >= 2) std::cout << "CHANCE TO SHOCK: " << shockChance << "%" << std::endl;
		double averageShockStacks = std::min<double>(10, averageStacks * shockChance);
		if (verbose >= 2) std::cout << "AVERAGE SHOCK STACKS: " << averageShockStacks << std::endl;
		double armourShredChance = statSum(currentStats, ARMOUR_SHRED_CHANCE);
		if (verbose >= 2) std::cout << "CHANCE TO SHRED ARMOUR: " << armourShredChance << "%" << std::endl;
		double armourShredEffect = statSum(currentStats, ARMOUR_SHRED_EFFECT);
		if (verbose >= 2) std::cout << "ARMOUR SHRED EFFECT (ONLY BALLISTAS, NO FALCON): " << armourShredEffect << "%" << std::endl;
		double averageArmourShred = 4 * (ailmentRatio * hitsPerSecond * (100 + armourShredEffect * ailmentRatio) / 100 + 2 * hitsPerSecondFalcon) * (armourShredChance + hitsPerSecondDiveBomb * 200);
		if (!stacks) averageArmourShred = 0;
		double averageArmourShredStacks = 4 * (ailmentRatio * hitsPerSecond + 2 * hitsPerSecondFalcon) * (armourShredChance / 100 + hitsPerSecondDiveBomb * 2);
		if (verbose >= 2) std::cout << "AVERAGE ARMOUR SHRED STACKS: " << averageArmourShredStacks << std::endl;
		if (verbose >= 2) std::cout << "AVERAGE ARMOUR SHRED: " << averageArmourShred << std::endl;
		double physArmorShredMore = 100 * (1.2 * averageArmourShred / (80 + 0.05 * pow(105, 2) + 1.2 * averageArmourShred) * 0.3
			+ 0.0012 * pow(averageArmourShred, 2) / (180 * 105 + 0.0015 * pow(averageArmourShred, 2)) * 0.55);
		if (verbose >= 2) std::cout << "AVERAGE MORE PHYCICAL DAMAGE FROM ARMOUR SHRED: " << physArmorShredMore << "%" << std::endl;
		double otherArmorShredMore = physArmorShredMore * 0.7;
		if (verbose >= 2) std::cout << "AVERAGE MORE OTHER DAMAGE FROM ARMOUR SHRED: " << otherArmorShredMore << "%" << std::endl << std::endl;

		double critRatio = statSum(currentStats, CRITICAL_STAT_RATIO) / 100;
		if (verbose >= 2) std::cout << "SHARED CRIT RATIO: " << (critRatio * 100) << "%" << std::endl;
		double baseCritMinion = statSum(currentStats, BASE_MINION_CRITICAL_STRIKE_CHANCE);
		if (verbose >= 2) std::cout << "BASE MINION CRIT: " << baseCritMinion << "%" << std::endl;
		double baseCritOwn = statSum(currentStats, BASE_CRITICAL_STRIKE_CHANCE);
		if (verbose >= 2) std::cout << "BASE OWN CRIT: " << baseCritOwn << "%" << std::endl;
		double baseCrit = baseCritMinion + baseCritOwn * critRatio;
		if (verbose >= 2) std::cout << "BASE CRIT: " << baseCrit << "%" << std::endl;
		double increasedCritChanceOwn = statSum(currentStats, INCREASED_CRITICAL_STRIKE_CHANCE);
		if (verbose >= 2) std::cout << "INCREASED CRIT CHANCE OWN: " << increasedCritChanceOwn << "%" << std::endl;
		double increasedCritChanceMinions = statSum(currentStats, INCREASED_MINION_CRITICAL_STRIKE_CHANCE);
		if (verbose >= 2) std::cout << "INCREASED CRIT CHANCE MINIONS: " << increasedCritChanceMinions << "%" << std::endl;
		double increasedCritChance = increasedCritChanceOwn * critRatio + increasedCritChanceMinions;
		if (verbose >= 2) std::cout << "INCREASED CRIT CHANCE TOTAL: " << increasedCritChance << "%" << std::endl;
		double increasedCritChanceFalcon = increasedCritChanceOwn * 0.75 + increasedCritChanceMinions;
		if (verbose >= 2) std::cout << "INCREASED CRIT CHANCE TOTAL FALCON: " << increasedCritChanceFalcon << "%" << std::endl;
		double increasedCritMultiOwn = statSum(currentStats, INCREASED_CRITICAL_STRIKE_MULTIPLIER);
		if (verbose >= 2) std::cout << "INCREASED CRIT MULTI OWN: " << increasedCritMultiOwn << "%" << std::endl;
		double increasedCritMultiMinions = statSum(currentStats, INCREASED_MINION_CRITICAL_STRIKE_MULTIPLIER);
		if (verbose >= 2) std::cout << "INCREASED CRIT MULTI MINIONS: " << increasedCritMultiMinions << "%" << std::endl;
		double criticalStrikeAvoidance = statSum(currentStats, CRITICAL_STRIKE_AVOIDANCE);
		if (verbose >= 2) std::cout << "CRITICAL STRIKE AVOIDANCE: " << criticalStrikeAvoidance << "%" << std::endl;
		double criticalStrikeAvoidanceMulti = criticalStrikeAvoidance * statSum(currentStats, INCREASED_MINION_CRITICAL_STRIKE_MULTIPLIER_PER_CRITICAL_STRIKE_AVOIDANCE);
		if (verbose >= 2) std::cout << "CRITICAL STRIKE AVOIDANCE CRIT MULTI: " << criticalStrikeAvoidanceMulti << "%" << std::endl;
		double totalCritMulti = increasedCritMultiOwn * critRatio + increasedCritMultiMinions + criticalStrikeAvoidanceMulti;
		if (verbose >= 2) std::cout << "CRIT MULTI TOTAL: " << totalCritMulti << "%" << std::endl;
		double uncappedCritChance = baseCrit * (100 + increasedCritChance) / 100 + averageCritVulnerabilityStacks * 2;
		lastCritChance = baseCrit * (100 + increasedCritChance) / 100;
		if (verbose >= 2) std::cout << "UNCAPPED CRIT CHANCE: " << uncappedCritChance << "%" << std::endl;
		double cappedCritChance = std::min<double>(uncappedCritChance, 100) / 100;
		if (verbose >= 2) std::cout << "CAPPED CRIT CHANCE: " << (cappedCritChance * 100) << "%" << std::endl;
		double effectiveCritMulti = cappedCritChance * totalCritMulti + 100 - cappedCritChance;
		if (verbose >= 2) std::cout << "EFFECTIVE CRIT MULTI: " << effectiveCritMulti << "%" << std::endl;
		double totalCritMultiFalcon = increasedCritMultiOwn * 0.75 + increasedCritMultiMinions + criticalStrikeAvoidanceMulti;
		if (verbose >= 2) std::cout << "CRIT MULTI TOTAL FALCON: " << totalCritMultiFalcon << "%" << std::endl;
		double uncappedCritChanceFalcon = (baseCritMinion * (100 + increasedCritChanceFalcon) / 100
			+ baseCritOwn * 0.75 * (100 + increasedCritChanceOwn) / 100)
			+ averageCritVulnerabilityStacks * 2;
		if (verbose >= 2) std::cout << "UNCAPPED CRIT CHANCE FALCON: " << uncappedCritChanceFalcon << "%" << std::endl;
		double cappedCritChanceFalcon = std::min<double>(uncappedCritChanceFalcon, 100) / 100;
		if (verbose >= 2) std::cout << "CAPPED CRIT CHANCE FALCON: " << (cappedCritChanceFalcon * 100) << "%" << std::endl;
		double effectiveCritMultiFalcon = cappedCritChanceFalcon * totalCritMultiFalcon + 100 - cappedCritChanceFalcon;
		if (verbose >= 2) std::cout << "EFFECTIVE CRIT MULTI FALCON: " << effectiveCritMultiFalcon << "%" << std::endl << std::endl;

		double totalPhysHit = flatPhys * (100 + increasedDamage + increasedMinionPhys) / 100 * moreDamage / 100 * (100 + physPen) / 100 * (100 + physArmorShredMore) / 100 * (effectiveCritMulti / 100);
		double totalColdHit = flatCold * (100 + increasedDamage + increasedCold * damageRatio) / 100 * moreDamage / 100 * (100 + otherArmorShredMore) / 100 * (effectiveCritMulti / 100);
		double totalLightHit = flatLight * (100 + increasedDamage) / 100 * moreDamage / 100 * (100 + averageLightShredStacks * 2) / 100 * (100 + otherArmorShredMore) / 100 * (effectiveCritMulti / 100);
		double totalHitFalcon = flatPhysFalcon * (100 + increasedDamageFalcon + increasedMinionPhys) / 100 * moreDamageFalcon / 100 * (100 + physPen) / 100 * (100 + physArmorShredMore) / 100 * (effectiveCritMultiFalcon / 100);
		double totalHitDiveBomb = flatPhysDiveBomb * (100 + increasedDamageFalcon + increasedMinionPhys) / 100 * moreDamageDiveBomb / 100 * (100 + physPen) / 100 * (100 + physArmorShredMore) / 100 * (effectiveCritMultiFalcon / 100);

		const int w1 = 27;
		const int w2 = 17;
		const int w3 = 11;
		if (verbose >= 2) std::cout << std::setw(w1) << "PHYSICAL HIT:" << std::setw(w2) << totalPhysHit << std::endl;
		if (verbose >= 2) std::cout << std::setw(w1) << "COLD HIT:" << std::setw(w2) << totalColdHit << std::endl;
		if (verbose >= 2) std::cout << std::setw(w1) << "LIGHTNING HIT:" << std::setw(w2) << totalLightHit << std::endl;
		if (verbose >= 2) std::cout << std::setw(w1) << "PHYSICAL HIT FALCON:" << std::setw(w2) << totalHitFalcon << std::endl;
		if (verbose >= 2) std::cout << std::setw(w1) << std::fixed << "PHYSICAL HIT DIVE BOMB:" << std::setw(w2) << totalHitDiveBomb << std::endl;
		double dps = (totalPhysHit + totalColdHit + totalLightHit) * hitsPerSecond + totalHitFalcon * hitsPerSecondFalcon + totalHitDiveBomb * hitsPerSecondDiveBomb;
		if (verbose >= 2) std::cout << std::setw(w1) << "PHYSICAL DPS:" << std::setw(w2) << totalPhysHit * hitsPerSecond << std::setw(w3) << (totalPhysHit * hitsPerSecond / dps * 100) << "%" << std::endl;
		if (verbose >= 2) std::cout << std::setw(w1) << "COLD DPS:" << std::setw(w2) << totalColdHit * hitsPerSecond << std::setw(w3) << (totalColdHit * hitsPerSecond / dps * 100) << "%" << std::endl;
		if (verbose >= 2) std::cout << std::setw(w1) << "LIGHTNING DPS:" << std::setw(w2) << totalLightHit * hitsPerSecond << std::setw(w3) << (totalLightHit * hitsPerSecond / dps * 100) << "%" << std::endl;
		if (verbose >= 2) std::cout << std::setw(w1) << "PHYSICAL DPS FALCON ATTACK:" << std::setw(w2) << totalHitFalcon * hitsPerSecondFalcon << std::setw(w3) << (totalHitFalcon * hitsPerSecondFalcon / dps * 100) << "%" << std::endl;
		if (verbose >= 2) std::cout << std::setw(w1) << "PHYSICAL DPS DIVE BOMB:" << std::setw(w2) << totalHitDiveBomb * hitsPerSecondDiveBomb << std::setw(w3) << (totalHitDiveBomb * hitsPerSecondDiveBomb / dps * 100) << "%" << std::endl << std::endl;

		if (verbose >= 2) std::cout << std::setw(w1) << "TOTAL DPS: " << std::setw(w2) << dps << std::endl;
		if (verbose >= 2) std::cout << std::setw(w1) << "VULNI CRIT: " << std::setw(w2) << uncappedCritChance << "%" << std::endl;
		if (verbose >= 2) std::cout << std::setw(w1) << "NO VULNI CRIT: " << std::setw(w2) << baseCrit * (100 + increasedCritChance) / 100 << "%" << std::endl;

		return dps;
	}

}

void BuildMaker::findBestItems() {
	double currentDpsCopy;
	ItemSet currentItemSetCopy;
	auto allItems = items.getAllItemSet();
	std::map<ITEM_TYPE, std::set<int>> usedItems = usedItemsInit;
	
	for (auto slotItems : items.getAllItemSet()) {
		/*if (slotItems.second.size() < 2)
			continue;*/

		//if (verbose >= 2)
		std::cout << std::endl << "ANALYZING " << STRINGS::ITEM_SLOT_MAP.at(slotItems.first) << std::endl;
		currentDpsCopy = bestDps;
		currentItemSetCopy = bestItemSet;
		/*if (slotItems.second.size() < 2)
			continue;*/
		std::map<double, std::tuple<int, Item, ItemSet>> maybeNewItemsMap;
		for (int i = 0; i < slotItems.second.size(); ++i) {
			auto item = slotItems.second[i];
			if (!allowSameItems && usedItems.at(item.getType()).count(i) > 0)
				continue;
		//for (auto item : slotItems.second) {
			//std::cout << std::endl;
			auto maybeItemSet = currentItemSetCopy;
			maybeItemSet.changeItem(slotItems.first, item);
			auto newDps = calculateDpsIf(maybeItemSet);
			maybeNewItemsMap.insert(std::make_pair(newDps, std::make_tuple(i, item, maybeItemSet)));
			//if (verbose >= 1) std::cout << newDps << " - " << item.toString() << std::endl;
		}
		if (maybeNewItemsMap.empty())
			continue;

		auto newDps = maybeNewItemsMap.rbegin()->first;
		auto newItem = std::get<1>(maybeNewItemsMap.rbegin()->second);
		usedItems.at(newItem.getType()).insert(std::get<0>(maybeNewItemsMap.rbegin()->second));
		if (newDps > currentDpsCopy) {
			if (verbose >= 1) {
				std::cout << std::endl << "Changing item for more DPS " << currentDpsCopy << " -> " << newDps << " +" << (newDps / currentDpsCopy - 1) * 100 << "%: " << " " << std::endl;
				std::cout << "from: " << (currentItemSetCopy.hasItem(slotItems.first) ? currentItemSetCopy.getItem(slotItems.first).toString() : "nothing") << std::endl;
				std::cout << "to  : " << newItem.toString() << std::endl;
			}
		}
		else {
			if (verbose >= 1) {
				//std::cout << std::endl << "NOTHING BETTER WAS FOUND, current DPS = " << bestDps << std::endl;
			}
		}
		bestDps = newDps;
		currentDps = bestDps;
		currentItemSet = std::get<2>(maybeNewItemsMap.rbegin()->second);
		bestItemSet = currentItemSet;
	}
	//if (verbose >= 1) std::cout << std::endl;
}

void BuildMaker::findBestSkills() {
	auto currentDpsCopy = bestDps;
	auto currentSkillsCopy = bestSkills;
	bool isKestrel = currentItemSet.getAllStats().count(STAT_NAME::LEVEL_OF_BALLISTA) > 0;
	auto maybeSkillsSet = isKestrel ? skillSetKestrel : skillSet;
	std::map<double, PassiveCombination<SKILL_PASSIVE_NAME>> maybeSkillsMap;
	for (auto maybeSkills : maybeSkillsSet) {
		maybeSkillsMap.insert(std::make_pair(calculateDpsIf(maybeSkills), maybeSkills));
	}
	auto newDps = maybeSkillsMap.rbegin()->first;
	auto newSkills = maybeSkillsMap.rbegin()->second;
	if (maybeSkillsMap.rbegin()->second != currentSkillsCopy) {
		if (verbose >= 1) {
			std::cout << "Changing skill set for more DPS " << currentDps << " -> " << newDps << " +" << (newDps / currentDps - 1) * 100 << "%: "
				<< maybeSkillsMap.rbegin()->second.toString(STRINGS::SKILL_PASSIVE_NAME_MAP) << std::endl << std::endl;
			for (auto skill : currentSkillsCopy.getPassives()) {
				if (newSkills.getPassivePoints(skill.first) != skill.second)
					std::cout << STRINGS::SKILL_PASSIVE_NAME_MAP.at(skill.first) << ": " << skill.second << " -> " << newSkills.getPassivePoints(skill.first) << std::endl;
			}
		}
	}
	currentSkills = maybeSkillsMap.rbegin()->second;
	bestSkills = currentSkills;
	bestDps = newDps;
	currentDps = bestDps;
	//currentSkills = currentSkillsCopy;
	//if (verbose >= 1) std::cout << std::endl;
}

void BuildMaker::findBestPassives() {
	if (reversePassiveSearch) {
		if (verbose >= 2) counter = 0;
		auto r = findBestPassivesReverse(minimumPassives, minimumPassives.totalPoints());
		bestDps = r.second;
		currentDps = bestDps;
		bestPassives = r.first;
		bestSkills = currentSkills;
		bestItemSet = currentItemSet;
		
	}
	else {
		bestDpsFound = false;
		//currentDps = calculateDpsIf(minimumPassives);
		findBestPassives(minimumPassives, passivePoints - minimumPassives.totalPoints(), bestDps);
		//if (verbose >= 1) std::cout << std::endl;
	}
	//auto p = bestPassives.totalPoints();
	//printPassiveCombination(STRINGS::PASSIVE_NAME_MAP, bestPassives);
	return;
}

void BuildMaker::findBestPassives(PassiveCombination<PASSIVE_NAME>& combo, int pointsLeft, double currentDpsCopy) {
	if (pointsLeft == 0) {
		//passiveDependencyCache.clear();
		if (dependencySatisfied(passives, combo, passiveDependencyCache).first != DEPENDENCY_OK)
			return;

		bestDpsFound = true;
		if (currentDpsCopy > bestDps && bestPassives != combo) {
			if (verbose >= 1) {
				/*
				std::cout << "Changing passives for more DPS " << bestDps << " -> " << currentDpsCopy << " +" << (currentDpsCopy / bestDps - 1) * 100 << "%: " << std::endl;
				for (auto passive : bestPassives.getPassives()) {
					if (combo.getPassivePoints(passive.first) != passive.second)
						std::cout << STRINGS::PASSIVE_NAME_MAP.at(passive.first) << ": " << passive.second 
							<< " -> " << combo.getPassivePoints(passive.first) << std::endl;
				}
				std::cout << std::endl;
				*/
			}
			bestDpsFound = true;
			bestDps = currentDpsCopy;
			currentDps = bestDps;
			bestPassives = combo;
			bestSkills = currentSkills;
			bestItemSet = currentItemSet;
			//if (verbose >= 1) std::cout << "New best DPS: " << bestDps << std::endl;
			//return;
		}
		return;
	}

	std::map<double, std::pair<PASSIVE_NAME, PassiveCombination<PASSIVE_NAME>>> maybeNewPassiveMap;
	for (auto passive : combo.getPassives()) {
		if (passive.second < passives.at(passive.first).getMaximumPoints()) {
			auto maybeCombo = combo;
			maybeCombo.addPassivePoint(passive.first, passives.at(passive.first).getClass());
			if (dependencySatisfied(passives, maybeCombo, passiveDependencyCache).first == DEPENDENCY_OK)
				maybeNewPassiveMap.insert(std::make_pair(calculateDpsIf(maybeCombo), std::make_pair(passive.first, maybeCombo)));
		}
	}
	for (auto maybeIt = maybeNewPassiveMap.rbegin(); maybeIt != maybeNewPassiveMap.rend(); ++maybeIt) {
		//printPassiveCombination(STRINGS::PASSIVE_NAME_MAP, maybeIt->second.second);
		//std::cout << pointsLeft << " " << STRINGS::PASSIVE_NAME_MAP.at(maybeIt->second.first) << " passiveDependencyCache.size() = " << passiveDependencyCache.size() << std::endl;
		if (verbose>=2) std::cout << maybeIt->first << " " << STRINGS::PASSIVE_NAME_MAP.at(maybeIt->second.first) << std::endl;
		findBestPassives(maybeIt->second.second, pointsLeft - 1, maybeIt->first);
		if (bestDpsFound)
			return;
	}
}

std::pair<PassiveCombination<PASSIVE_NAME>, double> BuildMaker::findBestPassivesReverse(PassiveCombination<PASSIVE_NAME>& combo, int pointsAllocated, PASSIVE_NAME limit) {
	if (pointsAllocated == passivePoints) {
		return std::make_pair(combo, calculateDpsIf(combo));
	}

	// first try all and sort by dps
	std::vector<std::tuple<double, PASSIVE_NAME, PassiveCombination<PASSIVE_NAME>>> passiveDpsVector;

	auto allPassives = combo.getPassives();
#pragma omp parallel for schedule(guided) num_threads(num_threads) shared(passiveDpsVector)
	for (int i = 0; i < allPassives.size(); ++i) {
		auto it = allPassives.begin(); // Get iterator for element at index i
		std::advance(it, i);     // Advance iterator to the i-th element

		auto passive = *it;
		if (limit != PASSIVE_NAME::BASE_STATS && passive.first != limit)
			continue;
		if (passive.second == 0 || passive.second - 1 < passives.at(passive.first).getAbsoluteMinimum())
			continue; // can't substract
		auto maybeCombo = combo;
		maybeCombo.substractPassivePoint(passive.first, passives.at(passive.first).getClass());
		auto dps = calculateDpsIf(maybeCombo);
#pragma omp critical
		passiveDpsVector.push_back(std::make_tuple(dps, passive.first, maybeCombo));
	}
/*
	for (auto passive : allPassives) {
		if (limit != PASSIVE_NAME::BASE_STATS && passive.first != limit)
			continue;
		if (passive.second == 0 || passive.second-1 < passives.at(passive.first).getAbsoluteMinimum())
			continue; // can't substract
		auto maybeCombo = combo;
		maybeCombo.substractPassivePoint(passive.first, passives.at(passive.first).getClass());
		auto t = calculateDpsIf(maybeCombo);
		auto dps = calculateDpsIf(maybeCombo);
		passiveDpsVector.push_back(std::make_tuple(dps, passive.first, maybeCombo));
	}
*/
	std::sort(passiveDpsVector.begin(), passiveDpsVector.end(), [](const auto& a, const auto& b) { return std::get<0>(a) < std::get<0>(b); });

	if (verbose >= 2 ) for (auto it = passiveDpsVector.begin(); it != passiveDpsVector.end(); ++it) {
	//for (auto passive : passiveDpsMap) {
		std::cout << "pointsAllocated " << pointsAllocated << ", dps " << std::get<0>(*it)
				<< " if passive " << STRINGS::PASSIVE_NAME_MAP.at(std::get<1>(*it)) << std::endl;
	}
	if (verbose >= 2) std::cout << "stack : " << counter << std::endl;

	// now check every starting from the worst
	std::map<double, std::pair<PASSIVE_NAME, PassiveCombination<PASSIVE_NAME>>> maybeNewPassiveMap{
		// somthing to always return, will be worse that anything
		std::make_pair(0, std::make_pair(PASSIVE_NAME::BASE_STATS, PassiveCombination<PASSIVE_NAME>())) 
	};
	bool substractOk = false;
	for (auto it = passiveDpsVector.rbegin(); it != passiveDpsVector.rend(); ++it) {
	//for (auto passive : passiveDpsMap) {
		if (substractOk)
			break;
		auto maybeCombo = combo;
		auto points = maybeCombo.getPassivePoints(std::get<1>(*it));
		maybeCombo.substractPassivePoint(std::get<1>(*it), passives.at(std::get<1>(*it)).getClass());
		auto r = dependencySatisfied(passives, maybeCombo, passiveDependencyCache);
		switch (r.first) {
			case DEPENDENCY_OK: {
				auto pair = findBestPassivesReverse(maybeCombo, pointsAllocated - 1);
				if (verbose >= 2) counter++;
				maybeNewPassiveMap.insert(std::make_pair(pair.second, std::make_pair(std::get<1>(*it), pair.first)));
				substractOk = true;
				if (verbose >= 2) std::cout << "pointsAllocated " << pointsAllocated
					<< ", substracted worst passive : " << STRINGS::PASSIVE_NAME_MAP.at(std::get<1>(*it)) << std::endl;
				break;
			}
			default: {
				continue; // shikanai
			}
			case DEPENDENCY_PARENT: {
				// someone blocks
				if (passives.at(r.second).getAbsoluteMinimum()) {
					if (verbose >= 2) std::cout << "pointsAllocated " << pointsAllocated << ", substract block : "
						<< STRINGS::PASSIVE_NAME_MAP.at(r.second) << " blocks " << STRINGS::PASSIVE_NAME_MAP.at(std::get<1>(*it)) << std::endl;
					continue; // shikanai
				}
				auto maybeCombo2 = combo;
				maybeCombo2.substractPassivePoint(r.second, passives.at(r.second).getClass());
				auto r1 = dependencySatisfied(passives, maybeCombo2, passiveDependencyCache);
				if (r1.first == DEPENDENCY_OK) {
					if (verbose >= 2) std::cout << "pointsAllocated " << pointsAllocated << ", substracted child : " << STRINGS::PASSIVE_NAME_MAP.at(r.second) << std::endl;
					auto pair = findBestPassivesReverse(maybeCombo2, pointsAllocated - 1, std::get<1>(*it));
					if (verbose >= 2) counter++;
					maybeNewPassiveMap.insert(std::make_pair(pair.second, std::make_pair(std::get<1>(*it), pair.first)));
				}
			}
		}
	}

	auto r = *maybeNewPassiveMap.rbegin(); // best result
	return std::make_pair(r.second.second, r.first);
}

double BuildMaker::statSum(std::map<STAT_NAME, std::vector<std::pair<std::string, double>>>& currentStats, STAT_NAME statName) {
	auto it = currentStats.find(statName);
	if (it == currentStats.end()) {
		if (verbose >= 2) std::cout << "Nothing with " << STRINGS::STAT_NAME_MAP.at(statName) << std::endl;
		return 0;
	}

	auto stats = it->second;
	
	double result = 0;
	bool first = true;
	for (auto stat : stats) {
		if (verbose >= 2) std::cout << (first ? "" : " + ") << stat.first << ":" << stat.second;
		result += stat.second;
		first = false;
	}
	if (verbose >= 2) std::cout << " = " << result << std::endl;
	//std::cout << std::endl << "TOTAL " << STRINGS::STAT_NAME_MAP.at(statName) << " = " << result << std::endl;
	return result;
}

double BuildMaker::statProduct(std::map<STAT_NAME, std::vector<std::pair<std::string, double>>>& currentStats, STAT_NAME statName) {
	auto it = currentStats.find(statName);
	if (it == currentStats.end()) {
		if (verbose >= 2) std::cout << "Nothing with " << STRINGS::STAT_NAME_MAP.at(statName) << std::endl;
		return 0;
	}

	auto stats = it->second;
	double result = 100;
	bool first = true;
	for (auto stat : stats) {
		if (verbose >= 2) std::cout << (first ? "" : " * ") << stat.first << ":" << (100+stat.second)/100;
		result *= (100+stat.second)/100;
		first = false;
	}
	if (verbose >= 2) std::cout << " = " << result << "%" << std::endl;
	//std::cout << std::endl << "TOTAL " << STRINGS::STAT_NAME_MAP.at(statName) << " = " << (result-100) << std::endl;
	return result - 100;
}

int BuildMaker::get_num_threads() {
	int num_threads = 1;
#pragma omp parallel
	{
#pragma omp single
		num_threads = omp_get_num_threads();
	}
	return num_threads;
}