#include "UIItem.h"

UIItem::UIItem(UIScreen* screenParent) : UIBase(screenParent)
{
	// Name
	name = "UIItem";
}

UIItem::UIItem(UIScreen* screenParent, const sf::Texture& texture, sf::IntRect rect) : UIBase(screenParent), Item(texture, rect)
{
	// Name
	name = "UIItem";
}

