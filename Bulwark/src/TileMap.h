#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class Layer
{
public:
	int opacity;                      // ��������������
	std::vector<int> tilesId;	      // ���� ������ 
	std::vector<sf::Sprite> tiles;    // ������� ������
};

class TileMap
{
public:
	// ���� ������
	enum  TileType { GROUND, WALL, WATER, CHEST };       
													     
	bool loadFromFile(std::string filename);          
	void draw(sf::RenderTarget& target);	             
											             
	void setTileSize(const int TileSize);	            
	void setTileType(int id, TileType type);	             
											             
	int getTileId(int x, int y);			             
	int getTileId(sf::Vector2i TilePos);	             
	TileType getTileType(int x, int y);		        
	TileType getTileType(const sf::Vector2i &TilePos);   

private:

	int width, height;                     // ������ � ������ ����� (� ������)
	int tileWidth, tileHeight;             // ������ ����� � ��������
	int firstTileID;				       
	sf::FloatRect drawingBounds;           // ����� ����� ������� �� ����� �������� � ������� ������������� view
	sf::Texture tilesetImage;              // TileSet	
	std::vector<Layer> layers;             // ����
	TileType typeArr[20] = { GROUND };     // ���� ��� ID;
};


