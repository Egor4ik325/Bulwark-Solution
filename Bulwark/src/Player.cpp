#include "Player.h"
#include "TileMap.h"
#include "DebugRect.h"
#include "UIManager.h"
#include "ItemManager.h"
#include "Global.h"
#include "InventoryCell.h"

Player::Player()
{
	// Properties
	position = sf::Vector2f(13 * TILE_SIZE, 11 * TILE_SIZE);
	playerDir = DIR::DOWN;
	frame = 0.f;
	health = 20;
	speed = 1.f;
	// Flags
	goingDirFlag = true;
}

Player::Player(const sf::Texture& texture) : Player()
{
	this->texture = &texture;
	// Texture
	sprite.setTexture(texture); sprite.setTextureRect(sf::IntRect(0, 0, 16, 16)); sprite.setScale(4, 4);
	effect.setTexture(texture); effect.setTextureRect(sf::IntRect(16, 64, 16, 16)); effect.setScale(4, 4);
}

void Player::update(float time)
{
	// Checks
	onTile = ((int)position.x % TILE_SIZE == 0) & ((int)position.y % TILE_SIZE == 0);

	// Movement
	updateMovement(time);

	if (velocity != sf::Vector2f(0.f, 0.f))
		position += (velocity * time);  //	��������� �����������

	// Collision
	collision();
	
	// Animation
	animation(time);
	
	// Drawing
	DebugRect::addRect(sf::FloatRect(position.x, position.y, TILE_SIZE, TILE_SIZE), sf::Color::Red);
	
	sprite.setPosition(position);

	// Equation to zero
	velocity = sf::Vector2f(0.f, 0.f);
	onTile = 0;
}

