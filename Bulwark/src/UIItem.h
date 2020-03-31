#pragma once
#include "Item.h"
#include "UIBase.h"

////////////////////////////////////////////////////////////
/// \brief Item class which is cragable
///
////////////////////////////////////////////////////////////
class UIItem : public Item, public UIBase
{
public:
	UIItem(UIScreen* screenParent);
	UIItem(UIScreen* screenParent, const sf::Texture& texture, sf::IntRect rect);
};