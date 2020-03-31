#include "UIBase.h"
#include "Global.h"

UIBase::UIBase(UIScreen * screenParent) :
	screenParent(screenParent)
{
}

void UIBase::update()
{
	updateChildren();
}

void UIBase::updateChildren()
{
	for (UIBase* c : childs)
		c->update();
}

void UIBase::draw(sf::RenderTarget & target)
{
	if (visible)
	{
		target.draw(*this, getViewTransformOffSet());
	}

	drawChildren(target);
}

void UIBase::drawChildren(sf::RenderTarget & target)
{
	for (UIBase* c : childs)
		c->draw(target);
}

void UIBase::setScreenParent(UIScreen * screenParent)
{
	this->screenParent = screenParent;
}

void UIBase::setScreenParent(UIScreen & screenParent)
{
	this->screenParent = &screenParent;
}

const std::string & UIBase::getName() const
{
	return name;
}
UIBase::~UIBase()
{
	for (UIBase* c : childs)
	{
		delete c;
	}
	childs.clear();
}
