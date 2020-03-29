#pragma once
#include "SFML/Graphics.hpp"
#include "UIDragable.h"

class UIButton : public UIDragable
{
protected:
	sf::Text text;
	sf::Color color;

public:
	// ����� ���������� ����������� �� ���������, �� ������� � ���������� �������� ��������, ��� �������� �� ��������
	UIButton(UIScreen* screenParent = nullptr);
	//UIButton(const std::string& text, const sf::Color& color, const sf::Font& font);

	void draw(sf::RenderTarget & target) override;
	void updateOver() override;

	void setColor(const sf::Color& color);
protected:

	void drawText(sf::RenderTarget& target);
};