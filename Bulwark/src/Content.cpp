#include "Content.h"
///////////////////   Инициализация переменных   /////////////////

const std::string ContentManager::CONTENT_DIR = "Content/";
sf::Texture ContentManager::TileSet;
sf::Texture ContentManager::PlayerTexture;
sf::Texture ContentManager::EffectTexture;
sf::Texture ContentManager::ItemSet;
sf::Texture ContentManager::InvCellTex;
sf::Texture ContentManager::MenuTexture;
sf::Texture ContentManager::UIButtunTexture;
sf::Font ContentManager::Font;

void ContentManager::LoadContent()
{
	TileSet.loadFromFile(CONTENT_DIR + "TileSet.png");
	PlayerTexture.loadFromFile(CONTENT_DIR + "PlayerTexture.png");
	EffectTexture.loadFromFile(CONTENT_DIR + "PlayerTexture.png");
	ItemSet.loadFromFile(CONTENT_DIR + "ItemSet.png");
	InvCellTex.loadFromFile(CONTENT_DIR + "InvCellSet.png");
	MenuTexture.loadFromFile(CONTENT_DIR + "menu.png", sf::IntRect(0,0, 1024, 400));
	UIButtunTexture.loadFromFile(CONTENT_DIR + "menu.png", sf::IntRect(503, 457, 200, 200));

	// Texture.setSmoth(bool)
    Font.loadFromFile(CONTENT_DIR + "Font.ttf");
}