#ifndef BUILD_MAKER
#define BUILD_MAKER

#include "enums.h"
#include "Passive.h"
#include "PassiveCombination.h"
#include "Item.h"

#include <map>
#include <set>
#include <vector>

#include <omp.h>

class BuildMaker {
public:
	BuildMaker();
	void makeGoodBuild() {
		// control item sets
		if (items.hasEmpty()) {
			std::cout << "Failed to make a build" << std::endl;
			return;
		}

		// literally anything
		{
			std::cout << "Generating initial build to start with" << std::endl;
			currentItemSet.clear();
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
			bool isKestrel = currentItemSet.getAllStats().count(STAT_NAME::LEVEL_OF_BALLISTA) > 0 ? 25 : 24;
			currentSkills = isKestrel ? *skillSetKestrel.begin() : *skillSet.begin();
			minimumPassives = calculatePassiveMinimums();
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
			if (verbose >= 1) std::cout << "FINDING BEST BUILD, iteration " << iteration++ << std::endl;
			prevDps = bestDps;
			findBestItems();
		}
		if (verbose >= 1) std::cout << std::endl << "NOTHING BETTER FOUND!" << std::endl;

		std::cout << std::endl<< "BEST BUILD:" << std::endl;
		//verbose = 2;
		//calculateDps();

		for (auto item : bestItemSet.getAllItems()) {
			std::cout << item.toString() << std::endl;
		}
		std::cout << std::endl;
		printPassiveCombination(STRINGS::PASSIVE_NAME_MAP, bestPassives);
		std::cout << std::endl;
		printPassiveCombination(STRINGS::SKILL_PASSIVE_NAME_MAP, bestSkills);
		std::cout << std::endl << "DPS: " << bestDps << std::endl;
	}
	bool tests();

	void addItemCandidate(Item item);

	bool stacks;
private:
	const unsigned int passivePoints = 113;

	std::map<PASSIVE_NAME, Passive<PASSIVE_NAME>> passives;
	PassiveCombination<PASSIVE_NAME> bestPassives;
	PassiveCombination<PASSIVE_NAME> minimumPassives;
	std::map<PassiveCombination<PASSIVE_NAME>, bool> passiveDependencyCache;

	std::map<SKILL_PASSIVE_NAME, Passive<SKILL_PASSIVE_NAME>> skills;
	std::vector<PassiveCombination<SKILL_PASSIVE_NAME>> skillSet;
	std::vector<PassiveCombination<SKILL_PASSIVE_NAME>> skillSetKestrel;
	PassiveCombination<SKILL_PASSIVE_NAME> currentSkills;
	PassiveCombination<SKILL_PASSIVE_NAME> bestSkills;

	ItemSet items;
	ItemSet currentItemSet;
	ItemSet bestItemSet;

	std::map<STAT_NAME, std::vector<std::pair<std::string, double>>> currentStats;
	double bestDps, currentDps;
	bool bestDpsFound;
	std::map<ItemSet, double> dpsCacheItems;
	std::map<std::pair<ItemSet, PassiveCombination<SKILL_PASSIVE_NAME>>, double> dpsCacheSkills;

	unsigned int verbose; // 0 - minimum, 1 - normal, 2 - detailed

