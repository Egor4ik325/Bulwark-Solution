#pragma once
#include <SFML/Graphics.hpp>
#include "UIDragable.h"


class Inventory;
class Item;

class InventoryCell : public UIDragable
{
public:
	Item* itemContain;

	Inventory* invParent;
	
	sf::Color selectedColor;
public:
	InventoryCell(Inventory* inventoryParent);

	void update() override;
	void draw(sf::RenderTarget& target) override;

	void setItem(Item* item);	
	void removeItem();
	bool isEmpty();
	Item* getItem();
};

