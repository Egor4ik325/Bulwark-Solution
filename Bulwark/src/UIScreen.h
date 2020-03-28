#pragma once
#include "SFML/Graphics.hpp"
#include "UIBase.h"

// Экран - массим интерфейсов
class UIScreen
{
public:
	std::vector <UIBase*> controls; // Адреса UI из динам. памяти

	bool active = false;
	UIBase* over, *drag;

public:

	UIScreen();

	void update();
	void draw(sf::RenderTarget &target);

	// Передаем UI для добавления в Managment
	void addControl(UIBase* control);
	void addControl(UIBase& control);

	void deleteControl(unsigned int index);
	void deleteControls();
	bool mouseIntersect();

private:
	void updateOver();
	void updateDrag();
};