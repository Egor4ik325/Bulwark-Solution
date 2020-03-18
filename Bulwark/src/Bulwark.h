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
	
	UIScreen* menuScreen;
	UIScreen* gameScreen;
	UIBase* startButtonAddress;
	UIBase* quitButtonAddress;
	
public:
	bool gameIsPlay;

	Bulwark();
	void PollEnvent();
	void Update();
	void Draw();
	
	void PollEnventMenu();
	void UpdateMenu();
	void DrawMenu();

private:
	void CreateUI();
	void DrawText(const char* text, float data, sf::Vector2i position, const char* count = "%.4f");
};

