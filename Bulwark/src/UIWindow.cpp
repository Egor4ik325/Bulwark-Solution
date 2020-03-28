#include "UIWindow.h"

#include "UIManager.h"
#include "Program.h"

UIWindow::UIWindow(UIScreen* screenParent): UIBase(screenParent)
{
	// Окно
	visible = true;
	dragAble = true;
	rectShape.setSize(sf::Vector2f(300, 200));
	// Цвета
	bodyColor = sf::Color(130, 130, 130, 180);
	titleColor = sf::Color(90, 90, 90, 200);
	titleSelectedColor = sf::Color(120, 120, 120, 200);
	// Заголовок
	titleVisible = true;
	title.setSize(sf::Vector2f(rectShape.getSize().x, TITLE_HEIGHT));
}

void UIWindow::update()
{	
	UIBase::update();

	// UIWINDOW
	title.setPosition(rectShape.getPosition());
	applyColors();
}

void UIWindow::updateOver()
{	
	UIBase::updateOver();
}

bool UIWindow::isDragAllow() const
{
	if (screenParent == nullptr)
		return false;

	bool Title = title.getGlobalBounds().contains(getMouseLocalPos());

	return (Title || screenParent->drag == this) && sf::Mouse::isButtonPressed(sf::Mouse::Left);
}

void UIWindow::draw(sf::RenderTarget & target)
{	
	UIBase::draw(target);

	// UIWINDOW
	if (titleVisible)
	{
		target.draw(title, getViewTransformOffSet());
	}
}

void UIWindow::applyColors()
{
	rectShape.setFillColor(bodyColor);
	title.setFillColor(titleColor);

	if (screenParent->over == this)
		title.setFillColor(titleSelectedColor);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && screenParent->drag == this)
		title.setFillColor(sf::Color::Red);
}