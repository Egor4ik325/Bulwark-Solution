#pragma once
#include "SFML/Graphics.hpp"

extern sf::RenderWindow window;
extern const int HEIGHT, WIDTH;  // Размеры окна
extern const int TILE_SIZE;

sf::Vector2f GetViewOffSet();
sf::Transform GetViewTransformOffSet();

sf::Vector2f GetMouseCoords();
bool GetMouseLeft();

bool IntersectsWithMouse(const sf::FloatRect& rect);