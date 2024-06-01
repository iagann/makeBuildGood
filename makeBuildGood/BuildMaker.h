#pragma once

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
			currentItemSet.addItem(HELM_SLOT, *items.getItems(HELM_SLOT).begin());
			currentItemSet.addItem(AMULET_SLOT, *items.getItems(AMULET_SLOT).begin());
			currentItemSet.addItem(BOW_SLOT, *items.getItems(BOW_SLOT).begin());
			currentItemSet.addItem(QUIVER_SLOT, *items.getItems(QUIVER_SLOT).begin());
			currentItemSet.addItem(BODY_SLOT, *items.getItems(BODY_SLOT).begin());
			currentItemSet.addItem(RING_LEFT_SLOT, *items.getItems(RING_LEFT_SLOT).begin());
			currentItemSet.addItem(RING_RIGHT_SLOT, *items.getItems(RING_RIGHT_SLOT).begin());
			currentItemSet.addItem(BELT_SLOT, *items.getItems(BELT_SLOT).begin());
			currentItemSet.addItem(GLOVES_SLOT, *items.getItems(GLOVES_SLOT).begin());
			currentItemSet.addItem(BOOTS_SLOT, *items.getItems(BOOTS_SLOT).begin());
			currentItemSet.addItem(RELIC_SLOT, *items.getItems(RELIC_SLOT).begin());
			currentItemSet.addItem(BIG_IDOL_1_SLOT, *items.getItems(BIG_IDOL_1_SLOT).begin());
			currentItemSet.addItem(BIG_IDOL_2_SLOT, *items.getItems(BIG_IDOL_2_SLOT).begin());
			currentItemSet.addItem(BIG_IDOL_3_SLOT, *items.getItems(BIG_IDOL_3_SLOT).begin());
			currentItemSet.addItem(BIG_IDOL_4_SLOT, *items.getItems(BIG_IDOL_4_SLOT).begin());
			currentItemSet.addItem(SMALL_IDOL_1_SLOT, *items.getItems(SMALL_IDOL_1_SLOT).begin());
			currentItemSet.addItem(SMALL_IDOL_2_SLOT, *items.getItems(SMALL_IDOL_2_SLOT).begin());
			currentItemSet.addItem(SMALL_IDOL_3_SLOT, *items.getItems(SMALL_IDOL_3_SLOT).begin());
			currentItemSet.addItem(SMALL_IDOL_4_SLOT, *items.getItems(SMALL_IDOL_4_SLOT).begin());
			currentItemSet.addItem(BLESSING_BLACK_SUN_SLOT, *items.getItems(BLESSING_BLACK_SUN_SLOT).begin());
			currentItemSet.addItem(BLESSING_REIGN_OF_DRAGONS_SLOT, *items.getItems(BLESSING_REIGN_OF_DRAGONS_SLOT).begin());
			currentItemSet.addItem(BLESSING_SPIRITS_OF_FIRE_SLOT, *items.getItems(BLESSING_SPIRITS_OF_FIRE_SLOT).begin());
			currentItemSet.addItem(BLESSING_THE_AGE_OF_WINTER_SLOT, *items.getItems(BLESSING_THE_AGE_OF_WINTER_SLOT).begin());
			currentItemSet.addItem(BLESSING_ENDING_THE_STORM_SLOT, *items.getItems(BLESSING_ENDING_THE_STORM_SLOT).begin());
			bool isKestrel = currentItemSet.getAllStats().count(STAT_NAME::LEVEL_OF_BALLISTA) > 0 ? 25 : 24;
			currentSkills = isKestrel ? *skillSetKestrel.begin() : *skillSet.begin();
			currentPassives = calculatePassiveMinimums();
		}
		double prevDps = 0;
		currentDps = calculateDps();
		if (verbose >= 1) std::cout << "Current DPS: " << currentDps << std::endl;
		bestDps = currentDps;
		while (prevDps < bestDps) {
			prevDps = bestDps;
			findBestItems();
			findBestSkills();
			findBestPassives();
		}
	}
	bool tests();

	void addItemCandidate(Item item);
