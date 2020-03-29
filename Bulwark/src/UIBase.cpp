#include "UIBase.h"
#include "Global.h"

UIBase::UIBase(UIScreen * screenParent) :
	screenParent(screenParent)
{
}

void UIBase::setScreenParent(UIScreen * screenParent)
{
	this->screenParent = screenParent;
}

void UIBase::setScreenParent(UIScreen & screenParent)
{
	this->screenParent = &screenParent;
}

const std::string & UIBase::getUIName() const
{
	return name;
}

void UIBase::draw(sf::RenderTarget & target)
{
	if (visible)
	{
		target.draw(*this, getViewTransformOffSet());
	}
}