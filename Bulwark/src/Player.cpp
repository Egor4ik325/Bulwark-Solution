#include "Player.h"

#include "DebugRect.h"
#include "UIManager.h"
#include "ItemManager.h"
#include "Program.h"
#include "UIInventoryCell.h"

UIInventory* Player::inventory = new UIInventory;

Player::Player()
{
	position = sf::Vector2f(13 * TILE_SIZE, 11 * TILE_SIZE);
	velocity = sf::Vector2f(0.f, 0.f);

	targ = sf::Vector2i(0.f, 0.f);
	playerDir = DIR::DOWN;
	frame = 0.f;
	
	going = false; Picking = false; DirGoingFlag = true;
	goneX = 0; goneY = 0;
	health = 20; 
	speed = 1.f;
	OnTile = false;
}

void Player::Update(float time)
{
	// Проверка на плитки или нет
	OnTile = ((int)position.x % TILE_SIZE == 0) & ((int)position.y % TILE_SIZE == 0);
	// Округленные данные 
	

	//////// Движение ////////
	UpdateMovement(time);

	if (velocity != sf::Vector2f(0.f, 0.f))
		position += (velocity * time);  //	Довавляем перемещения

	// Collision
	Collision();
	//////// Анимация ////////
	Animation(time);
	
	//////// Рисуем  /////////
	DebugRect::AddRect(sf::FloatRect(position.x, position.y, TILE_SIZE, TILE_SIZE), sf::Color::Red);
	
	sprite.setPosition(position);

	//////// Обнуляем ////////
	velocity = sf::Vector2f(0.f, 0.f);
	OnTile = 0;
}

