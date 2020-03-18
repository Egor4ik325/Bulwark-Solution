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
	map.LoadFromFile(ContentManager::CONTENT_DIR + "Map.tmx");   // Карта 30x30
	map.SetTileSize(TILE_SIZE);
	map.SetTileType(3, TileMap::WALL); map.SetTileType(5, TileMap::WALL); map.SetTileType(10, TileMap::WALL);

	// Параметры вида
	view.reset(FloatRect(0.0f, 0.0f, WIDTH, HEIGHT));
	//view.setViewport(FloatRect(0.0f, 0.0f, 0.5f, 0.5f)); // Двигаем окно
	//view.setSize(1280, 800);                             // Маштабируем
	//view.reset(FloatRect(offsetX, offsetY, WIDTH, HEIGHT)); // Движение
	//Sprite Map; Map.setTexture(Content::MapTexture); Map.setTILE_SIZE(4, 4); Map.setTextureRect(IntRect(16, 0, 16, 16));
	player.SetTexture(ContentManager::PlayerTexture);
	player.SetTileMap(map);

	DebugRect::Enabled = true;

	CreateUI();
	
	// Яблоки
	Item* item = new Item();
	(*item).Construct(ContentManager::ItemSet, sf::IntRect(0, 0, TILE_SIZE, TILE_SIZE));
	ItemManager::AddItem(item);

	Item* item2 = new Item();
	(*item2).Construct(ContentManager::ItemSet, sf::IntRect(0, 0, TILE_SIZE, TILE_SIZE));
	item2->SetTilePosition(sf::Vector2f(10, 12));
	ItemManager::AddItem(item2);

	// Добавляем яблоко в инвентарь
	Player::inventory->GetCell(0)->SetItem(item);
}

void Bulwark::CreateUI()
{
	UIScreen* menu = new UIScreen(); 
	menuScreen = menu;
	UIButton* startButton = new UIButton("Start", sf::Color::Black, ContentManager::Font);
	startButton->setPosition(WIDTH / 2 - 100, 350);
	startButton->SetColor(sf::Color::Green);
	startButton->setScreenParent(menu);
	menu->AddControl(startButton);
	
	startButtonAddress = startButton;

	UIButton* quitButton = new UIButton("Quit", sf::Color::Black, ContentManager::Font);
	quitButton->setPosition(WIDTH / 2 - 100, 470);
	quitButton->SetColor(sf::Color::Green);
	quitButton->setScreenParent(menu);
	menu->AddControl(quitButton);
	quitButtonAddress = quitButton;

	menu->active = true;
	UIManager::AddScreen(menu);

	UIScreen* game = new UIScreen(); 
	gameScreen = game;
	game->AddControl(Player::inventory);
	game->active = false;
	UIManager::AddScreen(game);

	Player::inventory->Construct();
	Player::inventory->setScreenParent(game);
}

void Bulwark::PollEnvent()
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
				if (UIManager::GetMouseOver() == nullptr)
				{
					sf::Vector2f MousePos = window.mapPixelToCoords(Mouse::getPosition(window));
					player.SetTargetedTile(MousePos.x, MousePos.y);
				}
			}
			if (event.key.code == Mouse::Right)
			{
				// Если курсор не находится над интерфейсом
				if (UIManager::GetMouseOver() == nullptr)
				{
					sf::Vector2f MousePos = window.mapPixelToCoords(Mouse::getPosition(window));
					player.SetTargetedTile(MousePos.x, MousePos.y);
					player.Picking = true;
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
			UIInventoryCell* cell = Player::inventory->GetSelectedCell();
			player.DropUp(cell);
		}
	}
}

void Bulwark::Update()
{
	// Время
	float deltaTime = clock.getElapsedTime().asSeconds();
	if (deltaTime > 1) deltaTime = 0;
	time = deltaTime;
	// Начинается отсчёт времени
	deltaTime *= 60;
	clock.restart();

	// Обновление данных
	UIManager::Update();
	player.Update(deltaTime);

	// Вид
	window.setView(view);
	view.setCenter(player.GetPosition());

	// Мышь
	sf::Vector2f MousePos = window.mapPixelToCoords(Mouse::getPosition(window));
	//std::cout << "MX " << MousePos.x / 64 << " MY " << MousePos.y / TILE_SIZE << std::endl;
}

void Bulwark::Draw()
{
	// Map
	map.Draw(window);
	// Player
	player.Draw(window);
	// UI
	UIManager::Draw(window);
	// Debug
	DebugRect::Draw(window);
	// Item
	ItemManager::Draw(window);

	// Текст	
	DrawText("X ", player.GetPosition().x / TILE_SIZE, Vector2i(WIDTH - 154, 550));
	DrawText("Y ", player.GetPosition().y / TILE_SIZE, Vector2i(WIDTH - 154, 580));
	DrawText("FPS ", 1 / time, Vector2i(WIDTH - 134, 0), "%.0f");
}

void Bulwark::DrawText(const char* text, float data, const sf::Vector2i position, const char* count)
{
	sf::Text Text; Text.setString(""); Text.setFont(ContentManager::Font); Text.setCharacterSize(40); Text.setFillColor(Color::Black);
	char temp[10];  sprintf_s(temp, count, data); // Первеодим float -> string

	Text.setString(text + std::string(temp));
	Text.setPosition((sf::Vector2f)position);
	window.draw(Text, GetViewTransformOffSet());
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Bulwark::PollEnventMenu()
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
				UIBase* over = UIManager::GetMouseOver();
				if (over != nullptr)
				{
					if (over == startButtonAddress)
					{
						gameIsPlay = true;
						UIManager::DeleteScreen(menuScreen);
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

void Bulwark::UpdateMenu()
{
	// Обновление данных
	UIManager::Update();
}

void Bulwark::DrawMenu()
{
	// Background
	Sprite grass(ContentManager::TileSet, sf::IntRect(0, 16 * 2, 16, 16)); 
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
	sf::Sprite logo(ContentManager::MenuTexture);
	logo.setPosition(0, 0);
	window.draw(logo);
	// UI
	UIManager::Draw(window);
	// Item
	ItemManager::Draw(window);
	// Debug
	DebugRect::Draw(window);
}



