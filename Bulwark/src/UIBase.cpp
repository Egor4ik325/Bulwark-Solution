#include "UIBase.h"
#include <iostream>
#include "Program.h"
#include "UIManager.h"

#include "UIScreen.h"

UIBase::UIBase()
{
	// ����������� ��������� ������
	Visible = true;
	DragAble = false;
	screenParent = nullptr;
	rectShape.setFillColor(sf::Color::White);
	rectShape.setSize(sf::Vector2f(TILE_SIZE, TILE_SIZE));
	rectShape.setPosition(0.f, 0.f);

	dragOffset = { 0.f, 0.f };
}

bool UIBase::getDragAllow()
{
	if (screenParent == nullptr)
		return false;

	return (rectShape.getGlobalBounds().contains(GetMouseCoords()) || screenParent->drag == this) && GetMouseLeft();
}

void UIBase::draw(sf::RenderTarget &target)
{
	if (Visible)
	{	
		target.draw(rectShape, GetViewTransformOffSet());
	}
}

void UIBase::update()
{
	
}

// ��������� ���������� ������� ��� ��������
void UIBase::updateOver()
{
	// ��� �������� ������ �������
	if (screenParent == nullptr)
		return;
	// ���� ������ ��������� � �����������
	if (rectShape.getGlobalBounds().contains(GetMouseCoords()))
	{
		std::cout << "Intersect!! \n" ;
		
		if (DragAble && getDragAllow())
		{
			// ���� �� ����������� 
			//���� ��� ����������� 1 ��� ������� ��������������
			if (screenParent->drag == nullptr)
			{
				// ���� �������� �����������
				//if (IsMouseLeft())
				{
					screenParent->drag = this;
					dragOffset = GetMouseCoords() - rectShape.getPosition();

					onDragBegin();

					std::cout << "START MOVING!! \n";
				}
			}
		}

		// ���� �� �����������, �� ��������� ��� �����������
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

sf::Vector2f UIBase::getPosition() const
{
	return rectShape.getPosition();
}

sf::Vector2f UIBase::getGlobalPosition() const
{
	sf::Vector2f coords = rectShape.getPosition() + GetViewOffSet();
	return coords;
}

sf::FloatRect UIBase::getGlobalBounds() const
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

sf::RectangleShape* UIBase::getRectShape()
{
	return &rectShape;
}