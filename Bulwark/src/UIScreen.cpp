#include "UIScreen.h"
#include "Program.h"

void UIScreen::update()
{
	// Сначала изменяем
	updateDrag(); 
	updateOver();


	for (UIBase* c : controls)
	{
		(*c).update();
	}
}

void UIScreen::updateOver()
{
	over = nullptr;

	for (UIBase* c : controls)
	{
		(*c).updateOver();
	}
}

void UIScreen::updateDrag()
{
	// Если сохранили интерфейс - (значит было разрешено)
	if (drag != nullptr)
	{
		// Если все ещё разрешено
		if ((*drag).isDragAllow())
		{
			sf::Vector2f NextPos = GetMouseCoords() - (*drag).getDragOffSet();
	
			(*drag).setPosition(sf::Vector2f(window.mapCoordsToPixel(NextPos)));
		}
		// Если уже не разрешено
		else
		{
			// Если под курсором что-то есть
			if (over != nullptr)
				(*drag).onDrop();
			else
				(*drag).onCancelDrag();
	
			// Отпускаем
			drag = nullptr;
		}
	
		//// Если зажата левая кнопка - передвидаем
		//if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		//{
		//	sf::Vector2f NextPos = GetMouseCoords() - (*Drag).GetDragOffSet();
		//
		//	(*Drag).SetPosition(sf::Vector2f(window.mapCoordsToPixel(NextPos)));
		//}
		//// Если отпустили
		//else
		//{
		//	// Если под курсором что-то
		//	if (Over != nullptr)
		//		(*Drag).OnDrop();
		//	else
		//		(*Drag).OnCancelDrag();
		//
		//	Drag = nullptr;
		//}
	}
}

void UIScreen::draw(sf::RenderTarget &target)
{
	for (UIBase *c : controls)
		(*c).draw(target);
}

void UIScreen::addControl(UIBase *ControlAdress)
{
	ControlAdress->setScreenParent(this);
	controls.push_back(ControlAdress); // Добавляем адресс Интерфейса в список
}

void UIScreen::deleteControl(unsigned int index)
{
	if (index > controls.size()) return;

	// Удаляем из динамической памяти
	delete controls[index];       

	// Удаляем из списка
	std::vector <UIBase*>::iterator iter = controls.begin();
	std::advance(iter, index);
	controls.erase(iter);        
}

void UIScreen::deleteControls()
{
	for (UIBase* c : controls)
	{
		delete c;
	}
	controls.clear();
}

bool UIScreen::mouseIntersect()
{
	bool intersect = false;
	for (UIBase* c : controls)
	{
		sf::Vector2f MouseGlobalPos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

		if ((*c).getGlobalBounds().contains(MouseGlobalPos))
		{
			intersect = true;
			break;
		}
	}

	return intersect;
}