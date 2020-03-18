#include "ItemFood.h"

ItemFood::ItemFood()
{
}

void ItemFood::Construct(const sf::Texture& texture, sf::IntRect textureRect, int scale)
{
	Item::Construct(texture, textureRect, scale);
}
