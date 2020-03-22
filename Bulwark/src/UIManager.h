#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "UIBase.h"
#include "UIScreen.h"

// Вспомогательный cтатический класс, хранящий UI и помагающий взаимодействовать с ними 
// Он будет доступен для всех классов

class UIManager
{
private:
	static std::vector<UIScreen*> screens;     // Храним все возможные экраны UI
						
	static UIBase* overAll, *dragAll;            // В итоге - что передвигаем и над чем курсор
public:											 

	static void update();						 // Обновляем активные UI экраны
    static void draw(sf::RenderTarget &target);  // Рисуем активные UI экраны

	static UIBase* getMouseOver();
	static UIBase* getMouseDrag();
	static void addScreen(UIScreen *screen);
	static void deleteScreen(unsigned int index);
	static void deleteScreen(const UIScreen* screen);

	static UIScreen* getScreen(unsigned int index);

	//static void addControl(unsigned int screenIndex, UIBase *controlAdress);
	//static void deleteControl(unsigned int screenIndex, unsigned int controlIndex);
private:

	static void updateDrag();
};