#include "UIBase.h"
#include <iostream>
#include "Global.h"
#include "UIManager.h"

#include "UIScreen.h"

UIBase::UIBase(UIScreen* screenParent): screenParent(screenParent)
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
	if (rectShape.getGlobalBounds().contains(getMouseLocalPos()))
	{
		
		std::cout << "Intersect!! \n" ;
		
		if (dragAble && isDragAllow())
		{
			// Если еще не передвигаем 
			//ЭТОТ КОД ВЫПОЛНЯЕТСЯ 1 РАЗ ВНАЧАЛЕ ПЕРЕТАСКИВАНИЯ
			if (screenParent->drag == nullptr)
			{				
				// Если способны передвигать
				//if (IsMouseLeft())

				screenParent->drag = this;
				dragOffset = getMouseLocalPos() - rectShape.getPosition();
				
				onDragBegin();
				

				std::cout << "START MOVING!! \n";
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

bool UIBase::isDragAllow() const
{
	if (screenParent == nullptr) return false;

	return (rectShape.getGlobalBounds().contains(getMouseLocalPos()) || screenParent->drag == this) && isMouseLeft();
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

