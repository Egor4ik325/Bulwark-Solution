#pragma once
#include "SFML/Graphics.hpp"
#include "UIBase.h"

class UIWindow : public  UIBase
{
protected:
	sf::RectangleShape title;
	bool titleVisible;
	const int TITLE_HEIGHT = 25;
	
	sf::Color bodyColor;
	sf::Color titleColor;
	sf::Color titleSelectedColor;
	sf::Color titleDragColor;

	void applyColors();
public:

	UIWindow(UIScreen* screenParent = nullptr);

	void update() override;
	void draw(sf::RenderTarget & target) override;
	void updateOver() override;

	bool getDragAllow() const override;
};