#include "DebugRect.h"

#include <iostream>
#include <vector>

bool DebugRect::Enabled;
std::list<sf::RectangleShape> DebugRect::objects;

void DebugRect::AddRect(sf::FloatRect Rect, sf::Color color)
{
	if (!Enabled) return;
	sf::RectangleShape rect;

	rect.setSize(sf::Vector2f(Rect.width, Rect.height));
	rect.setPosition(sf::Vector2f(Rect.left, Rect.top));

	rect.setOutlineThickness(1);
	rect.setOutlineColor(color);
	rect.setFillColor(sf::Color::Transparent);

	objects.push_back(rect);
}

void DebugRect::Draw(sf::RenderTarget & target)
{
	if (!Enabled) return;

	for (auto obj : objects)
		target.draw(obj);

	objects.clear();
}
