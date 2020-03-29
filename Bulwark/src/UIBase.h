#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class UIScreen;

////////////////////////////////////////////////////////////
/// \brief Abstract base class for UI includes {UIDrawable, UITransformable}
///
////////////////////////////////////////////////////////////
class UIBase : public sf::RectangleShape
{
protected:
	//UIBase() = default; // Default protected contructor means - abstract class - can not be created
	std::string name;
	bool visible;

	UIBase(UIScreen* screenParent); 

public:
	UIScreen* screenParent; // Родитель

public:

	virtual void draw(sf::RenderTarget& target);
	virtual void update() = 0;

	void setScreenParent(UIScreen* screenParent);
	void setScreenParent(UIScreen& screenParent);
	const std::string& getUIName() const;
};