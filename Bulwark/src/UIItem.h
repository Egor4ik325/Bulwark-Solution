#pragma once
#include "Item.h"
#include "UIDragable.h"

////////////////////////////////////////////////////////////
/// \brief Item class which is dragable
///
////////////////////////////////////////////////////////////
class UIItem : public UIDragable
{
public:
	UIItem(Item item);									   // ����������� Item
	UIItem(UIScreen* screenParent);						   // ����������� UI
	UIItem(const sf::Texture& texture, sf::IntRect rect);  // ����������� Item

	UIItem(Item* item);									   // ����������� Item

	virtual void draw(sf::RenderTarget& target) override;
	virtual void update() override;

	virtual void onDragBegin() override;
	virtual void onDrop() override;
	virtual void onCancelDrag() override;


public:
	Item item;
};