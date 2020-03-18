#include "UIInventoryCell.h"

#include "Program.h"
#include "Content.h"
#include "UIInventory.h"

UIInventoryCell::UIInventoryCell()
{
}

UIInventoryCell::UIInventoryCell(UIInventory* inv)
{
	// Запоминаем родителя
	this->invParent = inv;
	// Хранимый предмет
	itemContain = nullptr;
	//
	SelectedColor = sf::Color::Black;
	// Устанавливаем текстуру
	rectShape.setSize(sf::Vector2f(TILE_SIZE, TILE_SIZE));
	rectShape.setTexture(&ContentManager::InvCellTex, true);
	rectShape.setTextureRect(sf::IntRect(0, 0, 16, 16));
}

void UIInventoryCell::Update()
{
	UIBase::Update();

	if (itemContain != nullptr)
	{
		itemContain->SetPosition(rectShape.getPosition());
	}
}

void UIInventoryCell::Draw(sf::RenderTarget & target)
{
	if (invParent->GetCell(invParent->selectedCell) == this)
		rectShape.setFillColor(SelectedColor);
	else
		rectShape.setFillColor(sf::Color::White);

	UIBase::Draw(target);
}

void UIInventoryCell::SetItem(Item * item)
{
	itemContain = item;
	itemContain->OnGround = false;
	itemContain->SetPosition(GetPosition());
}

void UIInventoryCell::RemoveItem()
{
	itemContain = nullptr;
}

bool UIInventoryCell::IsEmpty()
{
	return itemContain == nullptr;
}

Item * UIInventoryCell::GetItem()
{
	return itemContain;
}
