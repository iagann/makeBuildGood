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

#include <chrono>

class BuildMaker {
public:
	BuildMaker();
	void makeGoodBuild();
	bool tests();

	void addItemCandidate(Item item);

	void exportFile(const std::string& filename);
	bool importFile(const std::string& filename);

	bool stacks;
	bool reversePassiveSearch;
	bool disableCriticalVulnerability;
	bool allowSameItems;
	bool staticAerial;
	PassiveCombination<PASSIVE_NAME> realPassives;
private:
	enum IMPORT_STATE {
		IMPORT_STATE_GLOBAL,
		IMPORT_STATE_PASSIVES,
		IMPORT_STATE_SKILLS,
		IMPORT_STATE_ITEMS
	};

	int counter;
	unsigned int passivePoints;
	const int num_threads;
	bool imported;

	std::map<PASSIVE_NAME, Passive<PASSIVE_NAME>> passives;
	PassiveCombination<PASSIVE_NAME> bestPassives;
	PassiveCombination<PASSIVE_NAME> minimumPassives;
	std::map<PassiveCombination<PASSIVE_NAME>, std::pair<DEPENDENCY, PASSIVE_NAME>> passiveDependencyCache;
	

	std::map<SKILL_PASSIVE_NAME, Passive<SKILL_PASSIVE_NAME>> skills;
	std::vector<PassiveCombination<SKILL_PASSIVE_NAME>> skillSet;
	std::vector<PassiveCombination<SKILL_PASSIVE_NAME>> skillSetKestrel;
	PassiveCombination<SKILL_PASSIVE_NAME> currentSkills;
	PassiveCombination<SKILL_PASSIVE_NAME> bestSkills;

	ItemSet items;
	ItemSet currentItemSet;
	ItemSet bestItemSet;
	std::map<ITEM_TYPE, std::set<int>> usedItemsInit;

