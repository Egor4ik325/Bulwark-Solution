#pragma once
#include "SFML/Graphics.hpp"
#include "UIBase.h"

// Экран интерфейсов
class UIScreen
{
public:
	std::vector <UIBase*> controls; // Адреса UI из динам. памяти

	bool active = false;
	UIBase* over, *drag;

public:

	void update();
	void draw(sf::RenderTarget &target);

	void addControl(UIBase *ControlAdress);
	void deleteControl(unsigned int index);
	void deleteControls();
	bool mouseIntersect();

private:
	void updateOver();
	void updateDrag();
};