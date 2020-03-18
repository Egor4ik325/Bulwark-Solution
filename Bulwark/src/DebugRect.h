#pragma once
#include "SFML/Graphics.hpp"
#include <list>

class DebugRect
{
public:
	static bool Enabled;
	static std::list <sf::RectangleShape> objects; // Тут хранятся все рисуемые фигуры

public:
	static void AddRect(sf::FloatRect, sf::Color color);
	static void Draw(sf::RenderTarget & target);
};