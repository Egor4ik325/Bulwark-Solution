#include "UIScreen.h"
#include "Program.h"

void UIScreen::update()
{
	// ������� ��������
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
	// ���� ��������� ��������� - (������ ���� ���������)
	if (drag != nullptr)
	{
		// ���� ��� ��� ���������
		if ((*drag).isDragAllow())
		{
			sf::Vector2f NextPos = GetMouseCoords() - (*drag).getDragOffSet();
	
			(*drag).setPosition(sf::Vector2f(window.mapCoordsToPixel(NextPos)));
		}
		// ���� ��� �� ���������
		else
		{
			// ���� ��� �������� ���-�� ����
			if (over != nullptr)
				(*drag).onDrop();
			else
				(*drag).onCancelDrag();
	
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
	for (UIBase *c : controls)
		(*c).draw(target);
}

void UIScreen::addControl(UIBase *ControlAdress)
{
	ControlAdress->setScreenParent(this);
	controls.push_back(ControlAdress); // ��������� ������ ���������� � ������
}

void UIScreen::deleteControl(unsigned int index)
{
	if (index > controls.size()) return;

	// ������� �� ������������ ������
	delete controls[index];       

	// ������� �� ������
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