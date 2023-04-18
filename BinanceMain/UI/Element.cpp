#ifdef __linux__
#include "Element.hpp"
#elif _WIN32
#include "Element.hpp"
#endif

using namespace UI;

/* EventControl */
EventControl::EventControl()
{
	this->time = 0.0f;
	this->cursorPosition = sf::Vector2f(0, 0);
}
EventControl::EventControl(const EventControl& eventControl)
{
	*this = eventControl;
}

EventControl& EventControl::operator=(const EventControl& eventControl)
{
	if (this == &eventControl)
		return *this;

	this->cursorPosition = eventControl.cursorPosition;
	for (size_t i = 0; i < eventControl.events.size(); i++)
	{
		this->events.push_back(eventControl.events[i]);
	}

	return *this;
}

bool EventControl::operator==(const EventControl& eventControl)
{
	if (this->cursorPosition == eventControl.cursorPosition)
	{
		for (size_t i = 0; i < eventControl.events.size(); i++)
		{
			if (this->events[i].type == eventControl.events[i].type)
			{
				if (this->events[i].key.code == eventControl.events[i].key.code)
				{
					return true;
				}
			}
		}
	}
	return false;
}
bool EventControl::operator!=(const EventControl& eventControl)
{
	return !this->operator==(eventControl);
}
/* ------------ */


/* Element */
Element::Element()
	:Element(sf::Vector2f(0, 0), sf::IntRect(0, 0, 0, 0), true, 1) {}
Element::Element(sf::Vector2f position, sf::IntRect rect)
	: Element(position, rect, true, 1) {}
Element::Element(sf::Vector2f position, sf::IntRect rect, int layer)
	: Element(position, rect, true, layer) {}
Element::Element(sf::Vector2f position, sf::IntRect rect, bool isVisible)
	: Element(position, rect, isVisible, 1) {}
Element::Element(sf::Vector2f position, sf::IntRect rect, bool isVisible, int layer)
{
	SetPosition(position);
	SetRect(rect);
	SetVisible(isVisible);
	SetLayer(layer);
}
Element::Element(const Element& element)
{
	*this = element;
}

void Element::SetLayer(int layer)
{
	this->layer = layer;
}
void Element::SetRect(sf::IntRect rect)
{
	this->rect = rect;
}
void Element::SetPosition(sf::Vector2f position)
{
	this->position = position;
}
void Element::SetVisible(bool isVisible)
{
	this->isVisible = isVisible;
}

int Element::GetLayer() const
{
	return this->layer;
}
sf::IntRect Element::GetRect() const
{
	return this->rect;
}
sf::Vector2f Element::GetPosition() const
{
	return this->position;
}
bool Element::GetVisible() const
{
	return this->isVisible;
}

Element& Element::operator=(const Element& element)
{
	if (this == &element)
		return *this;

	this->position = element.position;
	this->rect = element.rect;
	this->isVisible = element.isVisible;
	this->layer = element.layer;

	return *this;
}

Element::~Element()
{
	this->position = sf::Vector2f(0, 0);
	this->rect = sf::IntRect(0, 0, 0, 0);
	this->isVisible = false;
	this->layer = 0;
}
/* ------- */
