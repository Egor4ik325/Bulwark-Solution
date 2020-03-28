#pragma once
#include "SFML/Graphics.hpp"

extern sf::RenderWindow window;
extern const int HEIGHT, WIDTH;  // Размеры окна
extern const int TILE_SIZE;

const sf::Transform& getViewTransformOffSet() ;
sf::Vector2f GetViewOffSet();

sf::Vector2f getMouseLocalPos();
sf::Vector2f getMouseGlobalPos();
bool isMouseLeft();