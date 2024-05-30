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
		if (itemSet.hasEmpty()) {
			std::cout << "Failed to make a build" << std::endl;
			return;
		}

		// literally anything
		ItemSet currentSet;
		currentSet.addItem(*itemSet.getItems(ITEM_TYPE::HELM).begin());
		currentSet.addItem(*itemSet.getItems(ITEM_TYPE::AMULET).begin());
		currentSet.addItem(*itemSet.getItems(ITEM_TYPE::BOW).begin());
		currentSet.addItem(*itemSet.getItems(ITEM_TYPE::QUIVER).begin());
		currentSet.addItem(*itemSet.getItems(ITEM_TYPE::BODY).begin());
		currentSet.addItem(*itemSet.getItems(ITEM_TYPE::RING).begin());
		currentSet.addItem(*itemSet.getItems(ITEM_TYPE::RING).begin());
		currentSet.addItem(*itemSet.getItems(ITEM_TYPE::BELT).begin());
		currentSet.addItem(*itemSet.getItems(ITEM_TYPE::GLOVES).begin());
		currentSet.addItem(*itemSet.getItems(ITEM_TYPE::BOOTS).begin());
		currentSet.addItem(*itemSet.getItems(ITEM_TYPE::RELIC).begin());
		currentSet.addItem(*itemSet.getItems(ITEM_TYPE::BIG_IDOL).begin());
		currentSet.addItem(*itemSet.getItems(ITEM_TYPE::BIG_IDOL).begin());
		currentSet.addItem(*itemSet.getItems(ITEM_TYPE::BIG_IDOL).begin());
		currentSet.addItem(*itemSet.getItems(ITEM_TYPE::BIG_IDOL).begin());
		currentSet.addItem(*itemSet.getItems(ITEM_TYPE::SMALL_IDOL).begin());
		currentSet.addItem(*itemSet.getItems(ITEM_TYPE::SMALL_IDOL).begin());
		currentSet.addItem(*itemSet.getItems(ITEM_TYPE::SMALL_IDOL).begin());
		currentSet.addItem(*itemSet.getItems(ITEM_TYPE::SMALL_IDOL).begin());

		calculatePassiveCombinations<SKILL_PASSIVE_NAME>(skills, STRINGS::SKILL_PASSIVE_NAME_MAP, PassiveCombination<SKILL_PASSIVE_NAME>());
		//calculatePassiveCombinations<PASSIVE_NAME>(passives, calculatePassiveMinimums());
	}
	bool tests();

	void addItemCandidate(Item item) { itemSet.addItem(item); }
private:
	const unsigned int passivePoints = 113;
	//const unsigned int passivePoints = 92;

	std::map<PASSIVE_NAME, Passive<PASSIVE_NAME>> passives;
	std::set<PassiveCombination<PASSIVE_NAME>> universalCombinationSet;

	std::map<SKILL_PASSIVE_NAME, Passive<SKILL_PASSIVE_NAME>> skills;
	std::set<PassiveCombination<SKILL_PASSIVE_NAME>> skillSet;
	std::set<PassiveCombination<SKILL_PASSIVE_NAME>> skillSetKestrel;

	ItemSet itemSet;
	ItemSet currentTtemSet;

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

	template <typename T>
	void calculatePassiveCombinations(std::map<T, Passive<T>> universalPassives, std::map<T, std::string> universalStrings, PassiveCombination<T> initCombo) {
		std::set<PassiveCombination<T>> universalCombinationSet;
		int totalPoints;
		if (std::is_same<T, PASSIVE_NAME>::value) {
			totalPoints = passivePoints;
		}
		else if (std::is_same<T, SKILL_PASSIVE_NAME>::value) {
			bool isKestrel = currentTtemSet.getAllStats().count(STAT_NAME::LEVEL_OF_BALLISTA) > 0 ? 25 : 24;
			for (auto passive : universalPassives) {
				initCombo.setPassivePoints(passive.first, passive.second.getClass(), passive.second.getAbsoluteMinimum());
			}
			totalPoints = isKestrel > 0 ? 25 : 24;
		}
		else {
			throw std::string("passive type not suported: ") + typeid(T).name();
		}

		universalCombinationSet.clear();
		universalCombinationSet.insert(initCombo);
		const unsigned int unsingnedPoints = totalPoints - initCombo.totalPoints();
		int numThreads = 1; // get_num_threads();
		std::cout << "Initial combination has: " << initCombo.totalPoints() << " points, " << unsingnedPoints << " points to spend" << std::endl;

		for (unsigned int i = 0; i < unsingnedPoints; ++i) {
			std::vector<std::set<PassiveCombination<T>>> maybePassiveCombinationSet(numThreads);
			std::vector<PassiveCombination<T>> passiveCombinationVector(universalCombinationSet.begin(), universalCombinationSet.end());
			//#pragma omp parallel for schedule(guided) /*shared(passiveCombinationVector)*/
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

			universalCombinationSet.clear();
			for (int j = 0; j < numThreads; ++j) {
				//std::cout << "Thread " << j << " found " << maybePassiveCombinationSet[j].size() << " combinatioins" << std::endl;
				universalCombinationSet.insert(maybePassiveCombinationSet[j].begin(), maybePassiveCombinationSet[j].end());
			}
			/*
			auto top = *universalCombinationSet.begin();
			universalCombinationSet.clear();
			universalCombinationSet.insert(top);
			*/
			//printPassiveCombinationsSet(passiveCombinationSet);
			std::cout << "Iteration " << (i + 1) << "/" << unsingnedPoints
				<< " combination count " << universalCombinationSet.size() << std::endl;
			std::cout << "===============================================================================================================" << std::endl;
		}

		printPassiveCombinationsSet(universalStrings, universalCombinationSet);

		std::cout << "Total combinations: " << universalCombinationSet.size() << std::endl;
	}
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

	int get_num_threads();
};