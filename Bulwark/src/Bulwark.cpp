#include "Bulwark.h"

#include "Program.h"
#include "DebugRect.h"
#include "UIManager.h"
#include "ItemManager.h"
#include "Content.h"

#include "UIWindow.h"
#include "Item.h"
#include "UIInventory.h"
#include "UIInventoryCell.h"
#include "UIButton.h"

using namespace sf;

Bulwark::Bulwark()
{
	// Меню
	gameIsPlay = false;
	// Карта
	map.loadFromFile(ContentManager::CONTENT_DIR + "Map.tmx");   // Карта 30x30
	map.setTileSize(TILE_SIZE);
	map.setTileType(3, TileMap::WALL); map.setTileType(5, TileMap::WALL); map.setTileType(10, TileMap::WALL);

	// Параметры вида
	view.reset(FloatRect(0.0f, 0.0f, WIDTH, HEIGHT));
	//view.setViewport(FloatRect(0.0f, 0.0f, 0.5f, 0.5f)); // Двигаем окно
	//view.setSize(1280, 800);                             // Маштабируем
	//view.reset(FloatRect(offsetX, offsetY, WIDTH, HEIGHT)); // Движение
	//Sprite Map; Map.setTexture(Content::MapTexture); Map.setTILE_SIZE(4, 4); Map.setTextureRect(IntRect(16, 0, 16, 16));
	player.setTexture(ContentManager::playerTexture);
	player.setTileMap(map);

	DebugRect::enabled = true;

	createUI();
	
	// Яблоки
	Item* item = new Item();
	(*item).construct(ContentManager::itemSet, sf::IntRect(0, 0, TILE_SIZE, TILE_SIZE));
	ItemManager::addItem(item);

	Item* item2 = new Item();
	(*item2).construct(ContentManager::itemSet, sf::IntRect(0, 0, TILE_SIZE, TILE_SIZE));
	item2->setTilePosition(sf::Vector2f(10, 12));
	ItemManager::addItem(item2);

	// Добавляем яблоко в инвентарь
	Player::inventory->getCell(0)->setItem(item);
}

void Bulwark::createUI()
{
	UIScreen* menu = new UIScreen(); 
	menuScreen = menu;
	UIButton* startButton = new UIButton("Start", sf::Color::Black, ContentManager::font);
	startButton->setPosition(WIDTH / 2 - 100, 350);
	startButton->setColor(sf::Color::Green);
	startButton->setScreenParent(menu);
	menu->addControl(startButton);
	
	startButtonAddress = startButton;

	UIButton* quitButton = new UIButton("Quit", sf::Color::Black, ContentManager::font);
	quitButton->setPosition(WIDTH / 2 - 100, 470);
	quitButton->setColor(sf::Color::Green);
	quitButton->setScreenParent(menu);
	menu->addControl(quitButton);
	quitButtonAddress = quitButton;

	menu->active = true;
	UIManager::addScreen(menu);

	UIScreen* game = new UIScreen(); 
	gameScreen = game;
	game->addControl(Player::inventory);
	game->active = false;
	UIManager::addScreen(game);

	Player::inventory->construct();
	Player::inventory->setScreenParent(game);
}

void Bulwark::pollEnvent()
{
	Event event;
	while (window.pollEvent(event))
	{
		if (event.type == Event::Closed)
			window.close();
		if (event.type == Event::MouseButtonPressed)
		{
			if (event.key.code == Mouse::Left)
			{
				// Если курсор не находится над интерфейсом
				if (UIManager::getMouseOver() == nullptr)
				{
					sf::Vector2f MousePos = window.mapPixelToCoords(Mouse::getPosition(window));
					player.setTargetedTile(MousePos.x, MousePos.y);
				}
			}
			if (event.key.code == Mouse::Right)
			{
				// Если курсор не находится над интерфейсом
				if (UIManager::getMouseOver() == nullptr)
				{
					sf::Vector2f MousePos = window.mapPixelToCoords(Mouse::getPosition(window));
					player.setTargetedTile(MousePos.x, MousePos.y);
					player.pking = true;
				}
			}
		}
		if (event.type == sf::Event::MouseLeft)
		{

		}
		if (event.type == sf::Event::MouseEntered)
		{

		}
		// Движение колёсика мыши
		if (event.type == sf::Event::MouseWheelMoved)
		{
			if (event.mouseWheel.delta == 1 && Player::inventory->selectedCell >= 1)
				--Player::inventory->selectedCell;
			else if (event.mouseWheel.delta == -1 && Player::inventory->selectedCell <= 3)
				++Player::inventory->selectedCell;
		}
		if (Keyboard::isKeyPressed(Keyboard::Num1))
			Player::inventory->selectedCell = 0;	
		if (Keyboard::isKeyPressed(Keyboard::Num2))
			Player::inventory->selectedCell = 1;
		if (Keyboard::isKeyPressed(Keyboard::Num3))
			Player::inventory->selectedCell = 2;
		if (Keyboard::isKeyPressed(Keyboard::Num4))
			Player::inventory->selectedCell = 3;
		if (Keyboard::isKeyPressed(Keyboard::Num5))
			Player::inventory->selectedCell = 4;
		
		if (Keyboard::isKeyPressed(Keyboard::Key::Q))
		{
			UIInventoryCell* cell = Player::inventory->getSelectedCell();
			player.dropUp(cell);
		}
	}
}