void Player::UpdateMovement(float time)
{
	sf::Vector2i rPosition(GetRoundPos());
	sf::Vector2i tileMiddlePos = GetMiddleTilePos();

	// Переводим данные из буфера
	if (OnTile || rPosition == targ)
		targ = targT;

	// Сохраняем прошлые координаты
	if (!going)
	{
		goneX = tileMiddlePos.x * TILE_SIZE;
		goneY = tileMiddlePos.y * TILE_SIZE;
	}

	// Движемся
	if (going)
	{
		DebugRect::AddRect(sf::FloatRect(sf::Vector2f(targ), sf::Vector2f(TILE_SIZE, TILE_SIZE)), sf::Color::Blue);
		// Stop
		if (rPosition == targ)
		{
			going = false;
			targDir = DIR::NONE;
			position = sf::Vector2f(GetTilePos() * TILE_SIZE);
			position = sf::Vector2f(targ);

			if (Picking)
				PickUp();
		}

		// Позиция Таргета
		TargTileDir();

		// Движение по диагонале
		if (targDir == UPRIGHT || targDir == UPLEFT || targDir == DOWNRIGHT || targDir == DOWNLEFT)
		{
			if (DirGoingFlag)
			{
				if (targDir == UPRIGHT || targDir == DOWNRIGHT) // Вправо
				{
					float SVector = speed * time; 
					int NextTile = goneX + TILE_SIZE;   // Координаты куда прийдем

					// Проверка на то, что пришли или прошли
					if (rPosition.x + SVector >= NextTile)
					{
						goneX = position.x = NextTile;
						DirGoingFlag = false;
					}
					else
						velocity.x = speed;
				}
				else
					if (targDir == UPLEFT || targDir == DOWNLEFT) // Влево
					{
						float SVector = -speed * time; // Вектор перемещения
						int NextTile = goneX - TILE_SIZE;  // Координаты куда прийдем

						// Проверка на то, что пришли или прошли
						if (rPosition.x + SVector <= NextTile)
						{
							goneX = position.x = NextTile;
							DirGoingFlag = false;
						}
						else
							velocity.x = -speed;
					}
			}
			else
			{
				if (targDir == DOWNRIGHT || targDir == DOWNLEFT) // Вниз
				{
					float SVector = speed * time; // Вектор перемещения
					int NextTile = goneY + TILE_SIZE; // Координаты куда прийдем

					// Проверка на то, что пришли или прошли
					if (rPosition.y + SVector >= NextTile)
					{
						goneY = position.y = NextTile;
						DirGoingFlag = true;
					}
					else
						velocity.y = speed;
				}
				else
					if (targDir == UPRIGHT || targDir == UPLEFT) // Вверх
					{
						float SVector = -speed * time; // Вектор перемещения
						int NextTile = goneY - TILE_SIZE;  // Координаты куда прийдем

						// Проверка на то, что пришли или прошли
						if (rPosition.y + SVector <= NextTile)
						{
							goneY = position.y = NextTile;
							DirGoingFlag = true;
						}
						else
							velocity.y = -speed;
					}
			}
		}

		// Движение Горизонтально или Вертикально
		else if (targDir == RIGHT)   // Вправо
		{
			// Проверка на то, что пришли или прошли
			float SVector = speed * time;
			if (position.x + SVector > targ.x)
				position.x = targ.x;
			else
				velocity.x = speed;
			//
			goneX = tileMiddlePos.x * TILE_SIZE;
		}
		else if (targDir == LEFT)   // Влево
		{
			// Проверка на то, что пришли или прошли
			float SVector = -speed * time; 
			if (position.x + SVector < targ.x)
				position.x = targ.x;
			else
				velocity.x = -speed;
			//
			goneX = tileMiddlePos.x * TILE_SIZE;
		}
		else if (targDir == DOWN)   // Вниз
		{
			// Проверка на то, что пришли или прошли
			float SVector = speed * time; 
			if (position.y + SVector > targ.y)
				position.y = targ.y;
			else
				velocity.y = speed;
			//
			goneY = tileMiddlePos.y * TILE_SIZE;
		}
		else if (targDir == UP)   // Вверх
		{
			// Проверка на то, что пришли или прошли
			float SVector = -speed * time;
			if (position.y + SVector < targ.y)
				position.y = targ.y;
			else
				velocity.y = -speed;
			//
			goneY = tileMiddlePos.y * TILE_SIZE;
		}
	}

	//sf::Vector2i RPosition = GetPlayerRoundPos();
	//sf::Vector2i TilePos = GetPlayerTilePos();
	//
	//// Переводим данные из буфера
	//if (OnTile || RPosition == targ)
	//	targ = targT;
	//
	//// Сохраняем прошлые координаты
	//if (!Going)
	//{
	//	goneX = TilePos.x * TILE_SIZE;
	//	goneY = TilePos.y * TILE_SIZE;
	//}
	//
	//// Движемся
	//if (Going)
	//{
	//	DebugRect::AddRect(FloatRect(sf::Vector2f(targ), sf::Vector2f(TILE_SIZE, TILE_SIZE)), Color::Blue);
	//	// Stop
	//	if (RPosition == targ)
	//	{
	//		Stop();
	//		Position = Vector2f(targ);
	//
	//		if (Picking)
	//			PickUp();
	//	}
	//
	//	// Позиция Таргета
	//	TargTileDir();
	//
	//	// Движение по диагонале
	//	if (targDir == UPRIGHT || targDir == UPLEFT || targDir == DOWNRIGHT || targDir == DOWNLEFT)
	//	{
	//		if (DirGoingFlag)
	//		{
	//			if (targDir == UPRIGHT || targDir == DOWNRIGHT) // Вправо
	//			{
	//				float SVector = speed * time; // Вектор перемещения
	//				int NextTile = goneX + TILE_SIZE; // Координаты куда прийдем
	//
	//				// Проверка на то, что пришли или прошли
	//				if (RPosition.x + SVector >= NextTile)
	//				{
	//					goneX = Position.x = NextTile;
	//					DirGoingFlag = false;
	//				}
	//				else
	//					velocity.x = speed;
	//			}
	//			else
	//				if (targDir == UPLEFT || targDir == DOWNLEFT) // Влево
	//				{
	//					float SVector = -speed * time; // Вектор перемещения
	//					int NextTile = goneX - TILE_SIZE;  // Координаты куда прийдем
	//
	//					// Проверка на то, что пришли или прошли
	//					if (RPosition.x + SVector <= NextTile)
	//					{
	//						goneX = Position.x = NextTile;
	//						DirGoingFlag = false;
	//					}
	//					else
	//						velocity.x = -speed;
	//				}
	//		}
	//		else
	//		{
	//			if (targDir == DOWNRIGHT || targDir == DOWNLEFT) // Вниз
	//			{
	//				float SVector = speed * time; // Вектор перемещения
	//				int NextTile = goneY + TILE_SIZE; // Координаты куда прийдем
	//
	//				// Проверка на то, что пришли или прошли
	//				if (RPosition.y + SVector >= NextTile)
	//				{
	//					goneY = Position.y = NextTile;
	//					DirGoingFlag = true;
	//				}
	//				else
	//					velocity.y = speed;
	//			}
	//			else
	//				if (targDir == UPRIGHT || targDir == UPLEFT) // Вверх
	//				{
	//					float SVector = -speed * time; // Вектор перемещения
	//					int NextTile = goneY - TILE_SIZE;  // Координаты куда прийдем
	//
	//					// Проверка на то, что пришли или прошли
	//					if (RPosition.y + SVector <= NextTile)
	//					{
	//						goneY = Position.y = NextTile;
	//						DirGoingFlag = true;
	//					}
	//					else
	//						velocity.y = -speed;
	//				}
	//		}
	//	}
	//	// Движение Горизонтально или Вертикально
	//
	//	else if (targDir == RIGHT)   // Вправо
	//	{
	//		// Проверка на то, что пришли или прошли
	//		if (Position.x + (speed * time) > targ.x)
	//			Position.x = targ.x;
	//		else
	//			velocity.x = speed;
	//		goneX = TilePos.x * TILE_SIZE;
	//	}
	//	else if (targDir == LEFT)   // Влево
	//	{
	//		// Проверка на то, что пришли или прошли
	//		if (Position.x + (-speed * time) < targ.x)
	//			Position.x = targ.x;
	//		else
	//			velocity.x = -speed;
	//		goneX = TilePos.x * TILE_SIZE;
	//	}
	//	else if (targDir == DOWN)   // Вниз
	//	{
	//		// Проверка на то, что пришли или прошли
	//		if (Position.y + (speed * time) > targ.y)
	//			Position.y = targ.y;
	//		else
	//			velocity.y = speed;
	//		goneY = TilePos.y * TILE_SIZE;
	//	}
	//	else if (targDir == UP)   // Вверх
	//	{
	//		// Проверка на то, что пришли или прошли
	//		if (Position.y + (-speed * time) < targ.y)
	//			Position.y = targ.y;
	//		else
	//			velocity.y = -speed;
	//		goneY = TilePos.y * TILE_SIZE;
	//	}
	//}
}

