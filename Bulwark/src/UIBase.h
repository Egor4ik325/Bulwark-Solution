#pragma once
#include "SFML/Graphics.hpp"

class UIScreen;

// Базовый класс - Фактически UIDragable, реализовать интерфейсы UIBase {UIDrawable, UITransformable}
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

	virtual bool isDragAllow() const;

	inline void setScreenParent(UIScreen* parent) { screenParent = parent; };
	inline void setScreenParent(UIScreen& parent) { screenParent = &parent; };
	void setPosition(float x, float y);
	void setPosition(sf::Vector2f position);
	void setSize(float x, float y);
	void setSize(sf::Vector2f size);

	inline sf::Vector2f getDragOffSet() { return dragOffset; };
	inline sf::Vector2f getPosition() { return rectShape.getPosition(); };
	inline const sf::RectangleShape& getRectShape() const { return rectShape; };
};