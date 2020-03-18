#pragma once
#include "Item.h"
#include <vector>


// ������ �������������� ��������
struct ItemInfo
{
	unsigned int maxCount;
};

class ItemManager
{
private:
	static std::vector <Item*> items;

	static ItemInfo itemInfoArr[10];

public:

	static void draw(sf::RenderTarget &target);
	static void addItem(Item* item);	

	static Item* getItem(int tileX, int tileY);
	static Item* getItem(sf::Vector2f pos);

	static void setItemInfo(unsigned int id, const ItemInfo& info);
	static ItemInfo getItemInfo(unsigned int id);

};
