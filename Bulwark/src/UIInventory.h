#pragma once
#include "SFML/Graphics.hpp"
#include "UIWindow.h"
#include <vector>
#include "UIInventoryCell.h"

class UIInventory : public UIWindow
{
protected:
	std::vector <UIInventoryCell*> cells;

    unsigned int cellCount;
	
public:
	unsigned int selectedCell;
	
	UIInventory();

	void Construct();

	bool GetDragAllow() override;
	void Update() override;

	void PickUp();
	void Drop();

	UIInventoryCell* GetCell(unsigned int index);
	UIInventoryCell* GetEmptyCell();
	UIInventoryCell* GetSelectedCell();

protected:
	void AddCell();
};
