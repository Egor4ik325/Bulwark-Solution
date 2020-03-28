#pragma once
#include "SFML/Graphics.hpp"
#include "UIBase.h"

class UIButton : public UIBase
{
protected:
	sf::Text text;
	sf::Color color;

public:
	//  огда вызываетс€ конструктор по умолчанию, мы обещаем в дальнейшем передать родител€, без родител€ не работаем
	UIButton(UIScreen* screenParent = nullptr);
	//UIButton(const std::string& text, const sf::Color& color, const sf::Font& font);

	void draw(sf::RenderTarget & target) override;
	void updateOver() override;

	void setColor(const sf::Color& color);
protected:

	void drawText(sf::RenderTarget& target);
};