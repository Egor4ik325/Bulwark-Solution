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

	void construct();

	bool getDragAllow() override;
	void update() override;

	UIInventoryCell* getCell(unsigned int index);
	UIInventoryCell* getFirstEmptyCell();
	UIInventoryCell* getSelectedCell();

protected:
	void addCell();
};
