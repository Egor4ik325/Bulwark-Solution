#include "UIInventory.h"

#include "Program.h"
#include "UIManager.h"
#include "Content.h"
#include "Item.h"
#include "UIInventoryCell.h"

UIInventory::UIInventory(UIScreen* screenParent) : UIWindow(screenParent)
{
	dragAble = true;
	titleVisible = false;
	bodyColor = sf::Color(256, 256, 256, 100);
	selectedCell = 0;

	if (screenParent != nullptr)
		createCells();
}

bool UIInventory::getDragAllow() const
{
	return UIBase::getDragAllow();
}

void UIInventory::update()
{
	if (screenParent == nullptr) return;
	UIWindow::update();

	for (int i = 0; i < cellCount; i++)
	{
		cells[i]->update();
		cells[i]->setPosition(rectShape.getPosition() + sf::Vector2f(i * TILE_SIZE,0));
	}
}

void UIInventory::createCells()
{
	cellCount = 5;
	rectShape.setSize(sf::Vector2f(cellCount * 64 + 64, 64));
	for (int i = 0; i < cellCount; i++)
		addCell();
}

void UIInventory::addCell()
{
	UIInventoryCell* cell = new UIInventoryCell(this);
	(*cell).setPosition(cells.size() * (*cell).getRectShape().getSize().x, 0);
	cell->setScreenParent(screenParent);

	cell->screenParent->addControl(cell);

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
	if (index > cells.size())
		return nullptr;

	return cells[index];
}