#include "UIScreen.h"
#include "Program.h"

void UIScreen::Update()
{
	// Сначала изменяем
	UpdateDrag(); 
	UpdateOver();


	for (UIBase* c : controls)
	{
		(*c).Update();
	}
}

void UIScreen::UpdateOver()
{
	Over = nullptr;

	for (UIBase* c : controls)
	{
		(*c).UpdateOver();
	}
}

void UIScreen::UpdateDrag()
{
	// Если сохранили интерфейс - (значит было разрешено)
	if (Drag != nullptr)
	{
		// Если все ещё разрешено
		if ((*Drag).GetDragAllow())
		{
			sf::Vector2f NextPos = GetMouseCoords() - (*Drag).GetDragOffSet();
	
			(*Drag).setPosition(sf::Vector2f(window.mapCoordsToPixel(NextPos)));
		}
		// Если уже не разрешено
		else
		{
			// Если под курсором что-то есть
			if (Over != nullptr)
				(*Drag).OnDrop();
			else
				(*Drag).OnCancelDrag();
	
			// Отпускаем
			Drag = nullptr;
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

void UIScreen::Draw(sf::RenderTarget &target)
{
	for (UIBase *c : controls)
		(*c).Draw(target);
}

void UIScreen::AddControl(UIBase *ControlAdress)
{
	ControlAdress->setScreenParent(this);
	controls.push_back(ControlAdress); // Добавляем адресс Интерфейса в список
}

void UIScreen::DeleteControl(unsigned int index)
{
	if (index > controls.size()) return;

	// Удаляем из динамической памяти
	delete controls[index];       

	// Удаляем из списка
	std::vector <UIBase*>::iterator iter = controls.begin();
	std::advance(iter, index);
	controls.erase(iter);        
}

void UIScreen::DeleteControls()
{
	for (UIBase* c : controls)
	{
		delete c;
	}
	controls.clear();
}

bool UIScreen::MouseIntersect()
{
	bool intersect = false;
	for (UIBase* c : controls)
	{
		sf::Vector2f MouseGlobalPos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

		if ((*c).GetGlobalBounds().contains(MouseGlobalPos))
		{
			intersect = true;
			break;
		}
	}

	return intersect;
}