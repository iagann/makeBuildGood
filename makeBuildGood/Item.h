#pragma once

#include "enums.h"

#include <map>
#include <set>

class Item {
public:
	Item(ITEM_TYPE itemType_, std::string name_)
		: itemType(itemType_), name(name_)
	{}

	Item withStat(STAT_NAME stat, double value);
	const std::map<STAT_NAME, double> getStats() { return statsMap; }
	const ITEM_TYPE getType() { return itemType; }
	const std::string getName() { return name; }

	bool operator<(const Item& other) const;
	bool operator==(const Item& other) const;
private:
	ITEM_TYPE itemType;
	std::string name;
	std::map<STAT_NAME, double> statsMap;
};

class ItemSet {
public:
	ItemSet();
	void addItem(Item item) { items.at(item.getType()).insert(item); }
	std::set<Item>& getItems(ITEM_TYPE type) { return items.at(type); }
	bool hasEmpty();
	std::map<STAT_NAME, std::set<double>> getAllStats();

	bool operator<(const ItemSet& other) const;
	bool operator==(const ItemSet& other) const;
private:
	std::map<ITEM_TYPE, std::set<Item>> items;
};