void Player::TargTileDir()
{
	if (targ.x > position.x && targ.y > position.y)
		targDir = DOWNRIGHT;
	else if (targ.x < position.x && targ.y > position.y)
		targDir = DOWNLEFT;
	else if (targ.x > position.x && targ.y < position.y)
		targDir = UPRIGHT;
	else if (targ.x < position.x && targ.y < position.y)
		targDir = UPLEFT;
	else if (targ.x > position.x)
		targDir = RIGHT;
	else if (targ.x < position.x)
		targDir = LEFT;
	else if (targ.y > position.y)
		targDir = DOWN;
	else if (targ.y < position.y)
		targDir = UP;
	else
		targDir = NONE;
}

void Player::Collision()
{
	// Collision
	sf::Vector2i TilePos = GetTilePos();

	if (velocity.x > 0) {
		if (map->GetTileType(TilePos.x * TILE_SIZE + TILE_SIZE, TilePos.y * TILE_SIZE) == TileMap::WALL || map->GetTileType(TilePos.x * TILE_SIZE, TilePos.y * TILE_SIZE) == TileMap::WALL)
		{
			going = false; 
			position = sf::Vector2f(TilePos * TILE_SIZE);
			velocity = sf::Vector2f(0.f, 0.f);
			DebugRect::AddRect(sf::FloatRect(TilePos.x * TILE_SIZE + TILE_SIZE, TilePos.y * TILE_SIZE, TILE_SIZE, TILE_SIZE), sf::Color::Green);
		}
	}
	else
	if (velocity.x < 0) {
		if (map->GetTileType(TilePos.x * TILE_SIZE, TilePos.y * TILE_SIZE) == TileMap::WALL)
		{
			going = false;
			position = sf::Vector2f((TilePos.x + 1) * TILE_SIZE, TilePos.y * TILE_SIZE);
			velocity = sf::Vector2f(0.f, 0.f);
			DebugRect::AddRect(sf::FloatRect(TilePos.x * TILE_SIZE, TilePos.y * TILE_SIZE, TILE_SIZE, TILE_SIZE), sf::Color::Green);
		}
	}
	else
	if (velocity.y < 0) {
		if (map->GetTileType(TilePos.x * TILE_SIZE, TilePos.y * TILE_SIZE) == TileMap::WALL)
		{
			going = false;
			position = sf::Vector2f(TilePos.x * TILE_SIZE, (TilePos.y + 1) * TILE_SIZE);
			velocity = sf::Vector2f(0.f, 0.f);
			DebugRect::AddRect(sf::FloatRect(TilePos.x * TILE_SIZE, TilePos.y * TILE_SIZE, TILE_SIZE, TILE_SIZE), sf::Color::Green);
		}
	}
	else
	if (velocity.y > 0) {
		if (map->GetTileType(TilePos.x * TILE_SIZE, TilePos.y * TILE_SIZE + TILE_SIZE) == TileMap::WALL || map->GetTileType(TilePos.x * TILE_SIZE, TilePos.y * TILE_SIZE) == TileMap::WALL)
		{
			going = false;
			position = sf::Vector2f(TilePos * TILE_SIZE);
			velocity = sf::Vector2f(0.f, 0.f);
			DebugRect::AddRect(sf::FloatRect(TilePos.x * TILE_SIZE, TilePos.y * TILE_SIZE + TILE_SIZE, TILE_SIZE, TILE_SIZE), sf::Color::Green);
		}
	}
	/*
	// Если есть стена
	if (map->GetTileType(targ.x, targ.y) == TileMap::WALL)
	{
		Vector2i TilePosArr[8]
		{
			Vector2i(targ.x - TILE_SIZE, targ.y - TILE_SIZE),//[0]
			Vector2i(targ.x, targ.y - TILE_SIZE),		 //[1]
			Vector2i(targ.x + TILE_SIZE, targ.y - TILE_SIZE),//[2]
			Vector2i(targ.x + TILE_SIZE, targ.y),		 //[3]
			Vector2i(targ.x + TILE_SIZE, targ.y + TILE_SIZE),//[4]
			Vector2i(targ.x, targ.y + TILE_SIZE),		 //[5]
			Vector2i(targ.x - TILE_SIZE, targ.y + TILE_SIZE),//[6]
			Vector2i(targ.x - TILE_SIZE, targ.y)		 //[7]
		};

		TileMap::Type TypeArr[8]
		{
			map->GetTileType(TilePosArr[0]),
			map->GetTileType(TilePosArr[1]),		 // Верх
			map->GetTileType(TilePosArr[2]),
			map->GetTileType(TilePosArr[3]),		 // Право
			map->GetTileType(TilePosArr[4]),
			map->GetTileType(TilePosArr[5]),		 // Низ
			map->GetTileType(TilePosArr[6]),
			map->GetTileType(TilePosArr[7]),		 // Лево
		};

		switch (targDir)
		{
		case UP:
			if (TypeArr[5] != TileMap::WALL)
			{
				targ = TilePosArr[5]; break;
			}
			if (TypeArr[4] != TileMap::WALL)
			{
				targ = TilePosArr[4]; break;
			}
			if (TypeArr[6] != TileMap::WALL)
			{
				targ = TilePosArr[6]; break;
			}
			break;
		case DOWN:
			if (TypeArr[1] != TileMap::WALL)
			{
				targ = TilePosArr[1]; break;
			}
			if (TypeArr[0] != TileMap::WALL)
			{
				targ = TilePosArr[0]; break;
			}
			if (TypeArr[2] != TileMap::WALL)
			{
				targ = TilePosArr[2]; break;
			}
			break;
		case RIGHT:
			if (TypeArr[7] != TileMap::WALL)
			{
				targ = TilePosArr[7]; break;
			}
			if (TypeArr[0] != TileMap::WALL)
			{
				targ = TilePosArr[0]; break;
			}
			if (TypeArr[6] != TileMap::WALL)
			{
				targ = TilePosArr[6]; break;
			}
			break;
		case LEFT:
			if (TypeArr[3] != TileMap::WALL)
			{
				targ = TilePosArr[3]; break;
			}
			if (TypeArr[2] != TileMap::WALL)
			{
				targ = TilePosArr[2]; break;
			}
			if (TypeArr[4] != TileMap::WALL)
			{
				targ = TilePosArr[4]; break;
			}
			break;
		case UPRIGHT:
			if (TypeArr[5] != TileMap::WALL)
			{
				targ = TilePosArr[5]; break;
			}
			if (TypeArr[7] != TileMap::WALL)
			{
				targ = TilePosArr[7]; break;
			}
			if (TypeArr[6] != TileMap::WALL)
			{
				targ = TilePosArr[6]; break;
			}
			break;
		case UPLEFT:
			if (TypeArr[5] != TileMap::WALL)
			{
				targ = TilePosArr[5]; break;
			}
			if (TypeArr[3] != TileMap::WALL)
			{
				targ = TilePosArr[3]; break;
			}
			if (TypeArr[4] != TileMap::WALL)
			{
				targ = TilePosArr[4]; break;
			}
			break;
		case DOWNRIGHT:
			if (TypeArr[7] != TileMap::WALL)
			{
				targ = TilePosArr[7]; break;
			}
			if (TypeArr[1] != TileMap::WALL)
			{
				targ = TilePosArr[1]; break;
			}
			if (TypeArr[0] != TileMap::WALL)
			{
				targ = TilePosArr[0]; break;
			}
			break;
		case DOWNLEFT:
			if (TypeArr[1] != TileMap::WALL)
			{
				targ = TilePosArr[1]; break;
			}
			if (TypeArr[3] != TileMap::WALL)
			{
				targ = TilePosArr[3]; break;
			}
			if (TypeArr[2] != TileMap::WALL)
			{
				targ = TilePosArr[2]; break;
			}
			break;
		}
		targT = targ;
	}*/
}

