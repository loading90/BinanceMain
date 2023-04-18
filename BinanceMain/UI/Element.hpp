#ifndef ELEMENT_H_
#define ELEMENT_H_
#include "Macro.hpp"

namespace UI
{
	enum ElementCode
	{
		RESET,
		NONE,
		HOVER,
		ONCLICK_L,
		ONCLICK_R,
		PRESSED_L,
		PRESSED_R,
		CLAMPED_L,
		CLAMPED_R
	};

	extern bool isDebug;

	class EventControl
	{
	public:
		float time;
		sf::Vector2f cursorPosition;
		std::vector<sf::Event> events;

		EventControl();
		EventControl(const EventControl& eventControl);

		EventControl& operator=(const EventControl& eventControl);
		bool operator==(const EventControl& eventControl);
		bool operator!=(const EventControl& eventControl);
	};

	class IControl
	{
	public:
		virtual void SetPosition(sf::Vector2f position) = 0;
		virtual sf::Vector2f GetPosition() const = 0;

		virtual void SetRect(sf::IntRect rect) = 0;
		virtual sf::IntRect GetRect() const = 0;

		virtual ElementCode Update(sf::RenderWindow& window, EventControl& eventControl) = 0;
	};
	class Element : public IControl
	{
	protected:
		sf::Vector2f position;		// element position
		sf::IntRect rect;			// element rect
		bool isVisible;				// is visible element
		int layer;					// 1 - default, 0 - is window

	public:
		Element();
		Element(sf::Vector2f position, sf::IntRect rect);
		Element(sf::Vector2f position, sf::IntRect rect, int layer);
		Element(sf::Vector2f position, sf::IntRect rect, bool isVisible);
		Element(sf::Vector2f position, sf::IntRect rect, bool isVisible, int layer);
		Element(const Element& element);


		void SetLayer(int layer);
		void SetRect(sf::IntRect rect);
		void SetPosition(sf::Vector2f position);
		void SetVisible(bool isVisible);

		int GetLayer() const;
		sf::IntRect GetRect() const;
		sf::Vector2f GetPosition() const;
		bool GetVisible() const;

		virtual ElementCode Update(sf::RenderWindow& window, EventControl& eventControl) = 0;

		Element& operator=(const Element& element);

		virtual ~Element();
	};
}

#endif /* ELEMENT_H_ */
