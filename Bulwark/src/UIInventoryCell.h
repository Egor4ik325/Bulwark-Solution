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
	
	sf::Color SelectedColor;
public:
	UIInventoryCell();
	UIInventoryCell(UIInventory* inv);

	void Update() override;
	void Draw(sf::RenderTarget& target) override;

	void SetItem(Item* item);	
	void RemoveItem();
	bool IsEmpty();
	Item* GetItem();
};

