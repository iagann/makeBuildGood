#pragma once

#include "enums.h"

#include <map>
#include <vector>

template <typename T>
class Passive {
public:
	Passive(PASSIVE_CLASS_NAME passiveClassName_, unsigned int maxPoints_)
		: passiveClassName(passiveClassName_)
		, maxPoints(maxPoints_)
		, absoluteMinimum(0)
		, thresholdStatLimit(0)
		, thresholdStatValue(0)
		, enabled(true)
	{}

	Passive withThresholdStat(unsigned int limit, STAT_NAME stat, double value) {
		thresholdStatLimit = limit;
		thresholdStatName = stat;
		thresholdStatValue = value;
		return *this;
	}
	Passive withStat(STAT_NAME stat, double value) {
		stats.push_back(std::make_pair(stat, value));
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

	void disable() { enabled = false; }
	void enable() { enabled = true; }

	unsigned int getMaximumPoints() { return enabled ? maxPoints : 0; }
	unsigned int getAbsoluteMinimum() { return enabled ? absoluteMinimum : 0; }

	const std::vector<std::pair<STAT_NAME, double>> getStats(int points) {
		std::vector<std::pair<STAT_NAME, double>> result = stats;
		for (auto& stat : result)
			stat.second *= points;
		if (thresholdStatLimit > 0 && points >= thresholdStatLimit)
			result.push_back(std::make_pair(thresholdStatName, thresholdStatValue));
		return result;
	}
	const PASSIVE_CLASS_NAME getClass() { return passiveClassName; }
	unsigned int getMinimumClassPoints(PASSIVE_CLASS_NAME passiveClassName) {
		auto it = minimumClassPointsMap.find(passiveClassName);
		return (it != minimumClassPointsMap.end()) ? it->second : 0;
	}
	const std::map<T, unsigned int> getDependencies() { return dependMap; }
private:
	unsigned int maxPoints;
	unsigned int absoluteMinimum; // must be in the final result, but ignores dependency and skill point check

	std::vector<std::pair<STAT_NAME, double>> stats;
	unsigned int thresholdStatLimit;
	STAT_NAME thresholdStatName;
	double thresholdStatValue;
	PASSIVE_CLASS_NAME passiveClassName;
	std::map<PASSIVE_CLASS_NAME, unsigned int> minimumClassPointsMap;
	std::map<T, unsigned int> dependMap;

	bool enabled;
};