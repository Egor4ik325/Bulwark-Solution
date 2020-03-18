#include "UIManager.h"

#include <iostream>
#include <iterator>

std::vector <UIScreen*> UIManager::screens;

UIBase* UIManager::OverAll = nullptr;
UIBase* UIManager::DragAll = nullptr;

void UIManager::Update()
{
	UpdateDrag();
	for (UIScreen* uiscr : screens)
	{
		if ((*uiscr).active)
		{
			(*uiscr).Update();
			// Выводим одни общие указатели на *Drag и *Over
			DragAll = uiscr->Drag;
			OverAll = uiscr->Over;
			
		}
	}	
}

void UIManager::UpdateDrag()
{
}

void UIManager::Draw(sf::RenderTarget & target)
{
	for (UIScreen* uiscr : screens)
		if ((*uiscr).active)
			(*uiscr).Draw(target);
}

UIBase* UIManager::GetMouseOver()
{
	UIBase* over = nullptr;
	for (UIScreen* screen : screens)
	{
		if (screen->active)
		{
			if (screen->Over != nullptr)
			{
				over = screen->Over;
			}
		}
	}
	return over;
}

UIBase* UIManager::GetMouseDrag()
{
	UIBase* drag = nullptr;
	for (UIScreen* screen : screens)
	{
		if (screen->active)
		{
			if (screen->Drag != nullptr)
			{
				drag = screen->Over;
			}
		}
	}
	return drag;
}

void UIManager::AddScreen(UIScreen* uiscreen)
{
	screens.push_back(uiscreen);
}

void UIManager::DeleteScreen(unsigned int index)
{
	if (index > screens.size()) return;

	// Удаляем из динамической памяти
	UIScreen* screen = screens[index];
	screen->DeleteControls();
	delete screens[index];

	// Удаляем из списка
	std::vector <UIScreen*>::iterator iter = screens.begin();
	std::advance(iter, index);
	screens.erase(iter);
}

void UIManager::DeleteScreen(UIScreen* screen)
{
	for (int i = 0; i < screens.size(); i++)
	{
		if (&screen[i] == screen)
		{
			DeleteScreen(i);
			return;
		}
	}
}

void UIManager::AddControl(unsigned int screenIndex, UIBase* controlAdress)
{
	if (screenIndex > screens.size()) return;

	screens[screenIndex]->AddControl(controlAdress);
}

void UIManager::DeleteControl(unsigned int screenIndex, unsigned int controlIndex)
{
	if (screenIndex > screens.size()) return;
	if (controlIndex > screens[screenIndex]->controls.size()) return;

	screens[screenIndex]->DeleteControl(controlIndex);
}
