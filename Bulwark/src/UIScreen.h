#pragma once
#include "SFML/Graphics.hpp"
#include "UIDragable.h"

// ����� - ������ �����������
class UIScreen
{
public:
	std::vector <UIDragable*> controls; // ������ UI �� �����. ������

	bool active = false;
	UIDragable* over, *drag;

public:

	UIScreen();

	void update();
	void draw(sf::RenderTarget &target);

	// �������� UI ��� ���������� � Managment
	void addControl(UIDragable* control);
	void addControl(UIDragable& control);

	void deleteControl(unsigned int index);
	void deleteControls();
	bool mouseIntersect();

private:
	void updateOver();
	void updateDrag();
};