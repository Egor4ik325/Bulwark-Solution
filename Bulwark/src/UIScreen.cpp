#include "UIScreen.h"
#include "Program.h"

void UIScreen::Update()
{
	// ������� ��������
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
	// ���� ��������� ��������� - (������ ���� ���������)
	if (Drag != nullptr)
	{
		// ���� ��� ��� ���������
		if ((*Drag).GetDragAllow())
		{
			sf::Vector2f NextPos = GetMouseCoords() - (*Drag).GetDragOffSet();
	
			(*Drag).setPosition(sf::Vector2f(window.mapCoordsToPixel(NextPos)));
		}
		// ���� ��� �� ���������
		else
		{
			// ���� ��� �������� ���-�� ����
			if (Over != nullptr)
				(*Drag).OnDrop();
			else
				(*Drag).OnCancelDrag();
	
			// ���������
			Drag = nullptr;
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

void UIScreen::Draw(sf::RenderTarget &target)
{
	for (UIBase *c : controls)
		(*c).Draw(target);
}

void UIScreen::AddControl(UIBase *ControlAdress)
{
	ControlAdress->setScreenParent(this);
	controls.push_back(ControlAdress); // ��������� ������ ���������� � ������
}

void UIScreen::DeleteControl(unsigned int index)
{
	if (index > controls.size()) return;

	// ������� �� ������������ ������
	delete controls[index];       

	// ������� �� ������
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