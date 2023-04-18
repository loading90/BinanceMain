#ifndef BACKGROUND_H_
#define BACKGROUND_H_
#include "Text.hpp"
#include "Macro.hpp"
#include "Element.hpp"
#include "Timer.hpp"

namespace UI
{
	class BackgroundTexture
	{
		static BackgroundTexture* backgroundTexture;

		sf::Texture* texture = nullptr;

		BackgroundTexture();
		~BackgroundTexture();

	public:
		BackgroundTexture(const BackgroundTexture&) = delete;
		BackgroundTexture& operator=(const BackgroundTexture&) = delete;

		static BackgroundTexture* GetInstance();

		sf::Texture* GetTexture() const;
	};

	template<class TValue> class Background : public Element
	{
		sf::Sprite* backgroundSprite = nullptr;

		MillisTimer timer;
		bool isPressed;					// ���� ������� �� ���������� ��������, �������� � ���� � @previousPressedEvent
		sf::Event previousPressedEvent;	// Event ������� �� ���������� ��������

		ElementCode code;

		bool enableCoords;
		ValueText<std::wstring>* coords = nullptr;
		ValueText<std::wstring>* backgroundSize = nullptr;

	protected:
		void SetBackgroundColor(sf::Color color)
		{
			this->backgroundSprite->setColor(color);
		}
		const sf::Color& GetBackgroundColor()
		{
			return this->backgroundSprite->getColor();
		}

		void SetBackgroundTexture(sf::Texture& texture)
		{
			this->backgroundSprite->setTexture(texture);
		}
		const sf::Texture& GetBackgroundTexture()
		{
			return *(this->backgroundSprite->getTexture());
		}

	public:
		Background()
			:timer(EVENT_TIMEOUT_MS)
		{
			BackgroundTexture* texture = BackgroundTexture::GetInstance();
			this->backgroundSprite = new sf::Sprite(*(texture->GetTexture()));

			this->code = NONE;
			this->isPressed = false;

			TextFont* font = TextFont::GetInstance();
			sf::Text tempText;
			tempText.setFont(*(font->GetFont()));
			tempText.setCharacterSize(COORDS_FONT_SIZE);
			tempText.setColor(FONT_DEFAULT_COLOR);

			this->enableCoords = false;
			this->coords = new ValueText<std::wstring>(tempText, L"X0Y0");
			this->backgroundSize = new ValueText<std::wstring>(tempText, L"W0H0");
		}
		Background(const Background& background)
			:timer(EVENT_TIMEOUT_MS)
		{
			*this = background;
		}
		Background(Background&& background)
			:timer(EVENT_TIMEOUT_MS)
		{
			this->code = background.code;

			this->backgroundSprite = background.backgroundSprite;
			background.backgroundSprite = nullptr;

			this->enableCoords = background.enableCoords;
			this->coords = background.coords;
			background.coords = nullptr;
			this->backgroundSize = background.backgroundSize;
			background.backgroundSize = nullptr;

			this->previousPressedEvent = background.previousPressedEvent;

			this->Element::operator=(background);
		}

		virtual void SetBackground(TValue backgroundValue) = 0;
		virtual const TValue& GetBackground() = 0;

		void EnableCoords(bool enable)
		{
			this->enableCoords = enable;
		}

		virtual ElementCode Update(sf::RenderWindow& window, EventControl& eventControl) override
		{
			// �������� ������ �� @Element
			this->backgroundSprite->setPosition(GetPosition());
			this->backgroundSprite->setTextureRect(GetRect());
			// ---------------------------

			// ���������� ������� @coords � @backgroundSize
			if (this->enableCoords)
			{
				// @coords
				sf::FloatRect textRect = this->coords->GetText()->getLocalBounds();
				sf::Vector2f elementPosition = GetPosition();
				this->coords->SetPosition(sf::Vector2f(elementPosition.x + (textRect.width / 2), elementPosition.y - (textRect.height / 2)));

				std::wostringstream strXValue;
				strXValue << elementPosition.x;
				std::wstring coordsStr = L"X" + strXValue.str();
				std::wostringstream strYValue;
				strYValue << elementPosition.y;
				coordsStr += L"Y" + strYValue.str();

				this->coords->Set(coordsStr);
				// -------


				// @backgroundSize
				textRect = this->backgroundSize->GetText()->getLocalBounds();
				elementPosition = GetPosition();
				this->backgroundSize->SetPosition(sf::Vector2f(elementPosition.x + (textRect.width / 2), elementPosition.y + (textRect.height / 2) + 3));


				std::wostringstream strWValue;
				strWValue << this->rect.width;
				std::wstring backgroundSizeStr = L"W" + strWValue.str();
				std::wostringstream strHValue;
				strHValue << this->rect.height;
				backgroundSizeStr += L"H" + strHValue.str();

				this->backgroundSize->Set(backgroundSizeStr);
				// ---------------
			}

			this->code = NONE;	// ���������� ��� ��������

			// ��������� ������ �� ������� �����
			int indexPressed = -1;	// ������ event'a ������� ������ �����
			int indexReleased = -1;	// ������ event'a ���������� ������ �����
			for (size_t i = 0; i < eventControl.events.size(); i++)
			{
				// ���� ���� ������� �� ������� ������ �����
				if (eventControl.events[i].type == sf::Event::MouseButtonPressed)
				{
					indexPressed = static_cast<int>(i);	// ���������� ���� ������� ������ �����
				}

				// ���� ���� ������� �� ���������� ������ �����
				if (eventControl.events[i].type == sf::Event::MouseButtonReleased)
				{
					indexReleased = static_cast<int>(i);	// ���������� ���� ���������� ������ �����
				}
			}

			// ���� ������ ��������� � ������� �������
			if (this->backgroundSprite->getGlobalBounds().contains(eventControl.cursorPosition))
			{
				// ���� ������ ����� ���� ������
				if (indexPressed != -1)
				{
					// ���� ������ ����� ���� �������� �����
					if (indexReleased != -1)
					{
						// �������� �� ������� � ���������� ����� � ��� �� ������ �����
						if (eventControl.events[indexPressed].mouseButton.button == eventControl.events[indexReleased].mouseButton.button)
						{
							// ���� ����� ������ �����
							if (eventControl.events[indexPressed].mouseButton.button == sf::Mouse::Button::Left)
							{
								this->code = ONCLICK_L;
							}
							// ���� ������ ������ �����
							else if (eventControl.events[indexPressed].mouseButton.button == sf::Mouse::Button::Right)
							{
								this->code = ONCLICK_R;
							}
							// ��������� ������ �����
							else
							{
								this->code = NONE;
							}
						}
					}
					else
					{
						// ���������� event ������� ������ ����� � ���������� ����
						this->isPressed = true;
						this->previousPressedEvent = eventControl.events[indexPressed];

						// ����������� ����� ��������
						this->timer.SetInterval(DELAY_EVENT_TIMEOUT_MS);
						// ���������� ������
						this->timer.Reset();


						// ���� ����� ������ �����
						if (eventControl.events[indexPressed].mouseButton.button == sf::Mouse::Button::Left)
						{
							this->code = PRESSED_L;
						}
						// ���� ������ ������ �����
						else if (eventControl.events[indexPressed].mouseButton.button == sf::Mouse::Button::Right)
						{
							this->code = PRESSED_R;
						}
						// ��������� ������ �����
						else
						{
							this->code = NONE;
						}
					}
				}
				// ���� ������ ����� ���� ��������
				else if (indexReleased != -1)
				{
					// ��������� �� ����� ���� �� ������ ������ �����
					if (this->isPressed == true)
					{
						// ��������� ����� ������ ����� ���� ������
						if (eventControl.events[indexReleased].mouseButton.button == this->previousPressedEvent.mouseButton.button)
						{
							// ������ ����� ���� ������ � ��������
							this->isPressed = false;

							// ���� ����� ������ �����
							if (this->previousPressedEvent.mouseButton.button == sf::Mouse::Button::Left)
							{
								this->code = ONCLICK_L;
							}
							// ���� ������ ������ �����
							else if (this->previousPressedEvent.mouseButton.button == sf::Mouse::Button::Right)
							{
								this->code = ONCLICK_R;
							}
							// ��������� ������ �����
							else
							{
								this->code = NONE;
							}
						}
					}
				}
				else
				{
					// ���� � ���������� �������� ���� ������ ������ ����
					if (this->isPressed == true)
					{
						if (this->timer.IsPassedTime())
						{
							// ���� ����� ������ �����
							if (this->previousPressedEvent.mouseButton.button == sf::Mouse::Button::Left)
							{
								this->code = CLAMPED_L;
							}
							// ���� ������ ������ �����
							else if (this->previousPressedEvent.mouseButton.button == sf::Mouse::Button::Right)
							{
								this->code = CLAMPED_R;
							}
							// ��������� ������ �����
							else
							{
								this->code = NONE;
							}

							// ����������� ����� ��������
							this->timer.SetInterval(EVENT_TIMEOUT_MS);
							// ���������� ������
							this->timer.Reset();
						}
					}
					else
					{
						this->code = HOVER;
					}
				}
			}
			else
			{
				// �������� ��������� �� ������
				if (this->isPressed == true)
				{
					if (indexReleased != -1)
					{
						this->code = RESET;
						this->isPressed = false;
						this->previousPressedEvent = sf::Event();
					}
				}
			}

			if (this->isVisible)
			{
				window.draw(*this->backgroundSprite);

				if (this->enableCoords)
				{
					window.draw(*(this->coords->GetText()));
					window.draw(*(this->backgroundSize->GetText()));
				}
			}

			return this->code;
		}

		Background& operator=(const Background& background)
		{
			if (this == &background)
				return *this;

			this->Element::operator=(background);
			this->code = background.code;
			this->backgroundSprite = new sf::Sprite(*(background.backgroundSprite));
			this->previousPressedEvent = background.previousPressedEvent;
			this->enableCoords = background.enableCoords;
			this->coords = new ValueText<std::wstring>(*(background.coords));

			return *this;
		}

		virtual ~Background()
		{
			if (this->backgroundSprite != nullptr) delete this->backgroundSprite;
			if (this->coords != nullptr) delete this->coords;
		}
	};

	class SolidBackground : public Background<sf::Color>
	{
	public:
		SolidBackground();
		SolidBackground(const SolidBackground& background);

		virtual void SetBackground(sf::Color backgroundColor);
		virtual const sf::Color& GetBackground();

		SolidBackground& operator=(const SolidBackground& background);

		virtual ~SolidBackground();
	};
	class ImageBackground : public Background<sf::Texture>
	{
		sf::Texture texture;

	public:
		ImageBackground();
		ImageBackground(const ImageBackground& background);

		virtual void SetBackground(sf::Texture backgroundTexture);
		virtual const sf::Texture& GetBackground();

		void SetColor(sf::Color color);
		sf::Color GetColor();

		ImageBackground& operator=(const ImageBackground& background);

		virtual ~ImageBackground();
	};
}

#endif /* BACKGROUND_H_ */
