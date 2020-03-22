#pragma once
#include <SFML/Graphics.hpp>

#include "UIBase.h"
#include "Item.h"

class UIInventory;

class UIInventoryCell : public UIBase
{
public:
	Item* itemContain;

	UIInventory* invParent;
	
	sf::Color selectedColor;
public:
	UIInventoryCell(UIInventory* inventoryParent);

	void update() override;
	void draw(sf::RenderTarget& target) override;

	void setItem(Item* item);	
	void removeItem();
	bool isEmpty();
	Item* getItem();
};

