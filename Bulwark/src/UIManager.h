#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "UIBase.h"
#include "UIScreen.h"

// ��������������� c���������� �����, �������� UI � ���������� ����������������� � ���� 
// �� ����� �������� ��� ���� �������

class UIManager
{
private:
	static std::vector<UIScreen*> screens;     // ������ ��� ��������� ������ UI
						
	static UIBase* OverAll, *DragAll;            // � ����� - ��� ����������� � ��� ��� ������
public:											 

	static void Update();						 // ��������� �������� UI ������
    static void Draw(sf::RenderTarget &target);  // ������ �������� UI ������

	static UIBase* GetMouseOver();
	static UIBase* GetMouseDrag();
	static void AddScreen(UIScreen *screen);
	static void DeleteScreen(unsigned int index);
	static void DeleteScreen(UIScreen* screen);

	static void AddControl(unsigned int screenIndex, UIBase *controlAdress);
	static void DeleteControl(unsigned int screenIndex, unsigned int controlIndex);
private:

	static void UpdateDrag();
};