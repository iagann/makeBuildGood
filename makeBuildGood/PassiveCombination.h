#pragma once

#include "enums.h"

#include <map>
#include <string>
#include <sstream>
#include <iostream>

template <typename T>
class PassiveCombination {
public:
	PassiveCombination()
		: prevComboId(0)
	{
		if (std::is_same<T, PASSIVE_NAME>::value) {
			lastAddedPassive = static_cast<T>(PASSIVE_NAME::BASE_STATS);
			pointsCountMap = { {PASSIVE_CLASS_NAME::BASE, 0}, {PASSIVE_CLASS_NAME::BLADEDANCER, 0}, {PASSIVE_CLASS_NAME::MARKSMAN, 0}, {PASSIVE_CLASS_NAME::FALCONER, 0} };
		}
		else if (std::is_same<T, SKILL_PASSIVE_NAME>::value) {
			lastAddedPassive = static_cast<T>(PASSIVE_NAME::BASE_STATS);
			pointsCountMap = { {PASSIVE_CLASS_NAME::BASE, 0} };
		}
		else {
			throw std::string("passive type not suported: ") + typeid(T).name();
		}
	}

	void addPassivePoint(T passiveName, PASSIVE_CLASS_NAME passiveClassName) {
		if (passives.count(passiveName) == 0) {
			passives.insert(std::make_pair(passiveName, 1));
			pointsCountMap.at(passiveClassName)++;
		}
		else {
			passives.at(passiveName)++;
			pointsCountMap.at(passiveClassName)++;
		}
	}
	void substractPassivePoint(T passiveName, PASSIVE_CLASS_NAME passiveClassName) {
		if (passives.at(passiveName) == 0)
			throw "no no";
		passives.at(passiveName)--;
		pointsCountMap.at(passiveClassName)--;
	}
	void setPassivePoints(T passiveName, PASSIVE_CLASS_NAME passiveClassName, unsigned int points) {
		auto it = passives.find(passiveName);
		if (it == passives.end()) {
			passives.insert(std::make_pair(passiveName, points));
			pointsCountMap.at(passiveClassName) += points;
		}
		else {
			pointsCountMap.at(passiveClassName) += points - passives.at(passiveName);
			passives.at(passiveName) = points;
		}
	}
	//unsigned int totalPoints();
	std::map<T, unsigned int> getPassives() { return passives; }
	unsigned int getPassivePoints(T passiveName) const {
		auto it = passives.find(passiveName);
		return (it != passives.end()) ? it->second : 0;
	}

	unsigned int totalPoints() const {
		unsigned int result = 0;
		for (auto p : pointsCountMap) {
			result += p.second;
		}
		return result;
	}

	unsigned int totalAbsoluteMinimum(std::map<T, Passive<T>>& universalPassives) {
		unsigned int result = 0;
		for (auto passive : passives) {
			result += universalPassives.at(passive.first).getAbsoluteMinimum();
		}
		return result;
	}

	std::string toString(std::map<T, std::string> universalStrings) {
		std::stringstream ss;
		bool first = true;
		//ss << prevComboId << ":" << universalStrings.at(lastAddedPassive) << ":" << (passives.at(lastAddedPassive) - 1) << "->" << passives.at(lastAddedPassive) << std::endl;
		for (auto& passive : passives) {
			ss << (first ? "" : ",") << universalStrings.at(passive.first) << "=" << passive.second;
			first = false;
		}
		//ss << std::endl << "---------------------------------------------------------------------------------------------------------------" << std::endl;
		//ss << "===============================================================================================================" << std::endl;
		return ss.str();
	}

	bool operator<(const PassiveCombination& other) const {
		return passives < other.passives;
	}

	bool operator==(const PassiveCombination& other) const {
		return passives == other.passives;
	}

	bool operator!=(const PassiveCombination& other) const {
		return passives != other.passives;
	}

	T lastAddedPassive;
	unsigned int prevComboId;
	std::map<PASSIVE_CLASS_NAME, unsigned int> pointsCountMap;

private:
	std::map<T, unsigned int> passives;
};