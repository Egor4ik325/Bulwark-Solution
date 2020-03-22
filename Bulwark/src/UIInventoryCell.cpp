#include "UIInventoryCell.h"

#include "Program.h"
#include "Content.h"
#include "UIInventory.h"

UIInventoryCell::UIInventoryCell(UIInventory* inv) : UIBase(inv->screenParent)
{
	// Запоминаем родителя
	this->invParent = inv;
	// Хранимый предмет
	itemContain = nullptr;
	
	screenParent = invParent->screenParent;
	//
	selectedColor = sf::Color::Black;
	// Устанавливаем текстуру
	rectShape.setSize(sf::Vector2f(TILE_SIZE, TILE_SIZE));
	rectShape.setTexture(&ContentManager::invCellTexture, true);
	rectShape.setTextureRect(sf::IntRect(0, 0, 16, 16));
}

void UIInventoryCell::update()
{
	UIBase::update();

	if (itemContain != nullptr)
	{
		itemContain->setPosition(rectShape.getPosition());
	}
}

void UIInventoryCell::draw(sf::RenderTarget & target)
{
	if (invParent->getCell(invParent->selectedCell) == this)
		rectShape.setFillColor(selectedColor);
	else
		rectShape.setFillColor(sf::Color::White);

	UIBase::draw(target);
}

void UIInventoryCell::setItem(Item * item)
{
	itemContain = item;
	itemContain->onGround = false;
	itemContain->setPosition(getPosition());
}

void UIInventoryCell::removeItem()
{
	itemContain = nullptr;
}

bool UIInventoryCell::isEmpty()
{
	return itemContain == nullptr;
}

Item * UIInventoryCell::getItem()
{
	return itemContain;
}
