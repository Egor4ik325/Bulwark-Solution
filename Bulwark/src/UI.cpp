#include "UI.h"

UI::UI(UIScreen * screenParent):
	screenParent(screenParent)
{
}

void UI::setScreenParent(UIScreen & screenParent)
{
	this->screenParent = &screenParent;
}
