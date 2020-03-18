#include "ItemManager.h"
#include <iostream>
#include "Program.h"

std::vector <Item*> ItemManager::items;
ItemInfo ItemManager::ItemInfoArr[];

void ItemManager::AddItem(Item * item)
{
	items.push_back(item);
}

void ItemManager::Draw(sf::RenderTarget& target)
{
	for (Item* item : items)
	{
		(*item).Draw(target);
	}
}

Item* ItemManager::GetItem(int tileX, int tileY)
{
	for (Item* item : items)
	{
		sf::Vector2f pointPos(tileX * TILE_SIZE, tileY * TILE_SIZE);

		//sf::Vector2f itemCoords(item->GetGlobalPosition());
		//sf::FloatRect itemRect(itemPos, sf::Vector2f( TILE_SIZE, TILE_SIZE ));
		
		if (item->GetGlobalBounds().contains(pointPos))
			return item;
	}

	return nullptr;
}

Item * ItemManager::GetItem(sf::Vector2f pos)
{
	return GetItem(pos.x / TILE_SIZE, pos.y / TILE_SIZE);
}

void ItemManager::SetItemInfo(unsigned int id, const ItemInfo & info)
{
	ItemInfoArr[id] = info;
}

ItemInfo ItemManager::GetItemInfo(unsigned int id)
{
	if (id > 10) return ItemInfo();
	
	return ItemInfoArr[id];
}
