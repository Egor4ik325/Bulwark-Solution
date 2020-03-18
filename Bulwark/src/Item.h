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
	bool OnGround;

	Item();
	Item(const sf::Texture &texture, sf::IntRect TextureRect, int Scale = 4);
	virtual void Construct(const sf::Texture &texture, sf::IntRect TextureRect, int Scale = 4);
	virtual void Draw(sf::RenderTarget &target);

	void SetTilePosition(sf::Vector2f tilePos);
	void SetPosition(sf::Vector2f position);
	sf::Vector2f GetGlobalPosition();
	sf::FloatRect GetGlobalBounds();
};