#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "TileMap.h"

class Bulwark
{
private:
	Player player;  
	TileMap map;
	sf::View view;
	sf::Clock clock; float time;
	//std::list <Effect> Effects;  Manager
	UIInventory* inventory;

	UIScreen* menuScreen;
	UIScreen* gameScreen;
	UIBase* startButtonAddress;
	UIBase* quitButtonAddress;
	
public:
	bool gameIsPlay;

	Bulwark();
	void pollEnvent();
	void update();
	void draw();
	
	void pollEnventMenu();
	void updateMenu();
	void drawMenu();

private:
	void createUI();
	void drawText(const char* text, float data, sf::Vector2i position, const char* count = "%.4f");
};