	double bestDps, currentDps;
	double lastCritChance;
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
			if (passive.second.getClass() == PASSIVE_CLASS_NAME::BASE)
				initCombo.setPassivePoints(passive.first, passive.second.getClass(), passive.second.getAbsoluteMinimum());
		}

		basePassiveCombinationSet.insert(initCombo);
		const unsigned int unsingnedBasePoints = 20 - initCombo.totalPoints() + initCombo.totalAbsoluteMinimum(passives);
		for (unsigned int i = 0; i < unsingnedBasePoints; ++i) {
			std::set<PassiveCombination<PASSIVE_NAME>> maybePassiveCombinationSet;
			for (auto passiveCombination : basePassiveCombinationSet) {
				for (auto maybeNewPassive : passives) {
					if (maybeNewPassive.second.getClass() != PASSIVE_CLASS_NAME::BASE)
						continue;
					PassiveCombination<PASSIVE_NAME> maybePassiveCombination = passiveCombination;
					maybePassiveCombination.addPassivePoint(maybeNewPassive.first, maybeNewPassive.second.getClass());
					if (dependencySatisfied(passives, maybePassiveCombination, passiveDependencyCache).first != DEPENDENCY_OK)
						continue;
					if(passiveCombinationOk(passives, maybePassiveCombination) == DEPENDENCY_OK)
						maybePassiveCombinationSet.insert(maybePassiveCombination);
				}
			}
			basePassiveCombinationSet = maybePassiveCombinationSet;
		}
		for (auto passive : passives) {
			if (passive.second.getClass() == PASSIVE_CLASS_NAME::BASE)
				result.setPassivePoints(passive.first, passive.second.getClass(), passive.second.getMaximumPoints());
			else
				result.setPassivePoints(passive.first, passive.second.getClass(), passive.second.getAbsoluteMinimum());
		}
		for (auto passiveCombination : basePassiveCombinationSet) {
			if (totalClassPoints(passiveCombination, PASSIVE_CLASS_NAME::BASE) < 20)
				continue;
			for (auto passive : passives) {
				if (passive.second.getClass() == PASSIVE_CLASS_NAME::BASE) {
					if (result.getPassivePoints(passive.first) > passiveCombination.getPassivePoints(passive.first)) {
						result.setPassivePoints(passive.first, passive.second.getClass(), passiveCombination.getPassivePoints(passive.first));
					}
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
		std::cout << combo.toString(universalStrings) << std::endl;
		/*
		for (auto passive : combo.getPassives()) {
			std::cout << universalStrings.at(passive.first) << " = " << passive.second << ", ";
		}
		std::cout << std::endl;
		*/
	}
	template <typename T>
	std::pair<DEPENDENCY, T> dependencySatisfied(std::map<T, Passive<T>>& universalPassives, PassiveCombination<T>& combo, T passiveName) {
		Passive<T>& passive = universalPassives.at(passiveName);
		if (!reversePassiveSearch)
			if (passive.getAbsoluteMinimum() > 0 && combo.getPassivePoints(passiveName) == passive.getAbsoluteMinimum() && combo.totalPoints() != passivePoints) {
				return std::make_pair(DEPENDENCY_OK, passiveName); // ignore all checks
			}
		if (combo.getPassivePoints(passiveName) > 0) {
			auto dependencies = passive.getDependencies();
			for (auto dependency : dependencies) {
				if (combo.getPassivePoints(dependency.first) < dependency.second) {
					return std::make_pair(DEPENDENCY_PARENT, passiveName);
				}
			}
		}
		return std::make_pair(DEPENDENCY_OK, passiveName);
	}
	template <typename T>
	std::pair<DEPENDENCY, T> dependencySatisfied(
		std::map<T, Passive<T>>& universalPassives,
		PassiveCombination<T>& combo,
		std::map<PassiveCombination<PASSIVE_NAME>, std::pair<DEPENDENCY, T>>& cache) {
		auto it = cache.find(combo);
		if (it != cache.end()) {
			//std::cout << "dependency cache used" << std::endl;
			return it->second;
		}

		for (auto passive : combo.getPassives()) {
			auto r = dependencySatisfied(passives, combo, passive.first);
			if (r.first != DEPENDENCY_OK) {
				cache.insert(std::make_pair(combo, r));
				return r;
			}
		}

		auto r1 = passiveCombinationOk(universalPassives, combo);
		if (r1 != DEPENDENCY_OK) {
			auto r2 = std::make_pair(r1, BASE_STATS);
			cache.insert(std::make_pair(combo, r2));
			return r2;
		}

		auto r2 = std::make_pair(DEPENDENCY_OK, BASE_STATS);
		cache.insert(std::make_pair(combo, r2));
		return r2;
	}
	template <typename T>
	DEPENDENCY passiveCombinationOk(std::map<T, Passive<T>>& universalPassives, PassiveCombination<T>& combo) {
		std::map<T, unsigned int> comboPassives = combo.getPassives();
		for (auto comboPassive : comboPassives) {
			if (comboPassive.second == 0)
				continue;

			Passive<T>& passive = universalPassives.at(comboPassive.first);

			// not over the maximum
			if (!reversePassiveSearch)
				if (comboPassive.second > passive.getMaximumPoints() && combo.totalPoints() != passivePoints)
					return DEPENDENCY_OVER_MAX;

			if (!reversePassiveSearch)
				if (passive.getAbsoluteMinimum() > 0 && combo.totalPoints() != passivePoints)
					continue; // ignore all remaining checks

			// enough points into class tree to take this passive
			auto minimumMastery = passive.getMinimumClassPoints(passive.getClass());
			auto actualMastery = totalClassPoints(combo, passive.getClass(), minimumMastery);
			if (actualMastery < minimumMastery) {
				return DEPENDENCY_MASTERY;
			}
			// mastery, also control 20 points in base
			if (passive.getClass() != PASSIVE_CLASS_NAME::BASE) {
				auto minimumClass = passive.getMinimumClassPoints(PASSIVE_CLASS_NAME::BASE);
				auto actualClass = totalClassPoints(combo, PASSIVE_CLASS_NAME::BASE);
				if (actualClass < minimumClass) {
					return DEPENDENCY_MASTERY;
				}
			}
		}
		return DEPENDENCY_OK;
	}
	template <typename T>
	unsigned int totalClassPoints(PassiveCombination<T>& combo, PASSIVE_CLASS_NAME className, int minimumMastery = 999) {
		unsigned int result = 0;
		for (auto passive : combo.getPassives()) {
			if (passives.at(passive.first).getClass() == className && passives.at(passive.first).getMinimumClassPoints(className) < minimumMastery)
				result += passive.second;
		}
		return result;
		return combo.pointsCountMap.at(className) - (std::is_same<T, SKILL_PASSIVE_NAME>::value ? 1 : 0);
	}

	double calculateDps();
	double calculateDpsIf(ItemSet ifItemSet);
	double calculateDpsIf(PassiveCombination<SKILL_PASSIVE_NAME> ifSkills);
	double calculateDpsIf(PassiveCombination<PASSIVE_NAME> ifPassives);
	void findBestItems();
	void findBestSkills();
	void findBestPassives();
	void findBestPassives(PassiveCombination<PASSIVE_NAME>& combo, int pointsLeft, double currentDpsCopy);
	std::pair<PassiveCombination<PASSIVE_NAME>, double> findBestPassivesReverse(PassiveCombination<PASSIVE_NAME>& combo, int pointsAllocated, PASSIVE_NAME limit = PASSIVE_NAME::BASE_STATS);
	double statSum(std::map<STAT_NAME, std::vector<std::pair<std::string, double>>>& currentStats, STAT_NAME statName);
	double statProduct(std::map<STAT_NAME, std::vector<std::pair<std::string, double>>>& currentStats, STAT_NAME statName);

	int get_num_threads();
};

#endif