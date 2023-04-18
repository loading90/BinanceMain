#ifdef __linux__
#include "Lable.hpp"
#elif _WIN32
#include "Lable.hpp"
#endif

using namespace UI;

/* ImageLable */
ImageLable::ImageLable(sf::Texture& texture)
	:Lable(new ImageBackground)
{
	this->texture = texture;
	this->background->SetBackground(this->texture);
}
ImageLable::ImageLable(sf::Texture& texture, sf::Vector2f coords)
	: ImageLable(texture)
{
	SetPosition(coords);
}
ImageLable::ImageLable(sf::Texture& texture, int x, int y)
	:ImageLable(texture)
{
	SetPosition(sf::Vector2f(static_cast<float>(x), static_cast<float>(y)));
}
ImageLable::ImageLable(const ImageLable& imageLable)
	:Lable(nullptr)
{
	*this = imageLable;
}

ElementCode ImageLable::Update(sf::RenderWindow& window, EventControl& eventControl)
{
	ElementCode backgroundCode = this->background->Update(window, eventControl);

	return backgroundCode;
}

void ImageLable::SetColor(sf::Color color)
{
	static_cast<ImageBackground*>(this->background)->SetColor(color);
}
sf::Color ImageLable::GetColor()
{
	return static_cast<ImageBackground*>(this->background)->GetColor();
}

ImageLable& ImageLable::operator=(const ImageLable& imageLable)
{
	if (this == &imageLable)
		return *this;

	this->background = new ImageBackground(static_cast<ImageBackground&>(*(imageLable.background)));

	this->texture = imageLable.texture;
	this->background->SetBackground(this->texture);

	if (UI::isDebug == true)
	{
		this->background->EnableCoords(true);
	}

	return *this;
}

ImageLable::~ImageLable() {}
/* ---------- */