private:
	const unsigned int passivePoints = 113;

	std::map<PASSIVE_NAME, Passive<PASSIVE_NAME>> passives;
	PassiveCombination<PASSIVE_NAME> currentPassives;
	PassiveCombination<PASSIVE_NAME> bestPassives;

	std::map<SKILL_PASSIVE_NAME, Passive<SKILL_PASSIVE_NAME>> skills;
	std::set<PassiveCombination<SKILL_PASSIVE_NAME>> skillSet;
	std::set<PassiveCombination<SKILL_PASSIVE_NAME>> skillSetKestrel;
	PassiveCombination<SKILL_PASSIVE_NAME> currentSkills;
	PassiveCombination<SKILL_PASSIVE_NAME> bestSkills;

	ItemSet items;
	ItemSet currentItemSet;
	ItemSet bestItemSet;

	std::map<STAT_NAME, std::vector<std::pair<std::string, double>>> currentStats;
	double bestDps, currentDps;

	unsigned int verbose; // 0 - minimum, 1 - normal, 2 - detailed

	void init();
	void initPassives();
	void initSkills();
	PassiveCombination<PASSIVE_NAME> calculatePassiveMinimums() {
		auto result = PassiveCombination<PASSIVE_NAME>();
		return result;
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
			//printPassiveCombinationsSetCompact(maybePassiveCombinationSet);
			basePassiveCombinationSet = maybePassiveCombinationSet;
		}
		for (auto passive : passives) {
			result.setPassivePoints(passive.first, passive.second.getClass(), passive.second.getMaximumPoints());
		}
		for (auto passiveCombination : basePassiveCombinationSet) {
			if (totalClassPoints(passiveCombination, PASSIVE_CLASS_NAME::BASE) < 20)
				continue;
			for (auto passive : passives) {
				if (result.passivePoints(passive.first) > passiveCombination.passivePoints(passive.first)) {
					result.setPassivePoints(passive.first, passive.second.getClass(), passiveCombination.passivePoints(passive.first));
				}
			}
		}

		return result;
	}
	/*
	template <typename T>
	void calculatePassiveCombinations(std::map<T, Passive<T>> universalPassives, std::map<T, std::string> universalStrings, PassiveCombination<T> initCombo, PassiveCombination<T>& result) {
		int totalPoints;
		std::set<PassiveCombination<T>> universalPassiveConbinationSet;
		if (std::is_same<T, PASSIVE_NAME>::value) {
			totalPoints = passivePoints;
		}
		else if (std::is_same<T, SKILL_PASSIVE_NAME>::value) {
			bool isKestrel = currentItemSet.getAllStats().count(STAT_NAME::LEVEL_OF_BALLISTA) > 0 ? 25 : 24;
			totalPoints = (isKestrel > 0 ? 25 : 24) + 1; // + 1 for base skill stats
		}
		else {
			throw std::string("passive type not suported: ") + typeid(T).name();
		}

		for (auto passive : universalPassives) {
			initCombo.setPassivePoints(passive.first, passive.second.getClass(), passive.second.getAbsoluteMinimum());
		}

		universalPassiveConbinationSet.clear();
		universalPassiveConbinationSet.insert(initCombo);
		const unsigned int unsingnedPoints = totalPoints - initCombo.totalPoints();
		int numThreads = 1; // get_num_threads();
		std::cout << "Initial combination has: " << initCombo.totalPoints() << " points, " << unsingnedPoints << " points to spend" << std::endl;

		for (unsigned int i = 0; i < unsingnedPoints; ++i) {
			std::vector<std::set<PassiveCombination<T>>> maybePassiveCombinationSet(numThreads);
			std::vector<PassiveCombination<T>> passiveCombinationVector(universalPassiveConbinationSet.begin(), universalPassiveConbinationSet.end());
			//#pragma omp parallel for schedule(guided) //shared(passiveCombinationVector)
			for (int j = 0; j < passiveCombinationVector.size(); ++j) {
				auto passiveCombination = passiveCombinationVector[j];
				std::map<PASSIVE_CLASS_NAME, unsigned int> classPoints;
				if (std::is_same<T, PASSIVE_NAME>::value) {
					classPoints = {
						{ BASE, totalClassPoints(passiveCombination, BASE) },
						{ BLADEDANCER, totalClassPoints(passiveCombination, BLADEDANCER) },
						{ MARKSMAN, totalClassPoints(passiveCombination, MARKSMAN) },
						{ FALCONER, totalClassPoints(passiveCombination, FALCONER)},
					};
				}
				else if (std::is_same<T, SKILL_PASSIVE_NAME>::value) {
					classPoints = {
						{ BASE, totalClassPoints(passiveCombination, BASE) },
					};
				}
				else {
					throw std::string("passive type not suported: ") + typeid(T).name();
				}

				std::map<int, int> a;
				//for (auto passiveCombination : passiveCombinationSet) {
				PassiveCombination<T> maybePassiveCombination(passiveCombination);
				for (std::pair<const T, Passive<T>> maybeNewPassive : universalPassives) {
					// not enough mastery points to take this passive
					T maybeNewPassiveName = maybeNewPassive.first;
					if (classPoints.at(maybeNewPassive.second.getClass()) < maybeNewPassive.second.getMinimumClassPoints(maybeNewPassive.second.getClass()))
						continue;
					if (maybeNewPassive.second.getClass() != PASSIVE_CLASS_NAME::BASE) {
						if (classPoints.at(PASSIVE_CLASS_NAME::BASE) < maybeNewPassive.second.getMinimumClassPoints(PASSIVE_CLASS_NAME::BASE))
							continue;
					}
					maybePassiveCombination.addPassivePoint(maybeNewPassive.first, maybeNewPassive.second.getClass());
					if (!dependencySatisfied(universalPassives, maybePassiveCombination, maybeNewPassive.first)) {
						maybePassiveCombination.substractPassivePoint(maybeNewPassive.first, maybeNewPassive.second.getClass());
						continue;
					}
					if (passiveCombinationOk(universalPassives, maybePassiveCombination)) {
						maybePassiveCombination.prevComboId = j;
						maybePassiveCombination.lastAddedPassive = maybeNewPassive.first;
						maybePassiveCombinationSet[omp_get_thread_num()].insert(maybePassiveCombination);
					}
					maybePassiveCombination.substractPassivePoint(maybeNewPassive.first, maybeNewPassive.second.getClass());
				}
			}

			universalPassiveConbinationSet.clear();
			for (int j = 0; j < numThreads; ++j) {
				//std::cout << "Thread " << j << " found " << maybePassiveCombinationSet[j].size() << " combinatioins" << std::endl;
				universalPassiveConbinationSet.insert(maybePassiveCombinationSet[j].begin(), maybePassiveCombinationSet[j].end());
			}
			
			auto top = *universalPassiveConbinationSet.begin();
			universalPassiveConbinationSet.clear();
			universalPassiveConbinationSet.insert(top);
			
			//printPassiveCombinationsSet(passiveCombinationSet);
			//std::cout << "Iteration " << (i + 1) << "/" << unsingnedPoints << " combination count " << universalCombinationSet.size() << std::endl;
			//std::cout << "===============================================================================================================" << std::endl;
		}

		printPassiveCombinationsSet(universalStrings, universalPassiveConbinationSet);

		result = *universalPassiveConbinationSet.begin();

		//std::cout << "Total combinations: " << universalCombinationSet.size() << std::endl;
	}
	*/
	template <typename T>
	void printPassiveCombinationsSet(std::map<T, std::string> universalStrings, std::set<PassiveCombination<T>> comboSet) {
		unsigned int count = 0;
		std::set<int> a;
		for (auto it : a) {}
		for (auto passiveCombination : comboSet) {
			if (std::is_same<T, PASSIVE_NAME>::value) {
				std::cout << (count + 1) << ":" << passiveCombination.toString(universalStrings) << std::endl;
				std::cout
					<< STRINGS::PASSIVE_CLASS_NAME_MAP.at(PASSIVE_CLASS_NAME::BASE) << ":" << totalClassPoints(passiveCombination, PASSIVE_CLASS_NAME::BASE) << " "
					<< STRINGS::PASSIVE_CLASS_NAME_MAP.at(PASSIVE_CLASS_NAME::BLADEDANCER) << ":" << totalClassPoints(passiveCombination, PASSIVE_CLASS_NAME::BLADEDANCER) << " "
					<< STRINGS::PASSIVE_CLASS_NAME_MAP.at(PASSIVE_CLASS_NAME::MARKSMAN) << ":" << totalClassPoints(passiveCombination, PASSIVE_CLASS_NAME::MARKSMAN) << " "
					<< STRINGS::PASSIVE_CLASS_NAME_MAP.at(PASSIVE_CLASS_NAME::FALCONER) << ":" << totalClassPoints(passiveCombination, PASSIVE_CLASS_NAME::FALCONER)
					<< std::endl;
			}
			else if (std::is_same<T, SKILL_PASSIVE_NAME>::value) {
				std::cout << (count + 1) << ":" << passiveCombination.toString(universalStrings) << std::endl;
				std::cout
					<< "Total skill points :" << totalClassPoints(passiveCombination, PASSIVE_CLASS_NAME::BASE)
					<< std::endl;
			}
			else {
				throw std::string("passive type not suported: ") + typeid(T).name();
			}
		}
		std::cout << "===============================================================================================================" << std::endl;
	}
	template <typename T>
	bool dependencySatisfied(std::map<T, Passive<T>> universalPassives, PassiveCombination<T>& combo, T passiveName) {
		Passive<T>& passive = universalPassives.at(passiveName);
		if (combo.passivePoints(passiveName) == passive.getAbsoluteMinimum())
			return true; // ignore all checks
		auto dependencies = passive.getDependencies();
		for (auto dependency : dependencies) {
			if (combo.passivePoints(dependency.first) < dependency.second)
				return false;
		}
		return true;
	}
	template <typename T>
	bool passiveCombinationOk(std::map<T, Passive<T>> universalPassives, PassiveCombination<T>& combo) {
		std::map<T, unsigned int>& comboPassives = combo.getPassives();
		for (auto comboPassive : comboPassives) {
			if (comboPassive.second == 0)
				continue;

			Passive<T>& passive = universalPassives.at(comboPassive.first);

			// not over the maximum
			if (comboPassive.second > passive.getMaximumPoints())
				return false;

			if (passive.getAbsoluteMinimum() > 0)
				continue; // ignore all remaining checks

			// enough points into class tree to take this passive
			auto minimumMastery = passive.getMinimumClassPoints(passive.getClass());
			auto actualMastery = totalClassPoints(combo, passive.getClass());
			if (actualMastery < minimumMastery)
				return false;
			// mastery, also control 20 points in base
			if (passive.getClass() != PASSIVE_CLASS_NAME::BASE) {
				auto minimumClass = passive.getMinimumClassPoints(PASSIVE_CLASS_NAME::BASE);
				auto actualClass = totalClassPoints(combo, PASSIVE_CLASS_NAME::BASE);
				if (actualClass < minimumClass)
					return false;
			}
		}
		return true;
	}
	template <typename T>
	unsigned int totalClassPoints(PassiveCombination<T>& combo, PASSIVE_CLASS_NAME className) {
		return combo.pointsCountMap.at(className);
	}
	unsigned int totalAbsoluteMinimum();

	double calculateDps();
	double calculateDpsIf(ItemSet ifItemSet);
	double calculateDpsIf(PassiveCombination<SKILL_PASSIVE_NAME> ifSkills);
	double calculateDpsIf(PassiveCombination<PASSIVE_NAME> ifPassives);
	void findBestItems();
	void findBestSkills();
	void findBestPassives();
	double statSum(STAT_NAME statName);
	double statProduct(STAT_NAME statName);

	int get_num_threads();
};