#include "UIInventory.h"

#include "Program.h"
#include "UIManager.h"
#include "Content.h"
#include "Item.h"
#include "UIInventoryCell.h"

UIInventory::UIInventory()
{
}

void UIInventory::Construct()
{ 
	DragAble = true;
	TitleVisible = false;
	BodyColor = sf::Color(256, 256, 256, 100);

	cellCount = 5;
	rectShape.setSize(sf::Vector2f(cellCount * 64 + 64, 64));
	for (int i = 0; i < cellCount; i++)
		AddCell();

	selectedCell = 0;
}

bool UIInventory::GetDragAllow()
{
	return UIBase::GetDragAllow();
}

void UIInventory::Update()
{
	UIWindow::Update();

	for (int i = 0; i < cellCount; i++)
	{
		UIInventoryCell* cell = cells[i];

		cell->Update();
		cell->setPosition(rectShape.getPosition() + sf::Vector2f(i * TILE_SIZE,0));
	}
}

void UIInventory::PickUp()
{
}

void UIInventory::Drop()
{
}

void UIInventory::AddCell()
{
	UIInventoryCell* cell = new UIInventoryCell(this);
	(*cell).setPosition(cells.size() * (*cell).GetRectShape()->getSize().x, 0);
	cell->setScreenParent(screenParent);
	UIManager::AddControl(0, cell);
    cells.push_back(cell);
}
UIInventoryCell * UIInventory::GetEmptyCell()
{
	for (UIInventoryCell* cell : cells)
	{
		if (cell->IsEmpty())
			return cell;
	}
	
	return nullptr;
}
UIInventoryCell * UIInventory::GetSelectedCell()
{
	return GetCell(selectedCell);
}
UIInventoryCell* UIInventory::GetCell(unsigned int index)
{
	if (index < cells.size())
		return cells[index];

	return nullptr;
}