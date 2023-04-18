#ifndef TEXT_H_
#define TEXT_H_
#include "Macro.hpp"

namespace UI
{
	template<class TValue> class Text
	{
	protected:
		sf::Text text;

	public:
		virtual void Set(TValue value) = 0;
		virtual void SetPosition(sf::Vector2f postion) = 0;

		virtual TValue Get() = 0;
		virtual sf::Text* GetText() = 0;
	};

	class TextFont
	{
		static TextFont* textFont;

		sf::Font* font = nullptr;

		TextFont();
		~TextFont();

	public:
		TextFont(const TextFont&) = delete;
		TextFont& operator=(const TextFont&) = delete;

		static TextFont* GetInstance();

		sf::Font* GetFont() const;
	};

	/* Origin by center */
	template<class TValue> class ValueText : public Text<TValue>
	{
		TValue value;

		std::wstring additionalLine;

	public:
		ValueText(sf::Text& text, TValue value) : ValueText(text, value, L"") {}
		ValueText(sf::Text& text, TValue value, std::wstring additionalLine)
		{
			this->value = value;
			this->additionalLine = additionalLine;
			this->text = text;
		}
		ValueText(const ValueText& valueText)
		{
			*this = valueText;
		}

		void Set(TValue value) override
		{
			this->value = value;
		}
		void SetPosition(sf::Vector2f position) override
		{
			this->text.setPosition(position);
		}

		TValue Get() override
		{
			return this->value;
		}
		sf::Text* GetText() override
		{
			std::wostringstream strValue;
			strValue << this->value;

			this->text.setString(strValue.str() + this->additionalLine);

			sf::FloatRect textRect;

			textRect = this->text.getLocalBounds();
			this->text.setOrigin(textRect.left + textRect.width / 2.0f,
				textRect.top + textRect.height / 2.0f);

			return &this->text;
		}

		ValueText<TValue>& operator=(const ValueText<TValue>& valueText)
		{
			if (this == &valueText)
				return *this;

			this->text = valueText.text;
			this->value = valueText.value;
			this->additionalLine = valueText.additionalLine;

			return *this;
		}
	};
	/* Origin by center */
	template<class TValue = std::wstring> class LableText : public Text<TValue>
	{
		std::wstring lable;

		bool changed;
	public:
		LableText(sf::Text& text) : LableText(text, L"") {}
		LableText(sf::Text& text, std::wstring lable)
		{
			this->text = text;
			this->lable = lable;
			this->changed = true;
		}
		LableText(const LableText& lableText)
		{
			*this = lableText;
		}

		void Set(TValue lable)
		{
			this->lable = lable;
			this->changed = true;
		}
		void SetPosition(sf::Vector2f position)
		{
			this->text.setPosition(position);
		}

		TValue Get()
		{
			return this->lable;
		}
		sf::Text* GetText()
		{
			if (this->changed)
			{
				this->text.setString(this->lable);

				sf::FloatRect textRect;

				textRect = this->text.getLocalBounds();
				this->text.setOrigin(textRect.left + textRect.width / 2.0f,
					textRect.top + textRect.height / 2.0f);

				this->changed = false;
			}

			return &this->text;
		}
		sf::Text* GetText(sf::Vector2f& position)
		{
			this->text.setPosition(position);
			return GetText();
		}

		LableText<TValue>& operator=(const LableText& lableText)
		{
			if (this == &lableText)
				return *this;

			this->text = lableText.text;
			this->lable = lableText.lable;
			this->changed = lableText.changed;

			return *this;
		}
	};
}

#endif /* TEXT_H_ */
