#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "UIScreen.h"

class UIDragable;

// Вспомогательный cтатический класс, хранящий UI и помагающий взаимодействовать с ними 
// Он будет доступен для всех классов
class UIManager
{
private:
	static std::vector<UIScreen*> screens;     // Храним все возможные экраны UI
						
	static UIDragable* overAll, *dragAll;            // В итоге - что передвигаем и над чем курсор
public:											 

	static void update();						 // Обновляем активные UI экраны
    static void draw(sf::RenderTarget &target);  // Рисуем активные UI экраны

	static UIDragable* getMouseOver();
	static UIDragable* getMouseDrag();

	// Передаем адрес Screen созданного в динамической памяти
	static void addScreen(UIScreen* screen);
	static void addScreen(UIScreen& screen);

	// Удаляем Screen
	static void deleteScreen(unsigned int index);
	static void deleteScreen(const UIScreen* screen);
	static void deleteScreen(const UIScreen& screen);

	static UIScreen* getScreen(unsigned int index);
private:

	static void updateDrag();
};