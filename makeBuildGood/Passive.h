#pragma once

#include "enums.h"

#include <map>

template <typename T>
class Passive {
public:
	Passive(PASSIVE_CLASS_NAME passiveClassName_, unsigned int maxPoints_)
		: passiveClassName(passiveClassName_)
		, maxPoints(maxPoints_)
		, absoluteMinimum(0)
		, thresholdStatLimit(0)
		, thresholdStatValue(0)
	{}

	Passive withThresholdStat(unsigned int limit, STAT_NAME stat, double value) {
		thresholdStatLimit = limit;
		thresholdStatName = stat;
		thresholdStatValue = value;
		return *this;
	}
	Passive withStat(STAT_NAME stat, double value) {
		statsMap.insert(std::make_pair(stat, value));
		return *this;
	}
	Passive withMinimumClassPoints(PASSIVE_CLASS_NAME passiveClassName_, unsigned int points) {
		minimumClassPointsMap.insert(std::make_pair(passiveClassName_, points));
		if (passiveClassName_ != PASSIVE_CLASS_NAME::BASE)
			withMinimumClassPoints(PASSIVE_CLASS_NAME::BASE, 20);
		return *this;
	}
	Passive withDependency(T name, unsigned int points) {
		dependMap.insert(std::make_pair(name, points));
		return *this;
	}
	Passive withAbsoluteMinimum(unsigned int points) {
		absoluteMinimum = points;
		return *this;
	}

	unsigned int getMaximumPoints() { return maxPoints; }
	unsigned int getAbsoluteMinimum() { return absoluteMinimum; }
	const std::map<STAT_NAME, double> getStats() { return statsMap; }
	const PASSIVE_CLASS_NAME getClass() { return passiveClassName; }
	unsigned int getMinimumClassPoints(PASSIVE_CLASS_NAME passiveClassName) {
		auto it = minimumClassPointsMap.find(passiveClassName);
		return (it != minimumClassPointsMap.end()) ? it->second : 0;
	}
	const std::map<T, unsigned int> getDependencies() { return dependMap; }
private:
	unsigned int maxPoints;
	unsigned int absoluteMinimum; // must be in the final result, but ignores dependency and skill point check

	std::map<STAT_NAME, double> statsMap;
	unsigned int thresholdStatLimit;
	STAT_NAME thresholdStatName;
	double thresholdStatValue;
	PASSIVE_CLASS_NAME passiveClassName;
	std::map<PASSIVE_CLASS_NAME, unsigned int> minimumClassPointsMap;
	std::map<T, unsigned int> dependMap;
};