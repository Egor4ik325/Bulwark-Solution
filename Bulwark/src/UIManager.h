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
						
	static UIBase* OverAll, *DragAll;            // В итоге - что передвигаем и над чем курсор
public:											 

	static void Update();						 // Обновляем активные UI экраны
    static void Draw(sf::RenderTarget &target);  // Рисуем активные UI экраны

	static UIBase* GetMouseOver();
	static UIBase* GetMouseDrag();
	static void AddScreen(UIScreen *screen);
	static void DeleteScreen(unsigned int index);
	static void DeleteScreen(UIScreen* screen);

	static void AddControl(unsigned int screenIndex, UIBase *controlAdress);
	static void DeleteControl(unsigned int screenIndex, unsigned int controlIndex);
private:

	static void UpdateDrag();
};