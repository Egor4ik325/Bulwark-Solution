#pragma once
#include <SFML/Graphics.hpp>
#include "UI.h"

////////////////////////////////////////////////////////////
/// \brief Base class for UI with implementation
///
////////////////////////////////////////////////////////////
class UIBase : public UI
{
protected:
	UIBase(UIScreen* screenParent);

public:
	// ������������ ����� UI
	virtual void draw(sf::RenderTarget & target) override;
};