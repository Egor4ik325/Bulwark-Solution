#include "Inventory.h"

#include "Global.h"
#include "UIManager.h"
#include "Content.h"
#include "Item.h"
#include "InventoryCell.h"

Inventory::Inventory(UIScreen* screenParent) : UIWindow(screenParent)
{
	// Name
	name = "Inventory";
	dragAble = true;
	titleVisible = false;
	bodyColor = sf::Color(256, 256, 256, 100);
	selectedCell = 0;

	createCells();
}

void Inventory::createCells()
{
	if (screenParent == nullptr) return;

	cellCount = 5;
	setSize(sf::Vector2f(cellCount * 64 + 64, 64));
	for (int i = 0; i < cellCount; i++)
		addCell();
}

void Inventory::addCell()
{
	InventoryCell* cell = new InventoryCell(this);
	(*cell).setPosition(cells.size() * (*cell).getSize().x, 0);
	cell->setScreenParent(this->screenParent);
	this->screenParent->addControl(cell);
	cells.push_back(cell);
}

bool Inventory::isDragAllow() const
{
	return UIDragable::isDragAllow();
}

void Inventory::update()
{
	if (screenParent == nullptr) return;
	UIWindow::update();

	for (int i = 0; i < cellCount; i++)
	{
		cells[i]->update();

		if (!cells[i]->isDragAllow())
			cells[i]->setPosition(getPosition() + sf::Vector2f(i * TILE_SIZE, 0));
	}
}

InventoryCell * Inventory::getFirstEmptyCell()
{
	for (InventoryCell* cell : cells)
	{
		if (cell->isEmpty())
			return cell;
	}
	
	return nullptr;
}

InventoryCell * Inventory::getSelectedCell()
{
	return getCell(selectedCell);
}

InventoryCell* Inventory::getCell(unsigned int index)
{
	if (index > cells.size())
		return nullptr;

	return cells[index];
}