void Player::Animation(float time)
{
	// Кадры идут, когда двигаешся 
	if (going)
		frame += 0.03 * time; 
	if (frame > 2)    frame = 0;
	
	// Стоим на месте с определенным направлением
	switch (playerDir)
	{
	case DOWN:
		sprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
		break;
	case UP:
		sprite.setTextureRect(sf::IntRect(16, 0, 16, 16));
		break;
	case RIGHT:
		sprite.setTextureRect(sf::IntRect(16 * 2, 0, 16, 16));
		break;
	case LEFT:
		sprite.setTextureRect(sf::IntRect(16 * 3, 0, 16, 16));
		break;
	}

	// Идем с определенным направлением
	if (velocity.y > 0)
	{
		playerDir = DOWN;
		sprite.setTextureRect(sf::IntRect(0, 16 * int(frame) + 16, 16, 16));
	}
	else if (velocity.y < 0)
	{
		playerDir = UP;
		sprite.setTextureRect(sf::IntRect(16, 16 * int(frame) + 16, 16, 16));
	}
	else if (velocity.x > 0)
	{
		playerDir = RIGHT;
		sprite.setTextureRect(sf::IntRect(32, 16 * int(frame), 16, 16));
	}
	else if (velocity.x < 0)
	{
		playerDir = LEFT;
		sprite.setTextureRect(sf::IntRect(48, 16 * int(frame), 16, 16));
	}
}

