#pragma once
#include "SFML/Graphics.hpp"
#include "UIBase.h"

// ����� �����������
class UIScreen
{
public:
	std::vector <UIBase*> controls; // ������ UI �� �����. ������

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