#pragma once
#include "SFML/Graphics.hpp"
#include "UIBase.h"

class UIButton : public UIBase
{
protected:
	sf::Text text;
	sf::Color color;

public:
	UIButton();
	UIButton(const std::string& text, const sf::Color& color, const sf::Font& font);
	void Construct();

	void Draw(sf::RenderTarget& target) override;
	void UpdateOver() override;

	void SetColor(const sf::Color& color);
protected:

	void DrawText(sf::RenderTarget& target);
};