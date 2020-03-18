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

	virtual bool GetDragAllow();

	virtual void Draw(sf::RenderTarget & target);
	virtual void Update();
	virtual void UpdateOver();

	virtual void OnDragBegin();
	virtual void OnDrop();
	virtual void OnCancelDrag();

	void setPosition(float x, float y);
	void setPosition(sf::Vector2f position);
	void setSize(float x, float y);
	void setSize(sf::Vector2f size);
	void setScreenParent(UIScreen* parent);

	sf::Vector2f GetPosition() const;
	sf::Vector2f GetGlobalPosition()  const;
	sf::FloatRect GetGlobalBounds() const;
	sf::Vector2f GetDragOffSet() const;
	sf::RectangleShape* GetRectShape();
};