	void init();
	void initPassives();
	void initSkills();
	PassiveCombination<PASSIVE_NAME> calculatePassiveMinimums() {
		auto result = PassiveCombination<PASSIVE_NAME>();
		// base
		std::set<PassiveCombination<PASSIVE_NAME>> basePassiveCombinationSet;
		auto initCombo = PassiveCombination<PASSIVE_NAME>();
		for (auto passive : passives) {
			initCombo.setPassivePoints(passive.first, passive.second.getClass(), passive.second.getAbsoluteMinimum());
		}

		basePassiveCombinationSet.insert(initCombo);
		const unsigned int unsingnedBasePoints = 20 - initCombo.totalPoints() + totalAbsoluteMinimum();
		for (unsigned int i = 0; i < unsingnedBasePoints; ++i) {
			std::set<PassiveCombination<PASSIVE_NAME>> maybePassiveCombinationSet;
			for (auto passiveCombination : basePassiveCombinationSet) {
				for (auto maybeNewPassive : passives) {
					if (maybeNewPassive.second.getClass() != PASSIVE_CLASS_NAME::BASE)
						continue;
					PassiveCombination<PASSIVE_NAME> maybePassiveCombination = passiveCombination;
					maybePassiveCombination.addPassivePoint(maybeNewPassive.first, maybeNewPassive.second.getClass());
					if (!dependencySatisfied(passives, maybePassiveCombination, maybeNewPassive.first))
						continue;
					if (passiveCombinationOk(passives, maybePassiveCombination))
						maybePassiveCombinationSet.insert(maybePassiveCombination);
				}
			}
			basePassiveCombinationSet = maybePassiveCombinationSet;
		}
		for (auto passive : passives) {
			result.setPassivePoints(passive.first, passive.second.getClass(), passive.second.getMaximumPoints());
		}
		for (auto passiveCombination : basePassiveCombinationSet) {
			if (totalClassPoints(passiveCombination, PASSIVE_CLASS_NAME::BASE, 999) < 20)
				continue;
			for (auto passive : passives) {
				if (result.getPassivePoints(passive.first) > passiveCombination.getPassivePoints(passive.first)) {
					result.setPassivePoints(passive.first, passive.second.getClass(), passiveCombination.getPassivePoints(passive.first));
				}
			}
		}

		return result;
	}
	template <typename T>
	void printPassiveCombinationsSet(std::map<T, std::string> universalStrings, std::set<PassiveCombination<T>> comboSet) {
		unsigned int count = 0;
		for (auto combo : comboSet) {
			if (std::is_same<T, PASSIVE_NAME>::value) {
				std::cout << (count + 1) << ":" << combo.toString(universalStrings) << std::endl;
				std::cout
					<< STRINGS::PASSIVE_CLASS_NAME_MAP.at(PASSIVE_CLASS_NAME::BASE) << ":" << totalClassPoints(combo, PASSIVE_CLASS_NAME::BASE) << " "
					<< STRINGS::PASSIVE_CLASS_NAME_MAP.at(PASSIVE_CLASS_NAME::BLADEDANCER) << ":" << totalClassPoints(combo, PASSIVE_CLASS_NAME::BLADEDANCER) << " "
					<< STRINGS::PASSIVE_CLASS_NAME_MAP.at(PASSIVE_CLASS_NAME::MARKSMAN) << ":" << totalClassPoints(combo, PASSIVE_CLASS_NAME::MARKSMAN) << " "
					<< STRINGS::PASSIVE_CLASS_NAME_MAP.at(PASSIVE_CLASS_NAME::FALCONER) << ":" << totalClassPoints(combo, PASSIVE_CLASS_NAME::FALCONER)
					<< std::endl;
			}
			else if (std::is_same<T, SKILL_PASSIVE_NAME>::value) {
				std::cout << (count + 1) << ":" << combo.toString(universalStrings) << std::endl;
				std::cout
					<< "Total skill points :" << totalClassPoints(combo, PASSIVE_CLASS_NAME::BASE)
					<< std::endl;
			}
			else {
				throw std::string("passive type not suported: ") + typeid(T).name();
			}
			printPassiveCombination(combo);
		}
		std::cout << "===============================================================================================================" << std::endl;
	}
	template <typename T>
	void printPassiveCombination(std::map<T, std::string> universalStrings, PassiveCombination<T> combo) {
		for (auto passive : combo.getPassives()) {
			std::cout << universalStrings.at(passive.first) << " = " << passive.second << std::endl;
		}
	}
	template <typename T>
	bool dependencySatisfied(std::map<T, Passive<T>>& universalPassives, PassiveCombination<T>& combo, T passiveName) {
		Passive<T>& passive = universalPassives.at(passiveName);
		if (passive.getAbsoluteMinimum() > 0 && combo.getPassivePoints(passiveName) == passive.getAbsoluteMinimum() && combo.totalPoints() != passivePoints) {
			return true; // ignore all checks
		}
		auto dependencies = passive.getDependencies();
		for (auto dependency : dependencies) {
			if (combo.getPassivePoints(dependency.first) < dependency.second) {
				return false;
			}
		}
		return true;
	}
	template <typename T>
	bool dependencySatisfied(std::map<T, Passive<T>>& universalPassives, PassiveCombination<T>& combo, std::map<PassiveCombination<PASSIVE_NAME>, bool>& cache) {
		auto it = cache.find(combo);
		if (it != cache.end()) {
			//std::cout << "dependency cache used" << std::endl;
			return it->second;
		}

		for (auto passive : combo.getPassives()) {
			if (!dependencySatisfied(passives, combo, passive.first)) {
				cache.insert(std::make_pair(combo, false));
				return false;
			}
		}

		if (!passiveCombinationOk(universalPassives, combo)) {
			cache.insert(std::make_pair(combo, false));
			return false;
		}

		cache.insert(std::make_pair(combo, true));
		return true;
	}
	template <typename T>
	bool passiveCombinationOk(std::map<T, Passive<T>>& universalPassives, PassiveCombination<T>& combo) {
		std::map<T, unsigned int> comboPassives = combo.getPassives();
		for (auto comboPassive : comboPassives) {
			if (comboPassive.second == 0)
				continue;

			Passive<T>& passive = universalPassives.at(comboPassive.first);

			// not over the maximum
			if (comboPassive.second > passive.getMaximumPoints() && combo.totalPoints() != passivePoints)
				return false;

			if (passive.getAbsoluteMinimum() > 0 && combo.totalPoints() != passivePoints)
				continue; // ignore all remaining checks

			// enough points into class tree to take this passive
			auto minimumMastery = passive.getMinimumClassPoints(passive.getClass());
			auto actualMastery = totalClassPoints(combo, passive.getClass(), minimumMastery);
			if (actualMastery < minimumMastery) {
				return false;
			}
			// mastery, also control 20 points in base
			if (passive.getClass() != PASSIVE_CLASS_NAME::BASE) {
				auto minimumClass = passive.getMinimumClassPoints(PASSIVE_CLASS_NAME::BASE);
				auto actualClass = totalClassPoints(combo, PASSIVE_CLASS_NAME::BASE, 999);
				if (actualClass < minimumClass) {
					return false;
				}
			}
		}
		return true;
	}
	template <typename T>
	unsigned int totalClassPoints(PassiveCombination<T>& combo, PASSIVE_CLASS_NAME className, int minimumMastery) {
		unsigned int result = 0;
		for (auto passive : combo.getPassives()) {
			if (passives.at(passive.first).getClass() == className && passives.at(passive.first).getMinimumClassPoints(className) < minimumMastery)
				result += passive.second;
		}
		return result;
		return combo.pointsCountMap.at(className) - (std::is_same<T, SKILL_PASSIVE_NAME>::value ? 1 : 0);
	}
	unsigned int totalAbsoluteMinimum();

	double calculateDps();
	double calculateDpsIf(ItemSet ifItemSet);
	double calculateDpsIf(PassiveCombination<SKILL_PASSIVE_NAME> ifSkills);
	double calculateDpsIf(PassiveCombination<PASSIVE_NAME> ifPassives);
	void findBestItems();
	void findBestSkills();
	void findBestPassives();
	void findBestPassives(PassiveCombination<PASSIVE_NAME> &combo, int pointsLeft, double currentDpsCopy);
	double statSum(STAT_NAME statName);
	double statProduct(STAT_NAME statName);

	int get_num_threads();
};

#endif