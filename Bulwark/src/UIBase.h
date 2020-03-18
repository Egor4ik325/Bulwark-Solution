#pragma once
#include "SFML/Graphics.hpp"

class UIScreen;
// Абстрактный базовый класс
class UIBase
{
protected:
	sf::RectangleShape rectShape;
	bool Visible;
	bool DragAble;

	sf::Vector2f dragOffset;

public:
	UIScreen* screenParent;

	UIBase();

	virtual bool getDragAllow();

	virtual void draw(sf::RenderTarget & target);
	virtual void update();
	virtual void updateOver();

	virtual void onDragBegin();
	virtual void onDrop();
	virtual void onCancelDrag();

	void setPosition(float x, float y);
	void setPosition(sf::Vector2f position);
	void setSize(float x, float y);
	void setSize(sf::Vector2f size);
	void setScreenParent(UIScreen* parent);

	sf::Vector2f getPosition() const;
	sf::Vector2f getGlobalPosition()  const;
	sf::FloatRect getGlobalBounds() const;
	sf::Vector2f getDragOffSet() const;
	sf::RectangleShape* getRectShape();
};