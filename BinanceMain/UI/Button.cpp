#ifdef __linux__
#include "../UI/Button.hpp"
#elif _WIN32
#include "Button.hpp"
#endif

using namespace UI;

/* ImageButton */
ImageButton::ImageButton(sf::Texture& texture)
	:ImageLable(texture) {}
ImageButton::ImageButton(sf::Texture& texture, sf::Vector2f coords)
	: ImageLable(texture, coords) {}
ImageButton::ImageButton(sf::Texture& texture, int x, int y)
	: ImageLable(texture, x, y) {}
ImageButton::ImageButton(const ImageButton& imageButton)
	:ImageLable(imageButton) {}

ElementCode ImageButton::Update(sf::RenderWindow& window, EventControl& eventControl)
{
	ElementCode backgroundCode = this->ImageLable::Update(window, eventControl);

	switch (backgroundCode)
	{
	case ONCLICK_L:
		this->SetColor(sf::Color::White);
		break;
	case ONCLICK_R:
		this->SetColor(sf::Color::White);
		break;
	case PRESSED_L:
		this->SetColor(sf::Color(180, 180, 180));
		break;
	case PRESSED_R:
		this->SetColor(sf::Color(180, 180, 180));
		break;

	default:
		break;
	}

	return backgroundCode;
}

ImageButton& ImageButton::operator=(const ImageButton& imageButton)
{
	if (this == &imageButton)
		return *this;

	this->ImageLable::operator=(imageButton);

	return *this;
}

ImageButton::~ImageButton() {}
/* ----------- */

