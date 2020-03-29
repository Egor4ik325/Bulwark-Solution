#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class UIScreen;

////////////////////////////////////////////////////////////
/// \brief Abstract base class for UI includes {UIDrawable, UITransformable}
///
////////////////////////////////////////////////////////////
class UI : public sf::RectangleShape
{
protected:
	//UI() = default;
	UI(UIScreen* screenParent); // Default protected contructor means - abstract class - can not be created

	bool visible;

public:
	UIScreen* screenParent; // Родитель

public:

	virtual void draw(sf::RenderTarget& target) = 0;
	virtual void update() = 0;

	virtual const std::string& getUIName() const = 0;
	void setScreenParent(UIScreen& screenParent);
 };