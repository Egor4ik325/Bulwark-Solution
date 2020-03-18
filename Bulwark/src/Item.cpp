#include "Item.h"
#include "Program.h"
#include "ItemManager.h"
///////////////////////////
Item::Item()
{
	
}

Item::Item(const sf::Texture & texture, sf::IntRect TextureRect, int Scale)
{
	sprite.setTexture(texture);
	sprite.setTextureRect(TextureRect);
	sprite.setScale(Scale, Scale);
}

void Item::Construct(const sf::Texture & texture, sf::IntRect TextureRect, int Scale)
{
	sprite.setTexture(texture);
	sprite.setTextureRect(TextureRect);
	sprite.setScale(Scale, Scale);
}

void Item::Draw(sf::RenderTarget &target)
{
	if (OnGround)
		target.draw(sprite);
	else
		target.draw(sprite, GetViewTransformOffSet());
}

sf::Vector2f Item::GetGlobalPosition()
{
	return sprite.getPosition();
}

sf::FloatRect Item::GetGlobalBounds()
{
	return sprite.getGlobalBounds();
}

void Item::SetTilePosition(sf::Vector2f tilePos)
{
	sprite.setPosition(sf::Vector2f(tilePos.x * TILE_SIZE, tilePos.y * TILE_SIZE));
}

void Item::SetPosition(sf::Vector2f position)
{
	sprite.setPosition(position);
}
