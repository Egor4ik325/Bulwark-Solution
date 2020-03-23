#pragma once
#include "SFML/Graphics.hpp"
#include <vector>
#include "UIWindow.h"
#include "UIInventoryCell.h"

class UIInventory : public UIWindow
{
protected:
	std::vector <UIInventoryCell*> cells;

    unsigned int cellCount;
	
public:
	unsigned int selectedCell;

	UIInventory(UIScreen* screenParent = nullptr);

	bool isDragAllow() const override;
	void update() override;

	UIInventoryCell* getCell(unsigned int index);
	UIInventoryCell* getFirstEmptyCell();
	UIInventoryCell* getSelectedCell();

protected:
	void createCells();
	void addCell();
};
