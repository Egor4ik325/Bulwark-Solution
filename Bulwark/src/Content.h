#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class ContentManager 
{
private:
public:

	static const std::string CONTENT_DIR;
	
    static sf::Texture TileSet; // Плитки 16x16 пикселей
	static sf::Texture PlayerTexture;
	static sf::Texture EffectTexture;
	static sf::Texture ItemSet;
	static sf::Texture InvCellTex;
	static sf::Texture MenuTexture;
	static sf::Texture UIButtunTexture;

	static sf::Font Font;

	//// Загрузить контент STATIC //////
	static void LoadContent();
};
