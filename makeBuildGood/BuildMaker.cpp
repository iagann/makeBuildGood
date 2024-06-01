#include "BuildMaker.h"
#include "PassiveCombination.h"

#include <iostream>
#include <iomanip>
#include <cmath>

#include <set>


BuildMaker::BuildMaker() {
	init();
	verbose = 1;
}

void BuildMaker::init() {
	initPassives();
	initSkills();
}

void BuildMaker::initPassives() {
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
		.withStat(STAT_NAME::INCREASED_CRITICAL_STRIKE_CHANCE, 5)
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
		.withAbsoluteMinimum(5)
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
		.withAbsoluteMinimum(5)
	));
	passives.insert(std::make_pair(
		PASSIVE_NAME::EXPEDIENCY, Passive<PASSIVE_NAME>(PASSIVE_CLASS_NAME::FALCONER, 5)
		.withMinimumClassPoints(PASSIVE_CLASS_NAME::FALCONER, 40)
		.withAbsoluteMinimum(5)
	));
	passives.insert(std::make_pair(
		PASSIVE_NAME::FINESSE_THEM, Passive<PASSIVE_NAME>(PASSIVE_CLASS_NAME::FALCONER, 7)
		.withStat(STAT_NAME::CRITICAL_STRIKE_AVOIDANCE, 5)
		.withThresholdStat(0, STAT_NAME::INCREASED_MINION_CRITICAL_STRIKE_MULTIPLIER_PER_CRITICAL_STRIKE_AVOIDANCE, 1.5)
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
	skillSet.insert(shared1);
	shared1.setPassivePoints(SKILL_PASSIVE_NAME::ELIXIR_OF_CONSTRUCTION, PASSIVE_CLASS_NAME::BASE, 5); // 2
	skillSetKestrel.insert(shared1);

	auto shared2 = initCombo;
	shared2.setPassivePoints(SKILL_PASSIVE_NAME::RAPID_FIRE, PASSIVE_CLASS_NAME::BASE, 2); // 1
	shared2.setPassivePoints(SKILL_PASSIVE_NAME::CONTAMINATING_SHOTS, PASSIVE_CLASS_NAME::BASE, 2); //2
	skillSet.insert(shared2);
	shared2.setPassivePoints(SKILL_PASSIVE_NAME::ELIXIR_OF_CONSTRUCTION, PASSIVE_CLASS_NAME::BASE, 4); // 1
	skillSetKestrel.insert(shared2);

	auto shared0 = initCombo;
	shared0.setPassivePoints(SKILL_PASSIVE_NAME::ELIXIR_OF_CONSTRUCTION, PASSIVE_CLASS_NAME::BASE, 5); //2
	shared0.setPassivePoints(SKILL_PASSIVE_NAME::HEAVY_BOLTS, PASSIVE_CLASS_NAME::BASE, 1); // 1
	skillSet.insert(shared0);
	shared0.setPassivePoints(SKILL_PASSIVE_NAME::HEAVY_BOLTS, PASSIVE_CLASS_NAME::BASE, 0); // 0
	shared0.setPassivePoints(SKILL_PASSIVE_NAME::LIGHT_BOLTS, PASSIVE_CLASS_NAME::BASE, 2); // 1
	skillSet.insert(shared0);
	shared0.setPassivePoints(SKILL_PASSIVE_NAME::HEAVY_BOLTS, PASSIVE_CLASS_NAME::BASE, 1); // 1
	skillSetKestrel.insert(shared0);
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

unsigned int BuildMaker::totalAbsoluteMinimum() {
	unsigned int result = 0;
	for (auto passive : passives) {
		result += passive.second.getAbsoluteMinimum();
	}
	return result;
}

double BuildMaker::calculateDps() {
	return calculateDpsIf(currentItemSet);
}

double BuildMaker::calculateDpsIf(ItemSet ifItemSet) {
	return calculateDpsIf(currentSkills);
}

double BuildMaker::calculateDpsIf(PassiveCombination<SKILL_PASSIVE_NAME> ifSkills) {
	return calculateDpsIf(currentPassives);
}

double BuildMaker::calculateDpsIf(PassiveCombination<PASSIVE_NAME> ifPassives) {
	currentStats.clear();
	// PASSIVES
	{
		for (auto passive : currentPassives.getPassives()) {
			if (passive.first == PURSUIT)
				int fdsf = 1;
			auto passiveDefinition = passives.at(passive.first);
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
		for (auto item : currentItemSet.getAllItems()) {
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
		double dex = statSum(DEXTERITY);
		if (verbose >= 2) std::cout << "DEXTERITY: " << dex << std::endl << std::endl;

		double damageRatio = statSum(DAMAGE_STAT_RATIO) / 100;
		if (verbose >= 2) std::cout << "SHARED DAMAGE RATIO: " << (damageRatio * 100) << "%" << std::endl;
		double flatPhys = statSum(FLAT_MINION_PHYSICAL_DAMAGE) + statSum(FLAT_PHYSICAL_DAMAGE) * damageRatio;
		flatPhys *= 2;
		if (verbose >= 2) std::cout << "FLAT PHYSICAL DAMAGE: " << flatPhys << std::endl;
		double flatCold = (dex * statSum(FLAT_COLD_PER_DEX)) * damageRatio;
		flatCold *= 2;
		if (verbose >= 2) std::cout << "FLAT COLD DAMAGE: " << flatCold << std::endl;
		double flatLight = statSum(FLAT_LIGHTNING_DAMAGE) * damageRatio;
		flatLight *= 2;
		if (verbose >= 2) std::cout << "FLAT LIGHTNING DAMAGE: " << flatLight << std::endl << std::endl;

		double addedflatPhysFalcon = statSum(FLAT_MINION_PHYSICAL_DAMAGE_FALCON);
		if (verbose >= 2) std::cout << "ADDED FLAT PHYSICAL DAMAGE FALCON: " << addedflatPhysFalcon << std::endl;
		double flatPhysFalcon = 30 + addedflatPhysFalcon * 1.5;
		if (verbose >= 2) std::cout << "ATTACK FLAT PHYSICAL DAMAGE FALCON: " << flatPhysFalcon << std::endl;
		double flatPhysDiveBomb = 170 + addedflatPhysFalcon * 8.5 + 80 + addedflatPhysFalcon * 4; // + feather
		if (verbose >= 2) std::cout << "DIVE BOMB PHYSICAL DAMAGE FALCON: " << flatPhysDiveBomb << std::endl << std::endl;

		double increasedAttackSpeed1 = statSum(INCREASED_ATTACK_SPEED);
		if (verbose >= 2) std::cout << "INCREASED ATTACK SPEED FROM ITEMS: " << increasedAttackSpeed1 << std::endl;
		double increasedAttackSpeed2 = statSum(INCREASED_ATTACK_SPEED_PER_DEXTERITY) * dex;
		if (verbose >= 2) std::cout << "INCREASED ATTACK SPEED FROM DEXTERITY: " << increasedAttackSpeed2 << std::endl;
		double increasedAttackSpeed = increasedAttackSpeed1 + increasedAttackSpeed2;
		if (verbose >= 2) std::cout << "INCREASED ATTACK SPEED: " << increasedAttackSpeed << std::endl;
		double moreAttackSpeed = statProduct(MORE_ATTACK_SPEED);
		if (verbose >= 2) std::cout << "MORE ATTACK SPEED: " << moreAttackSpeed << "%" << std::endl;
		double hitsPerSecond = 6 * 0.717 * (100 + increasedAttackSpeed) / 100 * (100 + moreAttackSpeed) / 100;
		if (verbose >= 2) std::cout << "BALLISTA HITS PER SECOND: " << hitsPerSecond << std::endl;
		double hitsPerSecondFalcon = 1.257 * 1.2 * 1.16;
		if (verbose >= 2) std::cout << "FALCON HITS PER SECOND: " << hitsPerSecondFalcon << std::endl << std::endl;
		double hitsPerSecondDiveBomb = (1.0 + 0.12 * 4) / 5;
		if (verbose >= 2) std::cout << "DIVE BOMB HITS PER SECOND: " << hitsPerSecondDiveBomb << std::endl << std::endl;

		double increasedDamagePerDex = dex * statSum(INCREASED_MINION_DAMAGE_PER_DEXTERITY);
		if (verbose >= 2) std::cout << "INCREASED DAMAGE PER DEXTERITY: " << increasedDamagePerDex << std::endl;
		double increasedDamagePerMs = statSum(INCREASED_MOVEMENT_SPEED) * statSum(INCREASED_DAMAGE_PER_MOVEMENT_SPEED);
		if (verbose >= 2) std::cout << "INCREASED DAMAGE PER MOVEMENT SPEED: " << increasedDamagePerMs << std::endl;
		double increasedDamage = statSum(INCREASED_MINION_DAMAGE) + (statSum(INCREASED_DAMAGE) + increasedDamagePerMs) * damageRatio + increasedDamagePerDex;
		if (verbose >= 2) std::cout << "INCREASED DAMAGE: " << increasedDamage << std::endl;
		double increasedDamageFalcon = statSum(INCREASED_MINION_DAMAGE) + (statSum(INCREASED_DAMAGE) + increasedDamagePerMs) * 0.75 + increasedDamagePerDex;
		if (verbose >= 2) std::cout << "INCREASED DAMAGE FALCON: " << increasedDamageFalcon << std::endl;
		double increasedMinionPhys = statSum(INCREASED_MINION_PHYSICAL_DAMAGE) + statSum(INCREASED_PHYSICAL_DAMAGE) * damageRatio / 100;
		if (verbose >= 2) std::cout << "INCREASED MINION PHYSICAL DAMAGE: " << increasedMinionPhys << std::endl;
		double increasedCold = statSum(INCREASED_COLD_DAMAGE) * damageRatio / 100;
		if (verbose >= 2) std::cout << "INCREASED COLD DAMAGE: " << increasedCold << std::endl;
		double intelligence = statSum(INTELLIGENCE);
		if (verbose >= 2) std::cout << "INTELLIGENCE: " << intelligence << std::endl;
		double moreDamage = (100 + statProduct(MORE_DAMAGE)) / 100 * (100 + intelligence * statSum(MORE_DAMAGE_PER_INTELLIGENCE));
		if (verbose >= 2) std::cout << "MORE DAMAGE: " << moreDamage << "%" << std::endl;
		double moreDamageFalcon = (1.75 * 2 * (dex + 100) / 100 * 1.15 * 1.1) * 100;
		if (verbose >= 2) std::cout << "MORE DAMAGE FALCON: " << moreDamageFalcon << "%" << std::endl << std::endl;
		double moreDamageDiveBomb = ((moreDamageFalcon + 100) / 100 * (1 + 0.04 * 4) * (1 + 0.04 * 4)) * 100;
		if (verbose >= 2) std::cout << "MORE DAMAGE DIVE BOMB: " << moreDamageDiveBomb << "%" << std::endl << std::endl;

		double ailmentRatio = statSum(AILMENT_STAT_RATIO) / 100 + 0.25;
		if (verbose >= 2) std::cout << "SHARED AILMENTS RATIO: " << (ailmentRatio * 100) << "%" << std::endl;
		double averageStacks = 4 * (ailmentRatio * hitsPerSecond + 2 * hitsPerSecondFalcon) / 100;
		if (verbose >= 2) std::cout << "AVERAGE AILMENT STACKS FOR 1% chance: " << averageStacks << std::endl;
		double critVulnerabilityChance = statSum(CRITICAL_VULNERABILITY_CHANCE);
		if (verbose >= 2) std::cout << "CHANCE TO APPLY CRIT VULNERABILITY: " << critVulnerabilityChance << "%" << std::endl;
		double averageCritVulnerabilityStacks = std::min<double>(10, averageStacks * critVulnerabilityChance + hitsPerSecondDiveBomb * 4 * 3);
		if (verbose >= 2) std::cout << "AVERAGE CRIT VULNERABILITY STACKS: " << averageCritVulnerabilityStacks << std::endl;
		double physShredChance = statSum(CHANCE_TO_SHRED_PHYS_RES);
		if (verbose >= 2) std::cout << "CHANCE TO SHRED PHYSICAL RESISTANCE: " << physShredChance << "%" << std::endl;
		double averagePhysShredStacks = std::min<double>(10, averageStacks * physShredChance + hitsPerSecondDiveBomb * 4 * 5);
		if (verbose >= 2) std::cout << "AVERAGE PHYSICAL SHRED STACKS: " << averagePhysShredStacks << std::endl;
		double physPen = statSum(PHYSICAL_PENETRATION) + averagePhysShredStacks * 2;
		if (verbose >= 2) std::cout << "TOTAL PHYSICAL PENETRATION: " << physPen << "%" << std::endl;
		double lightShredChance = statSum(CHANCE_TO_SHRED_LIGHTNING_RES);
		if (verbose >= 2) std::cout << "CHANCE TO SHRED LIGHTNING RESISTANCE: " << lightShredChance << "%" << std::endl;
		double averageLightShredStacks = std::min<double>(10, averageStacks * lightShredChance);
		if (verbose >= 2) std::cout << "AVERAGE LIGHTNING SHRED STACKS: " << averageLightShredStacks << std::endl;
		double shockChance = statSum(SHOCK_CHANCE);
		if (verbose >= 2) std::cout << "CHANCE TO SHOCK: " << shockChance << "%" << std::endl;
		double averageShockStacks = std::min<double>(10, averageStacks * shockChance);
		if (verbose >= 2) std::cout << "AVERAGE SHOCK STACKS: " << averageShockStacks << std::endl;
		double armourShredChance = statSum(ARMOUR_SHRED_CHANCE);
		if (verbose >= 2) std::cout << "CHANCE TO SHRED ARMOUR: " << armourShredChance << "%" << std::endl;
		double armourShredEffect = statSum(ARMOUR_SHRED_EFFECT);
		if (verbose >= 2) std::cout << "ARMOUR SHRED EFFECT (ONLY BALLISTAS, NO FALCON): " << armourShredEffect << "%" << std::endl;
		double averageArmourShred = 4 * (ailmentRatio * hitsPerSecond * (100 + armourShredEffect) / 100 + 2 * hitsPerSecondFalcon) * (armourShredChance + hitsPerSecondDiveBomb * 2);
		if (verbose >= 2) std::cout << "AVERAGE ARMOUR SHRED: " << averageArmourShred << std::endl;
		double physArmorShredMore = 100 * (1.2 * averageArmourShred / (80 + 0.05 * pow(105, 2) + 1.2 * averageArmourShred) * 0.3
			+ 0.0012 * pow(averageArmourShred, 2) / (180 * 105 + 0.0015 * pow(averageArmourShred, 2)) * 0.55);
		if (verbose >= 2) std::cout << "AVERAGE MORE PHYCICAL DAMAGE FROM ARMOUR SHRED: " << physArmorShredMore << "%" << std::endl;
		double otherArmorShredMore = physArmorShredMore * 0.7;
		if (verbose >= 2) std::cout << "AVERAGE MORE OTHER DAMAGE FROM ARMOUR SHRED: " << otherArmorShredMore << "%" << std::endl << std::endl;

		double critRatio = statSum(CRITICAL_STAT_RATIO) / 100;
		if (verbose >= 2) std::cout << "SHARED CRIT RATIO: " << (critRatio * 100) << "%" << std::endl;
		double baseCritMinion = statSum(BASE_MINION_CRITICAL_STRIKE_CHANCE);
		if (verbose >= 2) std::cout << "BASE MINION CRIT: " << baseCritMinion << "%" << std::endl;
		double baseCritOwn = statSum(BASE_CRITICAL_STRIKE_CHANCE);
		if (verbose >= 2) std::cout << "BASE OWN CRIT: " << baseCritOwn << "%" << std::endl;
		double baseCrit = baseCritMinion + baseCritOwn * critRatio;
		if (verbose >= 2) std::cout << "BASE CRIT: " << baseCrit << "%" << std::endl;
		double increasedCritChanceOwn = statSum(INCREASED_CRITICAL_STRIKE_CHANCE);
		if (verbose >= 2) std::cout << "INCREASED CRIT CHANCE OWN: " << increasedCritChanceOwn << "%" << std::endl;
		double increasedCritChanceMinions = statSum(INCREASED_MINION_CRITICAL_STRIKE_CHANCE);
		if (verbose >= 2) std::cout << "INCREASED CRIT CHANCE MINIONS: " << increasedCritChanceMinions << "%" << std::endl;
		double increasedCritChance = increasedCritChanceOwn * critRatio + increasedCritChanceMinions;
		if (verbose >= 2) std::cout << "INCREASED CRIT CHANCE TOTAL: " << increasedCritChance << "%" << std::endl;
		double increasedCritChanceFalcon = increasedCritChanceOwn * 0.75 + increasedCritChanceMinions;
		if (verbose >= 2) std::cout << "INCREASED CRIT CHANCE TOTAL FALCON: " << increasedCritChanceFalcon << "%" << std::endl;
		double increasedCritMultiOwn = statSum(INCREASED_CRITICAL_STRIKE_MULTIPLIER);
		if (verbose >= 2) std::cout << "INCREASED CRIT MULTI OWN: " << increasedCritMultiOwn << "%" << std::endl;
		double increasedCritMultiMinions = statSum(INCREASED_MINION_CRITICAL_STRIKE_MULTIPLIER);
		if (verbose >= 2) std::cout << "INCREASED CRIT MULTI MINIONS: " << increasedCritMultiMinions << "%" << std::endl;
		double criticalStrikeAvoidance = statSum(CRITICAL_STRIKE_AVOIDANCE);
		if (verbose >= 2) std::cout << "CRITICAL STRIKE AVOIDANCE: " << criticalStrikeAvoidance << "%" << std::endl;
		double criticalStrikeAvoidanceMulti = criticalStrikeAvoidance * statSum(INCREASED_MINION_CRITICAL_STRIKE_MULTIPLIER_PER_CRITICAL_STRIKE_AVOIDANCE);
		if (verbose >= 2) std::cout << "CRITICAL STRIKE AVOIDANCE CRIT MULTI: " << criticalStrikeAvoidanceMulti << "%" << std::endl;
		double totalCritMulti = increasedCritMultiOwn * critRatio + increasedCritMultiMinions + criticalStrikeAvoidanceMulti;
		if (verbose >= 2) std::cout << "CRIT MULTI TOTAL: " << totalCritMulti << "%" << std::endl;
		double uncappedCritChance = baseCrit * (100 + increasedCritChance) / 100 + averageCritVulnerabilityStacks * 2;
		if (verbose >= 2) std::cout << "UNCAPPED CRIT CHANCE: " << uncappedCritChance << "%" << std::endl;
		double cappedCritChance = std::min<double>(uncappedCritChance, 100) / 100;
		if (verbose >= 2) std::cout << "CAPPED CRIT CHANCE: " << (cappedCritChance * 100) << "%" << std::endl;
		double effectiveCritMulti = cappedCritChance * totalCritMulti + 1 - cappedCritChance;
		if (verbose >= 2) std::cout << "EFFECTIVE CRIT MULTI: " << effectiveCritMulti << "%" << std::endl;
		double totalCritMultiFalcon = increasedCritMultiMinions + criticalStrikeAvoidanceMulti;
		if (verbose >= 2) std::cout << "CRIT MULTI TOTAL FALCON: " << totalCritMultiFalcon << "%" << std::endl;
		double uncappedCritChanceFalcon = baseCrit * (100 + increasedCritChanceFalcon) / 100 + averageCritVulnerabilityStacks * 2;
		if (verbose >= 2) std::cout << "UNCAPPED CRIT CHANCE FALCON: " << uncappedCritChanceFalcon << "%" << std::endl;
		double cappedCritChanceFalcon = std::min<double>(uncappedCritChanceFalcon, 100) / 100;
		if (verbose >= 2) std::cout << "CAPPED CRIT CHANCE FALCON: " << (cappedCritChanceFalcon * 100) << "%" << std::endl;
		double effectiveCritMultiFalcon = cappedCritChanceFalcon * totalCritMulti + 1 - cappedCritChanceFalcon;
		if (verbose >= 2) std::cout << "EFFECTIVE CRIT MULTI FALCON: " << effectiveCritMulti << "%" << std::endl << std::endl;

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
		return dps;
	}
}

void BuildMaker::findBestItems() {

}

void BuildMaker::findBestSkills() {

}

void BuildMaker::findBestPassives() {

}

double BuildMaker::statSum(STAT_NAME statName) {
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

double BuildMaker::statProduct(STAT_NAME statName) {
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