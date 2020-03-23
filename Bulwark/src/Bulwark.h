#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "TileMap.h"

class TileMap;
class UIScreen;

class Bulwark // УСТРАНИТЬ ОШИБКУ ИЗ ВЕКТОРА
{
private:
	Player player;
	TileMap map;
	sf::View view;
	sf::Clock clock; float time;
	//std::list <Effect> Effects;  Manager

	// Указатели - храним адреса (не null)
	const UIScreen* menuScreen;
	UIScreen* gameScreen;
	const UIBase* startButtonAddress;
	const UIBase* quitButtonAddress;
	
	bool gamePlay;
public:

	Bulwark();
	void pollEnvent();
	void update();
	void draw();
	
	void pollEnventMenu();
	void updateMenu();
	void drawMenu();

	bool isGamePlay() const;
private:
	void createUI();
	void drawText(const char* text, float data, sf::Vector2i position, const char* count = "%.4f");
};

