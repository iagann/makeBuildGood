#include "Item.h"

#include <iostream>

Item Item::withStat(STAT_NAME stat, double value) {
	stats.push_back(std::make_pair(stat, value));
	return *this;
}

bool Item::operator<(const Item& other) const {
	if (itemType != other.itemType)
		return itemType < other.itemType;
	if (name != other.name)
		return name < other.name;
	return stats < other.stats;
}
bool Item::operator==(const Item& other) const {
	return itemType == other.itemType && name == other.name &&  stats == other.stats;
}

ItemSet::ItemSet() {
	items = {
		{ HELM, std::vector<Item>()},
		{ AMULET, std::vector<Item>()},
		{ BOW, std::vector<Item>()},
		{ QUIVER, std::vector<Item>()},
		{ BODY, std::vector<Item>()},
		{ RING, std::vector<Item>()},
		{ BELT, std::vector<Item>()},
		{ GLOVES, std::vector<Item>()},
		{ BOOTS, std::vector<Item>()},
		{ RELIC, std::vector<Item>()},
		{ BIG_IDOL, std::vector<Item>()},
		{ SMALL_IDOL, std::vector<Item>()},
		{ BLESSING_BLACK_SUN, std::vector<Item>()},
		{ BLESSING_REIGN_OF_DRAGONS, std::vector<Item>()},
		{ BLESSING_SPIRITS_OF_FIRE, std::vector<Item>()},
		{ BLESSING_THE_AGE_OF_WINTER, std::vector<Item>()},
		{ BLESSING_ENDING_THE_STORM, std::vector<Item>()},
	};
}

std::vector<Item> ItemSet::getAllItems() {
	std::vector<Item> result;
	for (auto itemType : items) {
		auto itemsByType = getItems(itemType.first);
		result.insert(result.end(), itemsByType.begin(), itemsByType.end());
	}
	return result;
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

std::map<STAT_NAME, std::vector<double>> ItemSet::getAllStats() {
	std::map<STAT_NAME, std::vector<double>> result;
	for (auto item : items) {
		for (auto typedItem : item.second)
			for (auto stat : typedItem.getStats()) {
				auto it = result.find(stat.first);
				auto t = stat.first;
				auto t2 = stat.second;
				if (it == result.end())
					result.insert(std::make_pair(stat.first, std::vector<double>{stat.second}));
				else
					result.at(stat.first).push_back(stat.second);
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