void Bulwark::update()
{
	// Время
	float deltaTime = clock.getElapsedTime().asSeconds();
	if (deltaTime > 1) deltaTime = 0;
	time = deltaTime;
	// Начинается отсчёт времени
	deltaTime *= 60;
	clock.restart();

	// Обновление данных
	UIManager::update();
	player.update(deltaTime);

	// Вид
	window.setView(view);
	view.setCenter(player.getPosition());

	// Мышь
	sf::Vector2f MousePos = window.mapPixelToCoords(Mouse::getPosition(window));
	//std::cout << "MX " << MousePos.x / 64 << " MY " << MousePos.y / TILE_SIZE << std::endl;
}

void Bulwark::draw()
{
	// Map
	map.draw(window);
	// Player
	player.draw(window);
	// UI
	UIManager::draw(window);
	// Debug
	DebugRect::draw(window);
	// Item
	ItemManager::draw(window);

	// Текст	
	drawText("X ", player.getPosition().x / TILE_SIZE, Vector2i(WIDTH - 154, 550));
	drawText("Y ", player.getPosition().y / TILE_SIZE, Vector2i(WIDTH - 154, 580));
	drawText("FPS ", 1 / time, Vector2i(WIDTH - 134, 0), "%.0f");
}

void Bulwark::drawText(const char* text, float data, const sf::Vector2i position, const char* count)
{
	sf::Text Text; Text.setString(""); Text.setFont(ContentManager::font); Text.setCharacterSize(40); Text.setFillColor(Color::Black);
	char temp[10];  sprintf_s(temp, count, data); // Первеодим float -> string

	Text.setString(text + std::string(temp));
	Text.setPosition((sf::Vector2f)position);
	window.draw(Text, GetViewTransformOffSet());
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Bulwark::pollEnventMenu()
{
	Event event;
	while (window.pollEvent(event))
	{
		if (event.type == Event::Closed)
			window.close();
		if (event.type == Event::MouseButtonPressed)
		{
			if (event.key.code == Mouse::Left)
			{
				UIBase* over = UIManager::getMouseOver();
				if (over != nullptr)
				{
					if (over == startButtonAddress)
					{
						gameIsPlay = true;
						UIManager::deleteScreen(menuScreen);
						gameScreen->active = true;
					}
					if (over == quitButtonAddress)
					{
						window.close();
					}
				}
			
			}
			if (event.key.code == Mouse::Right)
			{
				// Если курсор не находится над интерфейсом
			
			}
		}
	}
}

void Bulwark::updateMenu()
{
	// Обновление данных
	UIManager::update();
}

void Bulwark::drawMenu()
{
	// Background
	Sprite grass(ContentManager::tileSet, sf::IntRect(0, 16 * 2, 16, 16)); 
	grass.setScale(sf::Vector2f(4, 4));
	for (int Y = 0; Y < HEIGHT/TILE_SIZE; Y++)
	{
		for (int X = 0; X  < WIDTH/TILE_SIZE; X++)
		{
			int x = X * TILE_SIZE;
			int y = Y * TILE_SIZE;

			grass.setPosition(x, y);
			window.draw(grass);
		}
	}
	// Logo
	sf::Sprite logo(ContentManager::menuTexture);
	logo.setPosition(0, 0);
	window.draw(logo);
	// UI
	UIManager::draw(window);
	// Item
	ItemManager::draw(window);
	// Debug
	DebugRect::draw(window);
}



