#pragma once
#include "SFML/Graphics.hpp"
#include "UIDragable.h"

// Экран - массив интерфейсов
class UIScreen
{
public:
	std::vector <UIDragable*> controls; // Адреса UI из динам. памяти

	bool active = false;
	UIDragable* over, *drag;

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
	void updateOver();
	void updateDrag();
};