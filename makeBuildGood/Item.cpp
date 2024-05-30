#include "Item.h"

#include <iostream>

Item Item::withStat(STAT_NAME stat, double value) {
	statsMap.insert(std::make_pair(stat, value));
	return *this;
}

bool Item::operator<(const Item& other) const {
	if (itemType != other.itemType)
		return itemType < other.itemType;
	if (name != other.name)
		return name < other.name;
	return statsMap < other.statsMap;
}
bool Item::operator==(const Item& other) const {
	return itemType == other.itemType && name == other.name &&  statsMap == other.statsMap;
}

ItemSet::ItemSet() {
	items = {
		{ HELM, std::set<Item>()},
		{ AMULET, std::set<Item>()},
		{ BOW, std::set<Item>()},
		{ QUIVER, std::set<Item>()},
		{ BODY, std::set<Item>()},
		{ RING, std::set<Item>()},
		{ BELT, std::set<Item>()},
		{ GLOVES, std::set<Item>()},
		{ BOOTS, std::set<Item>()},
		{ RELIC, std::set<Item>()},
		{ BIG_IDOL, std::set<Item>()},
		{ SMALL_IDOL, std::set<Item>()},
		{ BLESSING_BLACK_SUN, std::set<Item>()},
		{ BLESSING_REIGN_OF_DRAGONS, std::set<Item>()},
		{ BLESSING_SPIRITS_OF_FIRE, std::set<Item>()},
		{ BLESSING_THE_AGE_OF_WINTER, std::set<Item>()},
		{ BLESSING_ENDING_THE_STORM, std::set<Item>()},
	};
}

bool ItemSet::hasEmpty() {
	for (auto itemType : items) {
		if (itemType.second.empty()) {
			std::cout << STRINGS::ITEM_TYPE_MAP.at(itemType.first) << " is missing from the item set, cannot make a build" << std::endl;
			return true;
		}
	}
	return false;
}

std::map<STAT_NAME, std::set<double>> ItemSet::getAllStats() {
	std::map<STAT_NAME, std::set<double>> result;
	for (auto item : items) {
		for (auto typedItem : item.second)
			for (auto stat : typedItem.getStats()) {
				auto it = result.find(stat.first);
				auto t = stat.first;
				auto t2 = stat.second;
				if (it == result.end())
					result.insert(std::make_pair(stat.first, std::set<double>{stat.second}));
				else
					result.at(stat.first).insert(stat.second);
			}
	}
	return result;
}

bool ItemSet::operator<(const ItemSet& other) const {
	return items < other.items;
}
bool ItemSet::operator==(const ItemSet& other) const {
	return items == other.items;
}