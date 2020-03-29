#include "UIBase.h"

UIBase::UIBase(UIScreen* screenParent): UI(screenParent)
{
}

void UIBase::draw(sf::RenderTarget & target)
{
	if (visible)
	{
		target.draw(*this);
	}
}