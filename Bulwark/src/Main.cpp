#include "SFML/Graphics.hpp"
#include <iostream>

#include "Bulwark.h"
#include "Content.h"
#include "Program.h"

int main()
{
	// Window setings
	window.create(sf::VideoMode(WIDTH, HEIGHT), "Bulwark", sf::Style::Close);
	window.setPosition(sf::Vector2i(256, 16));	
	window.setVerticalSyncEnabled(true); //VSYNC
	window.setFramerateLimit(10);
	// Cursor
	window.setMouseCursorVisible(true);
	window.setMouseCursorGrabbed(false);
	sf::Cursor cursor; cursor.loadFromSystem(sf::Cursor::Arrow);
	window.setMouseCursor(cursor);
	//system("help");

	// Content
	ContentManager::loadContent();
	
	// Main class
	Bulwark game;

	std::cout << "Bulwark size: " << sizeof(game) << " bytes" << std::endl;
	
	// Main loop
	while (window.isOpen())
	{
		
		// Clear	
		window.clear(sf::Color::White);
		//system("cls");

		if (game.gameIsPlay) {
			// Input 
			game.pollEnvent();
			// Update
			game.update();
			// Draw
			game.draw();
		}
		else {
			game.pollEnventMenu();
			game.updateMenu();
			game.drawMenu();
		}

		window.display();
	}
	return 0;
}
