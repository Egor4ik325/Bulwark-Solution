#include "UIScreen.h"
#include "Global.h"
#include "UIManager.h"

UIScreen::UIScreen()
{
	UIManager::addScreen(this);
}

void UIScreen::update()
{
	// Сначала изменяем
	updateDrag();

	over = nullptr;
	//updateOver();
	for (UIBase* c : controls)
	{
		c->update();
	}
}

void UIScreen::updateDrag()
{
	// Если сохранили интерфейс - (значит было разрешено)
	if (drag != nullptr)
	{
		// Если все ещё разрешено
		if (drag->isDragAllow())
		{
			// Отнимаем от позиции мыши расстояник которые должно быть между UI и мышью,
			// и получаем следующее расстояние
			sf::Vector2f nextPos = getMouseLocalPos() - drag->getDragOffSet();
			drag->setPosition(nextPos);
		}
		// Если уже не разрешено
		else
		{
			// Если под курсором что-то есть
			if (over != nullptr)
				drag->onDrop();
			else
				drag->onCancelDrag();
	
			// Отпускаем
			drag = nullptr;
		}
	}
}

void UIScreen::draw(sf::RenderTarget &target)
{
	for (UIBase *c : controls)
	{
		c->draw(target);
	}
}

void UIScreen::addControl(UIDragable* control)
{
	control->setScreenParent(this);
	controls.push_back(control); // Добавляем UI в список
}

void UIScreen::addControl(UIDragable& control)
{
	control.setScreenParent(this);
	controls.push_back(&control);
}

void UIScreen::deleteControl(unsigned int index)
{
	if (index > controls.size()) return;

	//// Удаляем из динамической памяти
	//delete controls[index];       

	// Удаляем из списка
	std::vector <UIBase*>::iterator iter = controls.begin();
	std::advance(iter, index);
	controls.erase(iter);        
}

void UIScreen::deleteControls()
{
	//for (UIBase* c : controls)
	//{
	//	delete c;
	//}
	controls.clear();
}

bool UIScreen::mouseIntersect()
{
	bool intersect = false;
	for (UIBase* c : controls)
	{
		if (c->getGlobalBounds().contains(getMouseLocalPos()))
		{
			intersect = true;
			break;
		}
	}

	return intersect;
}

UIScreen::~UIScreen()
{
}
