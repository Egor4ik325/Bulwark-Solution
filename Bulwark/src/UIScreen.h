#pragma once
#include "SFML/Graphics.hpp"
#include "UIDragable.h"

// Экран - массив интерфейсов
class UIScreen
{
public:
	std::vector <UIBase*> controls; // Адреса UI из статик. памяти Stack/Heap

	UIDragable* over, *drag;
	bool visible = false;

public:

	UIScreen();

	void update();
	void draw(sf::RenderTarget &target);

	// Передаем UI для добавления в Managment
	void addControl(UIDragable* control);
	void addControl(UIDragable& control);
	void deleteControl(unsigned int index);
	void deleteControls();
	bool mouseIntersect();

private:
	void updateDrag();
};