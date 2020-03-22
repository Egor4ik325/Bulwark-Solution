#pragma once
#include <SFML/Graphics.hpp>
#include "TileMap.h"
#include "UIInventory.h"

class Player
{
private:
	sf::Vector2f position;      // Координаты	
	sf::Vector2f velocity;      // Скорость
	
	const TileMap *map;         // Карта - только для чтения данных
	const sf::Texture *texture; // Текстура игрока - только для чтения данных

	bool going;
	bool picking;
	bool onTile;

	float speed;
	int health;

	enum DIR { UP, DOWN, RIGHT, LEFT, UPRIGHT, UPLEFT, DOWNRIGHT, DOWNLEFT, NONE };

	DIR playerDir; DIR targDir;

	// Движение
	sf::Vector2i targ; 
	sf::Vector2i targT; // Координаты куда идти
	bool goingDirFlag; 
	int goneX, goneY;

	// Анимация
	float frame;
	sf::Sprite sprite;
	sf::Sprite effect;

public:
	UIInventory inventory;      // Инвентарь, для каждого игрока - отдельный
public:
	Player();
	// Передача по ссылке, тк необходимо устранить ошибки
	Player(const sf::Texture& texture); // СДЕЛАТЬ ОБЯЗАТЕЛЬНЫМ - нет так как нельза передавать nullptr или какой нибудь другой адрес -- можно передать только какую нибудь переменную от которой будет получен адресс

	void update(float time);
	void draw(sf::RenderTarget & target);
	
	void pickUp();
	void dropUp(UIInventoryCell* cell);
	void stop();
	
	void moveBy(int TileX, int TileY);

	void goTo(int x, int y);
	void setTexture(const sf::Texture &playerTex); 
	void setTileMap(const TileMap &map);
	void setPicking(bool picking);

	bool isPicking() const;
	sf::Vector2f getPosition() const;
	sf::Vector2i getRoundPos() const;
	sf::Vector2i getTilePos() const;	
	sf::Vector2i getMiddleTilePos() const;
	sf::Vector2f getMiddlePos() const;

private:
	void updateMovement(float time);
	void targTileDiraction();
	void collision();
	void animation(float time);


};