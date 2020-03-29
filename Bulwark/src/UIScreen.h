#pragma once
#include "SFML/Graphics.hpp"
#include "UIDragable.h"

// ����� - ������ �����������
class UIScreen
{
public:
	std::vector <UIBase*> controls; // ������ UI �� ������. ������ Stack/Heap

	UIDragable* over, *drag;
	bool visible = false;

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
	void updateDrag();
};