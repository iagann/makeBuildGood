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

	bool operator<(const Item& other) const;
	bool operator==(const Item& other) const;
private:
	ITEM_TYPE itemType;
	std::string name;
	std::vector<std::pair<STAT_NAME, double>> stats;
};

class ItemSet {
public:
	ItemSet();
	void addItem(Item item) { items.at(item.getType()).push_back(item); }
	std::vector<Item>& getItems(ITEM_TYPE type) { return items.at(type); }
	std::vector<Item> getAllItems();
	bool hasEmpty();
	void clear() { for (auto itemType : items) itemType.second.clear(); }
	std::map<STAT_NAME, std::vector<double>> getAllStats();

	bool operator<(const ItemSet& other) const;
	bool operator==(const ItemSet& other) const;
private:
	std::map<ITEM_TYPE, std::vector<Item>> items;
};