void Player::Draw(sf::RenderTarget & target)
{
	// Автоматическая передача (getTransform) при target.draw(...)
	if (going)
		target.draw(effect);
	target.draw(sprite);
}

void Player::SetTargetedTile(int x, int y)
{
	going = true;
	Picking = false;

	// Находим точные координаты плитки
	targT.x = ((int)x / TILE_SIZE) * TILE_SIZE;
	targT.y = ((int)y / TILE_SIZE) * TILE_SIZE;

	// Место куда идем
	effect.setPosition(targT.x, targT.y);
}

void Player::MoveBy(int TileX, int TileY)
{
	going = true;

	sf::Vector2i TilePos = GetTilePos();
	SetTargetedTile((TilePos.x + TileX) * TILE_SIZE, (TilePos.y + TileY) * TILE_SIZE);
}

void Player::PickUp()
{
	Picking = false;

	Item* item = ItemManager::GetItem(GetMiddlePos());
	if (item == nullptr)
		return;
	if (item->OnGround == false)
		return;

	UIInventoryCell* cell = inventory->GetEmptyCell();
	if (cell == nullptr)
		return;
	
	cell->SetItem(item);
}

void Player::DropUp(UIInventoryCell * cell)
{
	Item* item = cell->GetItem();
	if (item == nullptr) return;

	item->OnGround = true;
	item->SetTilePosition(sf::Vector2f(GetMiddleTilePos()));
	cell->RemoveItem();
}

