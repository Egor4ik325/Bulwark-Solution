#pragma once
#include <SFML/Graphics.hpp>
#include "TileMap.h"
#include "UIInventory.h"

class Player
{
public:
	Player();

	void Update(float time);
	void Draw(sf::RenderTarget & target);
	
	void PickUp();
	void DropUp(UIInventoryCell* cell);
	void Stop();
	void SetTargetedTile(int x, int y);
	void MoveBy(int TileX, int TileY);

	void SetTexture(sf::Texture &playerTex);
	void SetTileMap(TileMap &map);
	sf::Vector2f GetPosition() const;
	sf::Vector2i GetRoundPos() const;
	sf::Vector2i GetTilePos() const;	
	sf::Vector2i GetMiddleTilePos() const;
	sf::Vector2f GetMiddlePos() const;

	static UIInventory *inventory;

	bool Picking;
private:
	void UpdateMovement(float time);
	void TargTileDir();
	void Collision();
	void Animation(float time);

private:
	sf::Vector2f position;  // Координаты	
	sf::Vector2f velocity;  // Скорость

	bool going;
	
	bool OnTile;
	float speed; int health;

	enum DIR { UP, DOWN, RIGHT, LEFT, UPRIGHT, UPLEFT, DOWNRIGHT, DOWNLEFT, NONE };
	DIR playerDir; DIR targDir;

	TileMap *map;

	// Движение
	sf::Vector2i targ; sf::Vector2i targT; // Координаты куда идти
	bool DirGoingFlag; int goneX, goneY;

	// Анимация
	float frame;
	sf::Sprite sprite;
	sf::Sprite effect;
};