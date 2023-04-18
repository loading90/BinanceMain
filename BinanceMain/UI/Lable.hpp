#ifndef LABLE_H_
#define LABLE_H_
#include "Macro.hpp"
#include "Text.hpp"
#include "Background.hpp"

namespace UI
{
	template<class BackgroundType>class Lable : public IControl
	{
	protected:
		Background<BackgroundType>* background = nullptr;

	public:
		Lable(Background<BackgroundType>* background)
		{
			this->background = background;

			if (UI::isDebug == true && this->background != nullptr)
			{
				this->background->EnableCoords(true);
			}
		}
		Lable(const Lable& lable)
		{
			*this = lable;
		}

		void SetCoordsVisible(bool isVisible)
		{
			this->background->EnableCoords(isVisible);
		}
		void SetLayer(int layer)
		{
			this->background->SetLayer(layer);
		}
		void SetRect(sf::IntRect rect)
		{
			this->background->SetRect(rect);
		}
		virtual void SetPosition(sf::Vector2f position)
		{
			this->background->SetPosition(position);
		}
		void SetBackground(BackgroundType background)
		{
			this->background->SetBackground(background);
		}

		int GetLayer() const
		{
			return this->background->GetLayer();
		}
		sf::IntRect GetRect() const
		{
			return this->background->GetRect();
		}
		sf::Vector2f GetPosition() const
		{
			return this->background->GetPosition();
		}
		const BackgroundType& GetBackground()
		{
			return this->background->GetBackground();
		}

		virtual ElementCode Update(sf::RenderWindow& window, EventControl& eventControl) = 0;

		virtual ~Lable()
		{
			if (this->background != nullptr) delete this->background;
		}
	};

	template<class LableType> class TextLable : public Lable<sf::Color>
	{
		ValueText<LableType>* lable = nullptr;

		int padding;

	public:
		TextLable(LableType value, int padding = 0)
			:Lable(new SolidBackground)
		{
			TextFont* font = TextFont::GetInstance();
			sf::Text tempText;
			tempText.setFont(*(font->GetFont()));
			tempText.setCharacterSize(FONT_SIZE);
			tempText.setColor(FONT_DEFAULT_COLOR);

			this->lable = new ValueText<LableType>(tempText, value);

			// Calculate the size of the background in relation to the text
			sf::FloatRect textRect = this->lable->GetText()->getLocalBounds();
			sf::IntRect backgroundRect(0, 0, static_cast<int>(textRect.width) + padding + MIN_PADDING, static_cast<int>(textRect.height) + padding + MIN_PADDING);
			this->SetRect(backgroundRect);

			this->padding = padding;
			this->SetBackground(BUTTON_BACKGROUND_DEFAULT);
		}
		TextLable(LableType value, sf::Vector2f coords, int padding = 0)
			:TextLable(value, padding)
		{
			SetPosition(coords);
		}
		TextLable(LableType value, int x, int y, int padding = 0)
			:TextLable(value, padding)
		{
			SetPosition(sf::Vector2f(static_cast<float>(x), static_cast<float>(y)));
		}
		TextLable(const TextLable& textLable)
			:Lable(nullptr)
		{
			*this = textLable;
		}

		void SetPosition(sf::Vector2f position) override
		{
			this->Lable::SetPosition(position);

			sf::IntRect backgroundRect = this->GetRect();
			sf::Vector2f tempPosition = position;
			tempPosition.x += static_cast<float>(backgroundRect.width) / 2.0f;
			tempPosition.y += static_cast<float>(backgroundRect.height) / 2.0f;

			this->lable->SetPosition(tempPosition);
		}

		void SetText(LableType text)
		{
			this->lable->Set(text);
		}
		/* Default text size Macro.h FONT_SIZE */
		void SetTextSize(int fontSize)
		{
			bool rectFlag = false;	// false - фон другого размера

			// Checking the background size
			sf::FloatRect textRect = this->lable->GetText()->getLocalBounds();
			sf::IntRect tempRect(0, 0, static_cast<int>(textRect.width) + padding + MIN_PADDING, static_cast<int>(textRect.height) + padding + MIN_PADDING);


			if (tempRect.width == this->GetRect().width)
			{
				if (tempRect.height == this->GetRect().height)
				{
					// Fit button + padding
					rectFlag = true;
				}
			}
			// -----------------------------

			if (rectFlag == true)
			{
				this->lable->GetText()->setCharacterSize(fontSize);

				sf::FloatRect textRect = this->lable->GetText()->getLocalBounds();
				sf::IntRect backgroundRect(0, 0, static_cast<int>(textRect.width) + padding + MIN_PADDING, static_cast<int>(textRect.height) + padding + MIN_PADDING);
				this->SetRect(backgroundRect);
			}
			else
			{
				this->lable->GetText()->setCharacterSize(fontSize);
			}
		}

		LableType GetText() const
		{
			return this->lable->Get();
		}
		unsigned int GetTextSize() const
		{
			return this->lable->GetText()->getCharacterSize();
		}

		virtual ElementCode Update(sf::RenderWindow& window, EventControl& eventControl) override
		{
			ElementCode backgroundCode = this->background->Update(window, eventControl);

			// Update text postion //
			sf::IntRect backgroundRect = this->GetRect();
			sf::Vector2f tempPosition = this->GetPosition();
			tempPosition.x += static_cast<float>(backgroundRect.width) / 2.0f;
			tempPosition.y += static_cast<float>(backgroundRect.height) / 2.0f;

			this->lable->SetPosition(tempPosition);
			// ------------------- //

			if (this->background->GetVisible() == true)
			{
				window.draw(*(this->lable->GetText()));
			}

			return backgroundCode;
		}

		TextLable& operator=(const TextLable& textLable)
		{
			if (this == &textLable)
				return *this;

			this->background = new SolidBackground(static_cast<SolidBackground&>(*(textLable.background)));

			this->lable = new ValueText<LableType>(*(textLable.lable));
			this->padding = padding;

			if (UI::isDebug == true)
			{
				this->background->EnableCoords(true);
			}

			return *this;
		}

		virtual ~TextLable()
		{
			if (this->lable != nullptr) delete this->lable;
		}
	};
	class ImageLable : public Lable<sf::Texture>
	{
		sf::Texture texture;

	public:
		void SetColor(sf::Color color);
		sf::Color GetColor();

	public:
		ImageLable(sf::Texture& texture);
		ImageLable(sf::Texture& texture, sf::Vector2f coords);
		ImageLable(sf::Texture& texture, int x, int y);
		ImageLable(const ImageLable& textLable);

		virtual ElementCode Update(sf::RenderWindow& window, EventControl& eventControl) override;

		ImageLable& operator=(const ImageLable& imageLable);

		virtual ~ImageLable();
	};
}

#endif /* LABLE_H_ */
