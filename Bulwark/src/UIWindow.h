#pragma once
#include "SFML/Graphics.hpp"
#include "UIBase.h"

class UIWindow : public  UIBase
{
protected:
	sf::RectangleShape title;
	bool TitleVisible;
	const int TITLE_HEIGHT = 25;
	
	sf::Color BodyColor;
	sf::Color TitleColor;
	sf::Color TitleSelectedColor;
	sf::Color TitleDragColor;

	void ApplyColors();
public:

	UIWindow();

	void Update() override;
	void Draw(sf::RenderTarget & target) override;
	void UpdateOver() override;

	virtual bool GetDragAllow() override;
};