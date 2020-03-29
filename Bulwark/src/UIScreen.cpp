#include "UIScreen.h"
#include "Global.h"
#include "UIManager.h"

UIScreen::UIScreen()
{
	UIManager::addScreen(this);
}

void UIScreen::update()
{
	// ������� ��������
	updateDrag(); 
	updateOver();


	for (UIDragable* c : controls)
	{
		(*c).update();
	}
}

void UIScreen::updateOver()
{
	over = nullptr;

	for (UIDragable* c : controls)
	{
		(*c).updateOver();
	}
}

void UIScreen::updateDrag()
{
	// ���� ��������� ��������� - (������ ���� ���������)
	if (drag != nullptr)
	{
		// ���� ��� ��� ���������
		if (drag->isDragAllow())
		{
			// �������� �� ������� ���� ���������� ������� ������ ���� ����� UI � �����,
			// � �������� ��������� ����������
			sf::Vector2f nextPos = getMouseLocalPos() - drag->getDragOffSet();
			drag->setPosition(nextPos);
		}
		// ���� ��� �� ���������
		else
		{
			// ���� ��� �������� ���-�� ����
			if (over != nullptr)
				drag->onDrop();
			else
				drag->onCancelDrag();
	
			// ���������
			drag = nullptr;
		}
	
		//// ���� ������ ����� ������ - �����������
		//if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		//{
		//	sf::Vector2f NextPos = GetMouseCoords() - (*Drag).GetDragOffSet();
		//
		//	(*Drag).SetPosition(sf::Vector2f(window.mapCoordsToPixel(NextPos)));
		//}
		//// ���� ���������
		//else
		//{
		//	// ���� ��� �������� ���-��
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
	for (UIDragable *c : controls)
		(*c).draw(target);
}

void UIScreen::addControl(UIDragable* control)
{
	control->setScreenParent(this);
	controls.push_back(control); // ��������� UI � ������
}

void UIScreen::addControl(UIDragable& control)
{
	control.setScreenParent(this);
	controls.push_back(&control);
}

void UIScreen::deleteControl(unsigned int index)
{
	if (index > controls.size()) return;

	//// ������� �� ������������ ������
	//delete controls[index];       

	// ������� �� ������
	std::vector <UIDragable*>::iterator iter = controls.begin();
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
	for (UIDragable* c : controls)
	{
		if ((*c).getRectShape().getGlobalBounds().contains(getMouseLocalPos()))
		{
			intersect = true;
			break;
		}
	}

	return intersect;
}