void Player::updateMovement(float time)
{
	sf::Vector2i rPosition(getRoundPos());
	sf::Vector2i tileMiddlePos = getMiddleTilePos();

	// ��������� ������ �� ������
	if (onTile || rPosition == targ)
		targ = targT;

	// ��������� ������� ����������
	if (!going)
	{
		goneX = tileMiddlePos.x * TILE_SIZE;
		goneY = tileMiddlePos.y * TILE_SIZE;
	}

	// ��������
	if (going)
	{
		DebugRect::addRect(sf::FloatRect(sf::Vector2f(targ), sf::Vector2f(TILE_SIZE, TILE_SIZE)), sf::Color::Blue);
		// Stop
		if (rPosition == targ)
		{
			going = false;
			targDir = DIR::NONE;
			position = sf::Vector2f(getTilePos() * TILE_SIZE);
			position = sf::Vector2f(targ);

			if (picking)
				pickUp();
		}

		// ������� �������
		targTileDiraction();

		// �������� �� ���������
		if (targDir == UPRIGHT || targDir == UPLEFT || targDir == DOWNRIGHT || targDir == DOWNLEFT)
		{
			if (goingDirFlag)
			{
				if (targDir == UPRIGHT || targDir == DOWNRIGHT) // ������
				{
					float SVector = speed * time; 
					int NextTile = goneX + TILE_SIZE;   // ���������� ���� �������

					// �������� �� ��, ��� ������ ��� ������
					if (rPosition.x + SVector >= NextTile)
					{
						goneX = position.x = NextTile;
						goingDirFlag = false;
					}
					else
						velocity.x = speed;
				}
				else
					if (targDir == UPLEFT || targDir == DOWNLEFT) // �����
					{
						float SVector = -speed * time; // ������ �����������
						int NextTile = goneX - TILE_SIZE;  // ���������� ���� �������

						// �������� �� ��, ��� ������ ��� ������
						if (rPosition.x + SVector <= NextTile)
						{
							goneX = position.x = NextTile;
							goingDirFlag = false;
						}
						else
							velocity.x = -speed;
					}
			}
			else
			{
				if (targDir == DOWNRIGHT || targDir == DOWNLEFT) // ����
				{
					float SVector = speed * time; // ������ �����������
					int NextTile = goneY + TILE_SIZE; // ���������� ���� �������

					// �������� �� ��, ��� ������ ��� ������
					if (rPosition.y + SVector >= NextTile)
					{
						goneY = position.y = NextTile;
						goingDirFlag = true;
					}
					else
						velocity.y = speed;
				}
				else
					if (targDir == UPRIGHT || targDir == UPLEFT) // �����
					{
						float SVector = -speed * time; // ������ �����������
						int NextTile = goneY - TILE_SIZE;  // ���������� ���� �������

						// �������� �� ��, ��� ������ ��� ������
						if (rPosition.y + SVector <= NextTile)
						{
							goneY = position.y = NextTile;
							goingDirFlag = true;
						}
						else
							velocity.y = -speed;
					}
			}
		}

		// �������� ������������� ��� �����������
		else if (targDir == RIGHT)   // ������
		{
			// �������� �� ��, ��� ������ ��� ������
			float SVector = speed * time;
			if (position.x + SVector > targ.x)
				position.x = targ.x;
			else
				velocity.x = speed;
			//
			goneX = tileMiddlePos.x * TILE_SIZE;
		}
		else if (targDir == LEFT)   // �����
		{
			// �������� �� ��, ��� ������ ��� ������
			float SVector = -speed * time; 
			if (position.x + SVector < targ.x)
				position.x = targ.x;
			else
				velocity.x = -speed;
			//
			goneX = tileMiddlePos.x * TILE_SIZE;
		}
		else if (targDir == DOWN)   // ����
		{
			// �������� �� ��, ��� ������ ��� ������
			float SVector = speed * time; 
			if (position.y + SVector > targ.y)
				position.y = targ.y;
			else
				velocity.y = speed;
			//
			goneY = tileMiddlePos.y * TILE_SIZE;
		}
		else if (targDir == UP)   // �����
		{
			// �������� �� ��, ��� ������ ��� ������
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
	//// ��������� ������ �� ������
	//if (OnTile || RPosition == targ)
	//	targ = targT;
	//
	//// ��������� ������� ����������
	//if (!Going)
	//{
	//	goneX = TilePos.x * TILE_SIZE;
	//	goneY = TilePos.y * TILE_SIZE;
	//}
	//
	//// ��������
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
	//	// ������� �������
	//	TargTileDir();
	//
	//	// �������� �� ���������
	//	if (targDir == UPRIGHT || targDir == UPLEFT || targDir == DOWNRIGHT || targDir == DOWNLEFT)
	//	{
	//		if (DirGoingFlag)
	//		{
	//			if (targDir == UPRIGHT || targDir == DOWNRIGHT) // ������
	//			{
	//				float SVector = speed * time; // ������ �����������
	//				int NextTile = goneX + TILE_SIZE; // ���������� ���� �������
	//
	//				// �������� �� ��, ��� ������ ��� ������
	//				if (RPosition.x + SVector >= NextTile)
	//				{
	//					goneX = Position.x = NextTile;
	//					DirGoingFlag = false;
	//				}
	//				else
	//					velocity.x = speed;
	//			}
	//			else
	//				if (targDir == UPLEFT || targDir == DOWNLEFT) // �����
	//				{
	//					float SVector = -speed * time; // ������ �����������
	//					int NextTile = goneX - TILE_SIZE;  // ���������� ���� �������
	//
	//					// �������� �� ��, ��� ������ ��� ������
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
	//			if (targDir == DOWNRIGHT || targDir == DOWNLEFT) // ����
	//			{
	//				float SVector = speed * time; // ������ �����������
	//				int NextTile = goneY + TILE_SIZE; // ���������� ���� �������
	//
	//				// �������� �� ��, ��� ������ ��� ������
	//				if (RPosition.y + SVector >= NextTile)
	//				{
	//					goneY = Position.y = NextTile;
	//					DirGoingFlag = true;
	//				}
	//				else
	//					velocity.y = speed;
	//			}
	//			else
	//				if (targDir == UPRIGHT || targDir == UPLEFT) // �����
	//				{
	//					float SVector = -speed * time; // ������ �����������
	//					int NextTile = goneY - TILE_SIZE;  // ���������� ���� �������
	//
	//					// �������� �� ��, ��� ������ ��� ������
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
	//	// �������� ������������� ��� �����������
	//
	//	else if (targDir == RIGHT)   // ������
	//	{
	//		// �������� �� ��, ��� ������ ��� ������
	//		if (Position.x + (speed * time) > targ.x)
	//			Position.x = targ.x;
	//		else
	//			velocity.x = speed;
	//		goneX = TilePos.x * TILE_SIZE;
	//	}
	//	else if (targDir == LEFT)   // �����
	//	{
	//		// �������� �� ��, ��� ������ ��� ������
	//		if (Position.x + (-speed * time) < targ.x)
	//			Position.x = targ.x;
	//		else
	//			velocity.x = -speed;
	//		goneX = TilePos.x * TILE_SIZE;
	//	}
	//	else if (targDir == DOWN)   // ����
	//	{
	//		// �������� �� ��, ��� ������ ��� ������
	//		if (Position.y + (speed * time) > targ.y)
	//			Position.y = targ.y;
	//		else
	//			velocity.y = speed;
	//		goneY = TilePos.y * TILE_SIZE;
	//	}
	//	else if (targDir == UP)   // �����
	//	{
	//		// �������� �� ��, ��� ������ ��� ������
	//		if (Position.y + (-speed * time) < targ.y)
	//			Position.y = targ.y;
	//		else
	//			velocity.y = -speed;
	//		goneY = TilePos.y * TILE_SIZE;
	//	}
	//}
}

void Player::targTileDiraction()
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

void Player::collision()
{
	// Collision
	sf::Vector2i TilePos = getTilePos();

	if (velocity.x > 0) {
		if (map->getTileType(TilePos.x * TILE_SIZE + TILE_SIZE, TilePos.y * TILE_SIZE) == TileMap::WALL || map->getTileType(TilePos.x * TILE_SIZE, TilePos.y * TILE_SIZE) == TileMap::WALL)
		{
			going = false; 
			position = sf::Vector2f(TilePos * TILE_SIZE);
			velocity = sf::Vector2f(0.f, 0.f);
			DebugRect::addRect(sf::FloatRect(TilePos.x * TILE_SIZE + TILE_SIZE, TilePos.y * TILE_SIZE, TILE_SIZE, TILE_SIZE), sf::Color::Green);
		}
	}
	else
	if (velocity.x < 0) {
		if (map->getTileType(TilePos.x * TILE_SIZE, TilePos.y * TILE_SIZE) == TileMap::WALL)
		{
			going = false;
			position = sf::Vector2f((TilePos.x + 1) * TILE_SIZE, TilePos.y * TILE_SIZE);
			velocity = sf::Vector2f(0.f, 0.f);
			DebugRect::addRect(sf::FloatRect(TilePos.x * TILE_SIZE, TilePos.y * TILE_SIZE, TILE_SIZE, TILE_SIZE), sf::Color::Green);
		}
	}
	else
	if (velocity.y < 0) {
		if (map->getTileType(TilePos.x * TILE_SIZE, TilePos.y * TILE_SIZE) == TileMap::WALL)
		{
			going = false;
			position = sf::Vector2f(TilePos.x * TILE_SIZE, (TilePos.y + 1) * TILE_SIZE);
			velocity = sf::Vector2f(0.f, 0.f);
			DebugRect::addRect(sf::FloatRect(TilePos.x * TILE_SIZE, TilePos.y * TILE_SIZE, TILE_SIZE, TILE_SIZE), sf::Color::Green);
		}
	}
	else
	if (velocity.y > 0) {
		if (map->getTileType(TilePos.x * TILE_SIZE, TilePos.y * TILE_SIZE + TILE_SIZE) == TileMap::WALL || map->getTileType(TilePos.x * TILE_SIZE, TilePos.y * TILE_SIZE) == TileMap::WALL)
		{
			going = false;
			position = sf::Vector2f(TilePos * TILE_SIZE);
			velocity = sf::Vector2f(0.f, 0.f);
			DebugRect::addRect(sf::FloatRect(TilePos.x * TILE_SIZE, TilePos.y * TILE_SIZE + TILE_SIZE, TILE_SIZE, TILE_SIZE), sf::Color::Green);
		}
	}
	/*
	// ���� ���� �����
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
			map->GetTileType(TilePosArr[1]),		 // ����
			map->GetTileType(TilePosArr[2]),
			map->GetTileType(TilePosArr[3]),		 // �����
			map->GetTileType(TilePosArr[4]),
			map->GetTileType(TilePosArr[5]),		 // ���
			map->GetTileType(TilePosArr[6]),
			map->GetTileType(TilePosArr[7]),		 // ����
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

void Player::animation(float time)
{
	// ����� ����, ����� ��������� 
	if (going)
		frame += 0.03 * time; 
	if (frame > 2)    frame = 0;
	
	// ����� �� ����� � ������������ ������������
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

	// ���� � ������������ ������������
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

void Player::draw(sf::RenderTarget & target)
{
	// �������������� �������� (getTransform) ��� target.draw(...)
	if (going)
		target.draw(effect);
	target.draw(sprite);
}

void Player::goTo(int x, int y)
{
	going = true;
	picking = false;

	// ������� ������ ���������� ������
	targT.x = ((int)x / TILE_SIZE) * TILE_SIZE;
	targT.y = ((int)y / TILE_SIZE) * TILE_SIZE;

	// ����� ���� ����
	effect.setPosition(targT.x, targT.y);
}

void Player::moveBy(int TileX, int TileY)
{
	going = true;

	sf::Vector2i TilePos = getTilePos();
	goTo((TilePos.x + TileX) * TILE_SIZE, (TilePos.y + TileY) * TILE_SIZE);
}

void Player::pickUp()
{
	picking = false;

	Item* item = ItemManager::getItem(getMiddlePos());
	if (item == nullptr)
		return;
	if (item->onGround == false)
		return;

	InventoryCell* cell = inventory.getFirstEmptyCell();
	if (cell == nullptr)
		return;
	
	cell->setItem(item);
}

void Player::dropUp(InventoryCell * cell)
{
	Item* item = cell->getItem();
	if (item == nullptr) return;

	item->onGround = true;
	item->setTilePosition(sf::Vector2f(getMiddleTilePos()));
	cell->removeItem();
}

void Player::stop()
{
	goTo(getMiddleTilePos().x, getMiddleTilePos().y);
}

void Player::setTexture(const sf::Texture& playerTex)
{
	sprite.setTexture(playerTex); sprite.setTextureRect(sf::IntRect(0, 0, 16, 16)); sprite.setScale(4, 4);
	effect.setTexture(playerTex); effect.setTextureRect(sf::IntRect(16, 64, 16, 16)); effect.setScale(4, 4);
}

void Player::setTileMap(const TileMap & map)
{
	this->map = &map;
}

void Player::setPicking(bool picking)
{
	this->picking = picking;
}

sf::Vector2i Player::getRoundPos() const
{
	sf::Vector2i rPosition(round(position.x), round(position.y));         // ����������� ����������
	return rPosition;
}

sf::Vector2i Player::getTilePos() const
{
	sf::Vector2i tilePos;   // ���������� ������
	tilePos = sf::Vector2i(position.x / TILE_SIZE, position.y / TILE_SIZE);

	return tilePos;
}

sf::Vector2i Player::getMiddleTilePos() const
{
	sf::Vector2f middlePos = getMiddlePos();
	sf::Vector2i tilePos(middlePos.x / TILE_SIZE, middlePos.y / TILE_SIZE);
	return tilePos;
}

sf::Vector2f Player::getMiddlePos() const
{
	sf::Vector2f tileSizeHalf(TILE_SIZE / 2, TILE_SIZE / 2);
	return position + tileSizeHalf;
}

bool Player::isPicking() const
{
	return picking;
}

sf::Vector2f Player::getPosition() const
{
	return position;
}

