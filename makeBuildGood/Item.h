#pragma once

#include "enums.h"

#include <map>
#include <vector>

class Item {
public:
	Item(ITEM_TYPE itemType_, std::string name_)
		: itemType(itemType_), name(name_)
	{}

	Item withStat(STAT_NAME stat, double value);
	std::vector<std::pair<STAT_NAME, double>> getStats() { return stats; }
	const ITEM_TYPE getType() { return itemType; }
	const std::string getName() { return name; }
	std::string toString();

	bool operator<(const Item& other) const;
	bool operator==(const Item& other) const;
	bool operator!=(const Item& other) const { return !this->operator==(other); }
private:
	ITEM_TYPE itemType;
	std::string name;
	std::vector<std::pair<STAT_NAME, double>> stats;
};

class ItemSet {
public:
	ItemSet();
	void addItem(ITEM_SLOT slot, Item item) { items.at(slot).push_back(item); }
	std::vector<Item>& getItems(ITEM_SLOT slot) { return items.at(slot); }
	std::vector<Item> getAllItems();
	int hasItem(ITEM_SLOT slot) { return items.at(slot).size(); }
	Item getItem(ITEM_SLOT slot) { return items.at(slot).at(0); }
	std::map<ITEM_SLOT, Item> getItemSet();
	std::map<ITEM_SLOT, std::vector<Item>> getAllItemSet() { return items; }
	void changeItem(ITEM_SLOT slot, Item item) { items.at(slot) = std::vector<Item>{ item }; }
	void unequipItem(ITEM_SLOT slot) { items.at(slot).clear(); }
	void clear() { for (auto itemType : items) itemType.second.clear(); }
	std::map<STAT_NAME, std::vector<double>> getAllStats();

	bool operator<(const ItemSet& other) const;
	bool operator==(const ItemSet& other) const;
private:
	std::map<ITEM_SLOT, std::vector<Item>> items;
};
