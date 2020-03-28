#pragma once
#include "SFML/Graphics.hpp"

class UIScreen;
// Абстрактный базовый класс
class UIBase
{
protected:
	sf::RectangleShape rectShape;
	bool visible;
	bool dragAble;

	sf::Vector2f dragOffset;

public:
	// Без родителя UI НЕ РАБОТАЕТ
	UIScreen* screenParent; 

public:
	UIBase(UIScreen* screenParent = nullptr);

	virtual void draw(sf::RenderTarget & target);
	virtual void update();
	virtual void updateOver();
	virtual void onDragBegin();
	virtual void onDrop();
	virtual void onCancelDrag();

	inline void setScreenParent(UIScreen* parent) { screenParent = parent; };
	inline void setScreenParent(UIScreen& parent) { screenParent = &parent; };
	
	void setPosition(float x, float y);
	void setPosition(sf::Vector2f position);
	void setSize(float x, float y);
	void setSize(sf::Vector2f size);

	virtual bool isDragAllow() const;

	inline sf::Vector2f getPosition() { return rectShape.getPosition(); };
	inline sf::Vector2f getDragOffSet() { return dragOffset; };
	const sf::FloatRect& getGlobalBounds() const;
	inline const sf::RectangleShape& getRectShape() const { return rectShape; };
};