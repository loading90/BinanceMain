#ifndef BUTTON_H_
#define BUTTON_H_
#include "Macro.hpp"
#include "Lable.hpp"

namespace UI
{
	template<class ButtonType> class TextButton : public TextLable<ButtonType>
	{
	public:
		TextButton(ButtonType value, int padding = 0)
			:TextLable<ButtonType>(value, padding) {}
		TextButton(ButtonType value, sf::Vector2f coords, int padding = 0)
			:TextLable<ButtonType>(value, coords, padding) {}
		TextButton(ButtonType value, int x, int y, int padding = 0)
			:TextLable<ButtonType>(value, x, y, padding) {}
		TextButton(const TextButton& textButton)
			:TextLable<ButtonType>(textButton) {}

		virtual ElementCode Update(sf::RenderWindow& window, EventControl& eventControl) override
		{
			ElementCode backgroundCode = this->TextLable<ButtonType>::Update(window, eventControl);

			switch (backgroundCode)
			{
			case RESET:
				this->SetBackground(BUTTON_BACKGROUND_DEFAULT);
				break;
			case ONCLICK_L:
				this->SetBackground(BUTTON_BACKGROUND_DEFAULT);
				break;
			case ONCLICK_R:
				this->SetBackground(BUTTON_BACKGROUND_DEFAULT);
				break;
			case PRESSED_L:
				this->SetBackground(BUTTON_BACKGROUND_CLICK);
				break;
			case PRESSED_R:
				this->SetBackground(BUTTON_BACKGROUND_CLICK);
				break;

			default:
				break;
			}

			return backgroundCode;
		}

		TextButton& operator=(const TextButton& textButton)
		{
			if (this == &textButton)
				return *this;

			this->TextLable<ButtonType>::operator=(textButton);

			return *this;
		}

		virtual ~TextButton() {}
	};
	class ImageButton : public ImageLable
	{

	public:
		ImageButton(sf::Texture& texture);
		ImageButton(sf::Texture& texture, sf::Vector2f coords);
		ImageButton(sf::Texture& texture, int x, int y);
		ImageButton(const ImageButton& imageButton);

		virtual ElementCode Update(sf::RenderWindow& window, EventControl& eventControl) override;

		ImageButton& operator=(const ImageButton& imageButton);

		virtual ~ImageButton();
	};
}

#endif /* BUTTON_H_ */
