#include "UIBase.h"
#include <iostream>
#include "Program.h"
#include "UIManager.h"

#include "UIScreen.h"

UIBase::UIBase()
{
	// Присваиваем начальные данные
	Visible = true;
	DragAble = false;
	screenParent = nullptr;
	rectShape.setFillColor(sf::Color::White);
	rectShape.setSize(sf::Vector2f(TILE_SIZE, TILE_SIZE));
	rectShape.setPosition(0.f, 0.f);

	dragOffset = { 0.f, 0.f };
}

bool UIBase::GetDragAllow()
{
	if (screenParent == nullptr)
		return false;

	return (rectShape.getGlobalBounds().contains(GetMouseCoords()) || screenParent->Drag == this) && GetMouseLeft();
}

void UIBase::Draw(sf::RenderTarget &target)
{
	if (Visible)
	{	
		target.draw(rectShape, GetViewTransformOffSet());
	}
}

void UIBase::Update()
{
	
}

// Обновляем информацию объекта под курсором
void UIBase::UpdateOver()
{
	// Без родителя нельза двигать
	if (screenParent == nullptr)
		return;
	// Если курсор пересекся с Интерфейсом
	if (rectShape.getGlobalBounds().contains(GetMouseCoords()))
	{
		std::cout << "Intersect!! \n" ;
		
		if (DragAble && GetDragAllow())
		{
			// Если не передвигаем 
			//ЭТОТ КОД ВЫПОЛНЯЕТСЯ 1 РАЗ ВНАЧАЛЕ ПЕРЕТАСКИВАНИЯ
			if (screenParent->Drag == nullptr)
			{
				// Если способны передвигать
				//if (IsMouseLeft())
				{
					screenParent->Drag = this;
					dragOffset = GetMouseCoords() - rectShape.getPosition();

					OnDragBegin();

					std::cout << "START MOVING!! \n";
				}
			}
		}

		// Если не передвигаем, то находимся над интерфейсом
		if (screenParent->Drag != this)
			screenParent->Over = this;
	}
}

void UIBase::OnDragBegin()
{
}

void UIBase::OnDrop()
{
}

void UIBase::OnCancelDrag()
{
}

////////////////////////////////////////////////////////////////////////////////////////////
void UIBase::setPosition(sf::Vector2f position)
{
	rectShape.setPosition(position);
}

void UIBase::setPosition(float x, float y)
{
	setPosition(sf::Vector2f(x, y));
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
	setSize(sf::Vector2f(x, y));
}

sf::Vector2f UIBase::GetPosition() const
{
	return rectShape.getPosition();
}

sf::Vector2f UIBase::GetGlobalPosition() const
{
	sf::Vector2f coords = rectShape.getPosition() + GetViewOffSet();
	return coords;
}

sf::FloatRect UIBase::GetGlobalBounds() const
{
	sf::FloatRect globalBounds = rectShape.getGlobalBounds();
	globalBounds.left += GetViewOffSet().x;
	globalBounds.top += GetViewOffSet().y;
	return globalBounds;
}

sf::Vector2f UIBase::GetDragOffSet() const
{
	return dragOffset;
}

sf::RectangleShape* UIBase::GetRectShape()
{
	return &rectShape;
}