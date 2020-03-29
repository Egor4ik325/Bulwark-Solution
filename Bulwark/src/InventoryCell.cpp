#include "InventoryCell.h"
#include "Item.h"
#include "Global.h"
#include "Content.h"
#include "Inventory.h"

InventoryCell::InventoryCell(Inventory* inv) : UIDragable(inv->screenParent)
{
	// Name
	name = "InventoryCell";
	// Запоминаем родителя
	this->invParent = inv;
	// Хранимый предмет
	itemContain = nullptr;
	dragAble = true;
	
	screenParent = invParent->screenParent;
	//
	selectedColor = sf::Color::Black;
	// Устанавливаем текстуру
	setSize(sf::Vector2f(TILE_SIZE, TILE_SIZE));
	setTexture(&ContentManager::invCellTexture, true);
	setTextureRect(sf::IntRect(0, 0, 16, 16));
}

void InventoryCell::update()
{
	UIDragable::update();

	if (itemContain != nullptr)
	{
		// Двигаем Item внутри
		itemContain->setPosition(getPosition());
	}
}

void InventoryCell::draw(sf::RenderTarget & target)
{
	if (invParent->getCell(invParent->selectedCell) == this)
		setFillColor(selectedColor);
	else
		setFillColor(sf::Color::White);

	UIDragable::draw(target);
}

void InventoryCell::setItem(Item * item)
{
	itemContain = item;
	itemContain->onGround = false;
	itemContain->setPosition(getPosition());
}

void InventoryCell::removeItem()
{
	itemContain = nullptr;
}

bool InventoryCell::isEmpty()
{
	return itemContain == nullptr;
}

Item * InventoryCell::getItem()
{
	return itemContain;
}
