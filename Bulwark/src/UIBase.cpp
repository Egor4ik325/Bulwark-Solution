#include "UIBase.h"
#include <iostream>
#include "Program.h"
#include "UIManager.h"

#include "UIScreen.h"

UIBase::UIBase(UIScreen* screenParent)
{
	// Присваиваем начальные данные
	visible = true;
	dragAble = false;
	this->screenParent = screenParent;
	rectShape.setFillColor(sf::Color::White);
	rectShape.setSize(sf::Vector2f(TILE_SIZE, TILE_SIZE));
	rectShape.setPosition(0.f, 0.f);

	dragOffset = { 0.f, 0.f };
}

void UIBase::draw(sf::RenderTarget &target)
{
	if (visible)
	{	
		target.draw(rectShape, GetViewTransformOffSet());
	}
}

void UIBase::update()
{
	
}

// Обновляем информацию объекта под курсором
void UIBase::updateOver()
{
	// Без родителя нельза двигать
	if (screenParent == nullptr)
		return;
	// Если курсор пересекся с Интерфейсом
	if (rectShape.getGlobalBounds().contains(GetMouseCoords()))
	{
		std::cout << "Intersect!! \n" ;
		
		if (dragAble && getDragAllow())
		{
			// Если не передвигаем 
			//ЭТОТ КОД ВЫПОЛНЯЕТСЯ 1 РАЗ ВНАЧАЛЕ ПЕРЕТАСКИВАНИЯ
			if (screenParent->drag == nullptr)
			{
				// Если способны передвигать
				//if (IsMouseLeft())
				{
					screenParent->drag = this;
					dragOffset = GetMouseCoords() - rectShape.getPosition();

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

void UIBase::setScreenParent(UIScreen * parent)
{
	screenParent = parent;
}

void UIBase::setSize(float x, float y)
{
	rectShape.setSize(sf::Vector2f(x, y));
}

bool UIBase::getDragAllow() const
{
	if (screenParent == nullptr)
		return false;

	return (rectShape.getGlobalBounds().contains(GetMouseCoords()) || screenParent->drag == this) && GetMouseLeft();
}

sf::Vector2f UIBase::getPosition() const
{
	return rectShape.getPosition();
}

sf::Vector2f UIBase::getGlobalPosition() const
{
	sf::Vector2f coords = rectShape.getPosition() + GetViewOffSet();
	return coords;
}

const sf::FloatRect& UIBase::getGlobalBounds() const
{
	sf::FloatRect globalBounds = rectShape.getGlobalBounds();
	globalBounds.left += GetViewOffSet().x;
	globalBounds.top += GetViewOffSet().y;

	return globalBounds;
}

sf::Vector2f UIBase::getDragOffSet() const
{
	return dragOffset;
}

const sf::RectangleShape& UIBase::getRectShape() const
{
	return rectShape;
}