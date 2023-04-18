#ifdef __linux__
#include "../UI/Background.hpp"
#elif _WIN32
#include "Background.hpp"
#endif

using namespace UI;

/* BackgroundTexture */
BackgroundTexture* BackgroundTexture::backgroundTexture = nullptr;

BackgroundTexture::BackgroundTexture()
{
	this->texture = new sf::Texture;

	if (this->texture->loadFromFile(BACKGROUND_PATH))
		std::cout << "Background texture load!" << std::endl;
	else
		std::cout << "Background texture load! error!" << std::endl;
}
BackgroundTexture::~BackgroundTexture()
{
	if (this->texture != nullptr) delete this->texture;
}

BackgroundTexture* BackgroundTexture::GetInstance()
{
	if (BackgroundTexture::backgroundTexture == nullptr)
	{
		BackgroundTexture::backgroundTexture = new BackgroundTexture();
	}

	return BackgroundTexture::backgroundTexture;
}

sf::Texture* BackgroundTexture::GetTexture() const
{
	return this->texture;
}
/* ----------------- */


/* SolidBackground */
SolidBackground::SolidBackground() : Background()
{
	this->SetBackgroundColor(BACKGROUND_DEFAULT);
}
SolidBackground::SolidBackground(const SolidBackground& background)
{
	*this = background;
}

void SolidBackground::SetBackground(sf::Color backgroundColor)
{
	this->SetBackgroundColor(backgroundColor);
}
const sf::Color& SolidBackground::GetBackground()
{
	return this->GetBackgroundColor();
}

SolidBackground& SolidBackground::operator=(const SolidBackground& background)
{
	if (this == &background)
		return *this;

	this->Background::operator=(background);

	return *this;
}

SolidBackground::~SolidBackground() {}
/* --------------- */


/* ImageBackground */
ImageBackground::ImageBackground() : Background() {}
ImageBackground::ImageBackground(const ImageBackground& background)
{
	*this = background;
}

void ImageBackground::SetBackground(sf::Texture backgroundTexture)
{
	texture = backgroundTexture;
	this->SetBackgroundTexture(texture);
}
const sf::Texture& ImageBackground::GetBackground()
{
	return this->GetBackgroundTexture();
}

void ImageBackground::SetColor(sf::Color color)
{
	this->SetBackgroundColor(color);
}
sf::Color ImageBackground::GetColor()
{
	return this->GetBackgroundColor();
}

ImageBackground& ImageBackground::operator=(const ImageBackground& background)
{
	if (this == &background)
		return *this;

	this->Background::operator=(background);

	return *this;
}

ImageBackground::~ImageBackground() {}
/* --------------- */
