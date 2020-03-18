#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class Layer
{
public:
	int opacity;                      // ��������������
	std::vector<int> TilesId;	      // ���� ������ 
	std::vector<sf::Sprite> tiles;    // ������� ������
};

class TileMap
{
public:
	// ���� ������
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

	int width, height;                     // ������ � ������ ����� (� ������)
	int tileWidth, tileHeight;             // ������ ����� � ��������
	int firstTileID;				       
	sf::FloatRect drawingBounds;           // ����� ����� ������� �� ����� �������� � ������� ������������� view
	sf::Texture tilesetImage;              // TileSet	
	std::vector<Layer> layers;             // ����
	TileType TypeArr[20] = { GROUND };     // ���� ��� ID;
};


