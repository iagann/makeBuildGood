#include "Item.h"

#include <iostream>
#include <sstream>

Item Item::withStat(STAT_NAME stat, double value) {
	stats.push_back(std::make_pair(stat, value));
	return *this;
}

std::string Item::toString() {
	std::stringstream ss;
	ss << getName() << " (" << STRINGS::ITEM_TYPE_MAP.at(getType()) << "): ";
	bool first = true;
	for (auto stat : stats) {
		if (!first)
			ss << ", ";
		ss << STRINGS::STAT_NAME_MAP.at(stat.first) << " = " << stat.second;
		first = false;
	}
	return ss.str();
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
		{ HELM_SLOT, std::vector<Item>()},
		{ AMULET_SLOT, std::vector<Item>()},
		{ BOW_SLOT, std::vector<Item>()},
		{ QUIVER_SLOT, std::vector<Item>()},
		{ BODY_SLOT, std::vector<Item>()},
		{ RING_LEFT_SLOT, std::vector<Item>()},
		{ RING_RIGHT_SLOT, std::vector<Item>()},
		{ BELT_SLOT, std::vector<Item>()},
		{ GLOVES_SLOT, std::vector<Item>()},
		{ BOOTS_SLOT, std::vector<Item>()},
		{ RELIC_SLOT, std::vector<Item>()},
		{ BIG_IDOL_1_SLOT, std::vector<Item>()}, { BIG_IDOL_2_SLOT, std::vector<Item>()}, { BIG_IDOL_3_SLOT, std::vector<Item>()}, { BIG_IDOL_4_SLOT, std::vector<Item>()},
		{ SMALL_IDOL_1_SLOT, std::vector<Item>()}, { SMALL_IDOL_2_SLOT, std::vector<Item>()}, { SMALL_IDOL_3_SLOT, std::vector<Item>()}, { SMALL_IDOL_4_SLOT, std::vector<Item>()},
		{ BLESSING_BLACK_SUN_SLOT, std::vector<Item>()},
		{ BLESSING_REIGN_OF_DRAGONS_SLOT, std::vector<Item>()},
		{ BLESSING_SPIRITS_OF_FIRE_SLOT, std::vector<Item>()},
		{ BLESSING_THE_AGE_OF_WINTER_SLOT, std::vector<Item>()},
		{ BLESSING_ENDING_THE_STORM_SLOT, std::vector<Item>()},
	};
}

std::vector<Item> ItemSet::getAllItems() {
	std::vector<Item> result;
	for (auto itemSlot : items) {
		auto itemsByType = getItems(itemSlot.first);
		result.insert(result.end(), itemsByType.begin(), itemsByType.end());
	}
	return result;
}

std::map<ITEM_SLOT, Item> ItemSet::getItemSet() {
	std::map<ITEM_SLOT, Item> result;
	for (auto slot : items) {
		result.insert(std::make_pair(slot.first, slot.second.at(0)));
	}
	return result;
}

bool ItemSet::hasEmpty() {
	for (auto slot : items) {
		if (slot.second.empty()) {
			std::cout << STRINGS::ITEM_SLOT_MAP.at(slot.first) << " is missing from the item set, cannot make a build" << std::endl;
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