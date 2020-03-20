#pragma once
#include <SFML/Graphics.hpp>
#include "TileMap.h"
#include "UIInventory.h"

class Player
{
private:
	sf::Vector2f position;  // Координаты	
	sf::Vector2f velocity;  // Скорость

	bool going;

	bool onTile;
	float speed; int health;

	enum DIR { UP, DOWN, RIGHT, LEFT, UPRIGHT, UPLEFT, DOWNRIGHT, DOWNLEFT, NONE };
	DIR playerDir; DIR targDir;

	TileMap *map;

	// Движение
	sf::Vector2i targ; sf::Vector2i targT; // Координаты куда идти
	bool dirGoingFlag; int goneX, goneY;

	// Анимация
	float frame;
	sf::Sprite sprite;
	sf::Sprite effect;

public:
	Player();

	void update(float time);
	void draw(sf::RenderTarget & target);
	
	void pickUp();
	void dropUp(UIInventoryCell* cell);
	void stop();
	void setTargetedTile(int x, int y);
	void moveBy(int TileX, int TileY);

	void setTexture(sf::Texture &playerTex); // СДЕЛАТЬ 
	void setIventory(UIInventory* inventory); // СДЕЛАТЬ ОБЯЗАТЕЛЬНЫМ
	void setTileMap(TileMap &map);
	sf::Vector2f getPosition() const;
	sf::Vector2i getRoundPos() const;
	sf::Vector2i getTilePos() const;	
	sf::Vector2i getMiddleTilePos() const;
	sf::Vector2f getMiddlePos() const;

	static UIInventory *inventory;

	bool pking;
private:
	void updateMovement(float time);
	void targTileDiraction();
	void collision();
	void animation(float time);


};