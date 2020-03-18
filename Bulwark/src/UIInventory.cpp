#include "UIInventory.h"

#include "Program.h"
#include "UIManager.h"
#include "Content.h"
#include "Item.h"
#include "UIInventoryCell.h"

UIInventory::UIInventory()
{
}

void UIInventory::construct()
{ 
	DragAble = true;
	titleVisible = false;
	bodyColor = sf::Color(256, 256, 256, 100);

	cellCount = 5;
	rectShape.setSize(sf::Vector2f(cellCount * 64 + 64, 64));
	for (int i = 0; i < cellCount; i++)
		addCell();

	selectedCell = 0;
}

bool UIInventory::getDragAllow()
{
	return UIBase::getDragAllow();
}

void UIInventory::update()
{
	UIWindow::update();

	for (int i = 0; i < cellCount; i++)
	{
		UIInventoryCell* cell = cells[i];

		cell->update();
		cell->setPosition(rectShape.getPosition() + sf::Vector2f(i * TILE_SIZE,0));
	}
}

void UIInventory::pickUp()
{
}

void UIInventory::drop()
{
}

void UIInventory::addCell()
{
	UIInventoryCell* cell = new UIInventoryCell(this);
	(*cell).setPosition(cells.size() * (*cell).getRectShape()->getSize().x, 0);
	cell->setScreenParent(screenParent);
	UIManager::addControl(0, cell);
    cells.push_back(cell);
}
UIInventoryCell * UIInventory::getFirstEmptyCell()
{
	for (UIInventoryCell* cell : cells)
	{
		if (cell->isEmpty())
			return cell;
	}
	
	return nullptr;
}
UIInventoryCell * UIInventory::getSelectedCell()
{
	return getCell(selectedCell);
}
UIInventoryCell* UIInventory::getCell(unsigned int index)
{
	if (index < cells.size())
		return cells[index];

	return nullptr;
}