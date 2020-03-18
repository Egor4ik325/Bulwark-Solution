#include "UIButton.h"
#include "UIScreen.h"
#include "Program.h"
#include "DebugRect.h"
#include <iostream>

UIButton::UIButton()
{
	Construct();
}

UIButton::UIButton(const std::string& text,const sf::Color& color,const sf::Font& font)
{
	Construct();
	this->text.setString(text); 
	this->text.setFillColor(color);
	this->text.setFont(font);
}

void UIButton::Construct()
{
	rectShape.setFillColor(sf::Color::White);
	rectShape.setPosition(100.f, 100.f);
	rectShape.setSize(sf::Vector2f(200.f, 100.f));
	rectShape.setOutlineThickness(10.f);
	rectShape.setOutlineColor(sf::Color::Black);

	text.setFillColor(sf::Color::Black);
	text.setPosition(0, 0);
	text.setString("");
	text.setScale(1, 1);

	DragAble = false;
}

void UIButton::Draw(sf::RenderTarget& target)
{
	UIBase::Draw(target);

	if (rectShape.getGlobalBounds().contains(GetMouseCoords()) && GetMouseLeft())
		rectShape.setFillColor(sf::Color::White); 
	else
		rectShape.setFillColor(color);

    DrawText(target);
}

void UIButton::UpdateOver()
{
	UIBase::UpdateOver();
}

void UIButton::SetColor(const sf::Color & color)
{
	this->color = color;
}

void UIButton::DrawText(sf::RenderTarget& target)
{
	float sizeRel = rectShape.getSize().x / 100.f; // ��������������� ������� ������ ������� ������ �� �����
	sizeRel *= (200.f / text.getString().getSize());														 
	text.setCharacterSize(sizeRel);																	
	sizeRel *= ((float)18.f/40.f); // ��������� Character size � ��������� ������ � pix				
																									
	sf::Vector2f textPos;																			
																						
	float CharacterVal = text.getString().getSize();										
	CharacterVal /= 2.f;																	
	float rectMiddlePosX = rectShape.getPosition().x + (rectShape.getSize().x / 2.f);	
	textPos.x = rectMiddlePosX - ((float)CharacterVal * sizeRel);									
																									
	sizeRel *= 3.f;																					
	float rectMiddlePosY = rectShape.getPosition().y + (rectShape.getSize().y / 2.f);				
	textPos.y = rectMiddlePosY - (0.5f * sizeRel);													
																									
	//DebugRect::AddRect(sf::FloatRect(rectShape.getPosition().x, rectMiddlePosY, 18,18*3),sf::Color::Red);	 

	text.setPosition(textPos);
	target.draw(text);
}