#ifdef __linux__
#include "Text.hpp"
#elif _WIN32
#include "Text.hpp"
#endif

namespace UI
{
	/* TextFont */
	TextFont* TextFont::textFont = nullptr;

	TextFont::TextFont()
	{
		this->font = new sf::Font;
		if (this->font->loadFromFile(FONT_PATH))
			std::cout << "Text font loaded!" << std::endl;
		else
			std::cout << "Text font load error!" << std::endl;
	}
	TextFont::~TextFont()
	{
		if (this->font != nullptr) delete this->font;
	}

	TextFont* TextFont::GetInstance()
	{
		if (TextFont::textFont == nullptr)
		{
			TextFont::textFont = new TextFont();
		}

		return TextFont::textFont;
	}

	sf::Font* TextFont::GetFont() const
	{
		return this->font;
	}
	/* -------- */
}
