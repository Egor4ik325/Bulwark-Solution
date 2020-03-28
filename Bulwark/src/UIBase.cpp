#include "UIBase.h"
#include <iostream>
#include "Program.h"
#include "UIManager.h"

#include "UIScreen.h"

UIBase::UIBase(UIScreen* screenParent): 
	screenParent(screenParent)
{
	visible = true;
	dragAble = false;
	// Присваиваем начальные данные
	rectShape.setFillColor(sf::Color::White);
	rectShape.setSize(sf::Vector2f(TILE_SIZE, TILE_SIZE));
	rectShape.setPosition(0.f, 0.f);
	dragOffset = sf::Vector2f(0.f, 0.f);
}

void UIBase::draw(sf::RenderTarget &target)
{
	if (visible)
	{	
		target.draw(rectShape, getViewTransformOffSet());
	}
}

void UIBase::update()
{
	
}

// Обновляем информацию объекта под курсором
void UIBase::updateOver()
{
	if (screenParent == nullptr) return;

	// Если курсор пересекся с Интерфейсом
	auto mouseLocalPos = getMouseLocalPos();
	if (rectShape.getGlobalBounds().contains(mouseLocalPos))
	{
		std::cout << "Intersect!! \n" ;
		
		if (dragAble && isDragAllow())
		{
			// Если не передвигаем 
			//ЭТОТ КОД ВЫПОЛНЯЕТСЯ 1 РАЗ ВНАЧАЛЕ ПЕРЕТАСКИВАНИЯ
			if (screenParent->drag == nullptr)
			{
				// Если способны передвигать
				//if (IsMouseLeft())
				{
					screenParent->drag = this;
					//auto mouseLocalPos2 = getMouseLocalPos();
					dragOffset = mouseLocalPos - rectShape.getPosition();

					onDragBegin();

					std::cout << "START MOVING!! \n";
				}
			}
		}

		// Если не передвигаем, то находимся над интерфейсом
		if (screenParent->drag != this)
			screenParent->over = this;
	}
}

void UIBase::onDragBegin()
{

}

void UIBase::onDrop()
{

}

void UIBase::onCancelDrag()
{

}
////////////////////////////////////////////////////////////////////////////////////
void UIBase::setPosition(sf::Vector2f position)
{
	rectShape.setPosition(position);
}

void UIBase::setPosition(float x, float y)
{
	rectShape.setPosition(sf::Vector2f(x, y));
}

void UIBase::setSize(sf::Vector2f size)
{
	rectShape.setSize(size);
}

void UIBase::setSize(float x, float y)
{
	rectShape.setSize(sf::Vector2f(x, y));
}

bool UIBase::isDragAllow() const
{
	if (screenParent == nullptr) return false;

	return (rectShape.getGlobalBounds().contains(getMouseLocalPos()) || screenParent->drag == this) && isMouseLeft();
}

//sf::Vector2f UIBase::getGlobalPosition() const
//{
//	sf::Vector2f coords = rectShape.getPosition() + GetViewOffSet();
//	return coords;
//}
//
//const sf::FloatRect& UIBase::getGlobalBounds() const
//{
//	sf::FloatRect globalBounds = rectShape.getGlobalBounds();
//	globalBounds.left += GetViewOffSet().x;
//	globalBounds.top += GetViewOffSet().y;
//
//	return globalBounds;
//}