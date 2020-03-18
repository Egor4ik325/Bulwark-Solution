#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class Layer
{
public:
	int opacity;                      // Непрозрачность
	std::vector<int> TilesId;	      // Айди плиток 
	std::vector<sf::Sprite> tiles;    // Спрайты плиток
};

class TileMap
{
public:
	// Типы плиток
	enum  TileType { GROUND, WALL, WATER, CHEST };       
													     
	bool LoadFromFile(std::string filename);          
	void Draw(sf::RenderTarget& target);	             
											             
	void SetTileSize(const int TileSize);	            
	void SetTileType(int id, TileType type);	             
											             
	int GetTileId(int x, int y);			             
	int GetTileId(sf::Vector2i TilePos);	             
	TileType GetTileType(int x, int y);		        
	TileType GetTileType(const sf::Vector2i &TilePos);   

private:

	int width, height;                     // Ширина и высота карты (в тайлах)
	int tileWidth, tileHeight;             // размер тайла в пикселях
	int firstTileID;				       
	sf::FloatRect drawingBounds;           // Часть карты которую мы будем рисовать и которая соответствует view
	sf::Texture tilesetImage;              // TileSet	
	std::vector<Layer> layers;             // Слои
	TileType TypeArr[20] = { GROUND };     // Типы для ID;
};


