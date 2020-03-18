#pragma once
#include "SFML/Graphics.hpp"
#include "UIBase.h"

// Экран интерфейсов
class UIScreen
{
public:
	std::vector <UIBase*> controls; // Адреса UI из динам. памяти

	bool active = false;
	UIBase* Over, *Drag;

public:

	void Update();
	void Draw(sf::RenderTarget &target);

	void AddControl(UIBase *ControlAdress);
	void DeleteControl(unsigned int index);
	void DeleteControls();
	bool MouseIntersect();

private:
	void UpdateOver();
	void UpdateDrag();
};