#pragma once
#include <SFML/Graphics.hpp>

class Item
{
protected:
	// Собственные данные
	sf::Sprite sprite;

	unsigned int id;
	unsigned int count;
	
public:
	bool onGround;

	Item();
	Item(const sf::Texture &texture, sf::IntRect TextureRect, int Scale = 4);
	virtual void construct(const sf::Texture &texture, sf::IntRect TextureRect, int Scale = 4);
	virtual void draw(sf::RenderTarget &target);

	void setTilePosition(sf::Vector2f tilePos);
	void setPosition(sf::Vector2f position);
	sf::Vector2f getGlobalPosition();
	sf::FloatRect getGlobalBounds();
};