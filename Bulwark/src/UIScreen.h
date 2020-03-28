#pragma once
#include "SFML/Graphics.hpp"
#include "UIBase.h"

// ����� - ������ �����������
class UIScreen
{
public:
	std::vector <UIBase*> controls; // ������ UI �� �����. ������

	bool active = false;
	UIBase* over, *drag;

public:

	UIScreen();

	void update();
	void draw(sf::RenderTarget &target);

	// �������� UI ��� ���������� � Managment
	void addControl(UIBase* control);
	void addControl(UIBase& control);

	void deleteControl(unsigned int index);
	void deleteControls();
	bool mouseIntersect();

private:
	void updateOver();
	void updateDrag();
};