#pragma once
#include "Item.h"
#include <vector>


// Хранит характеристику предмета
struct ItemInfo
{
	unsigned int maxCount;
};

class ItemManager
{
private:
	static std::vector <Item*> items;

	static ItemInfo ItemInfoArr[10];

public:

	static void Draw(sf::RenderTarget &target);
	static void AddItem(Item* item);	

	static Item* GetItem(int tileX, int tileY);
	static Item* GetItem(sf::Vector2f pos);

	static void SetItemInfo(unsigned int id, const ItemInfo& info);
	static ItemInfo GetItemInfo(unsigned int id);

};