void Player::Stop()
{
	SetTargetedTile(GetMiddleTilePos().x, GetMiddleTilePos().y);
}

void Player::SetTexture(sf::Texture & playerTex)
{
	sprite.setTexture(playerTex); sprite.setTextureRect(sf::IntRect(0, 0, 16, 16)); sprite.setScale(4, 4);
	effect.setTexture(playerTex); effect.setTextureRect(sf::IntRect(16, 64, 16, 16)); effect.setScale(4, 4);
}

void Player::SetTileMap(TileMap & map)
{
	this->map = &map;
}

sf::Vector2i Player::GetRoundPos() const
{
	sf::Vector2i rPosition(round(position.x), round(position.y));         // Округленные координаты
	return rPosition;
}

sf::Vector2i Player::GetTilePos() const
{
	sf::Vector2i tilePos;   // Координаты плитки
	tilePos = sf::Vector2i(position.x / TILE_SIZE, position.y / TILE_SIZE);

	return tilePos;
}

sf::Vector2i Player::GetMiddleTilePos() const
{
	sf::Vector2f middlePos = GetMiddlePos();
	sf::Vector2i tilePos(middlePos.x / TILE_SIZE, middlePos.y / TILE_SIZE);
	return tilePos;
}

sf::Vector2f Player::GetMiddlePos() const
{
	sf::Vector2f tileSizeHalf(TILE_SIZE / 2, TILE_SIZE / 2);
	return position + tileSizeHalf;
}

sf::Vector2f Player::GetPosition() const
{
	return position;
}

