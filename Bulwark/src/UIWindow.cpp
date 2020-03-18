#include "UIWindow.h"

#include "UIManager.h"
#include "Program.h"

UIWindow::UIWindow()
{
	// Окно
	Visible = true;
	DragAble = true;
	rectShape.setSize(sf::Vector2f(300, 200));
	// Цвета
	BodyColor = sf::Color(130, 130, 130, 180);
	TitleColor = sf::Color(90, 90, 90, 200);
	TitleSelectedColor = sf::Color(120, 120, 120, 200);
	// Заголовок
	TitleVisible = true;
	title.setSize(sf::Vector2f(rectShape.getSize().x, TITLE_HEIGHT));
}

void UIWindow::Update()
{	
	UIBase::Update();

	// UIWINDOW
	title.setPosition(rectShape.getPosition());
	ApplyColors();
}

void UIWindow::UpdateOver()
{	
	UIBase::UpdateOver();
}

bool UIWindow::GetDragAllow()
{
	if (screenParent == nullptr)
		return false;

	return (IntersectsWithMouse(title.getGlobalBounds()) || screenParent->Drag == this) && GetMouseLeft();
}

void UIWindow::Draw(sf::RenderTarget & target)
{	
	UIBase::Draw(target);

	// UIWINDOW
	if (TitleVisible)
	{
		target.draw(title, GetViewTransformOffSet());
	}
}

void UIWindow::ApplyColors()
{
	rectShape.setFillColor(BodyColor);
	title.setFillColor(TitleColor);

	if (screenParent->Over == this)
		title.setFillColor(TitleSelectedColor);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && screenParent->Drag == this)
		title.setFillColor(sf::Color::Red);
}