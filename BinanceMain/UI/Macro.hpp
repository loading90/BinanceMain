#ifndef SFML_MACRO_H_
#define SFML_MACRO_H_
/* STD Inlcudes */
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
/* ------------ */

/* SFML Includes */
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
/* ------------- */

namespace UI
{
#ifdef __WIN32
	#define FONT_PATH "./fonts/calibri.ttf"
	#define BACKGROUND_PATH "./img/texture.jpg"
#elif __linux__
	#define FONT_PATH "./fonts/calibri.ttf"
	#define BACKGROUND_PATH "./img/texture.jpg"
#endif

	/* Font */
	#define FONT_SIZE 30
	#define FONT_DEFAULT_COLOR sf::Color::Black
	/* ---- */

	/* Background */
	#define EVENT_TIMEOUT_MS 200
	#define COORDS_FONT_SIZE FONT_SIZE / 2
	#define BACKGROUND_DEFAULT sf::Color::White
	#define DELAY_EVENT_TIMEOUT_MS EVENT_TIMEOUT_MS * 3
	/* ---------- */

	/* Lable */
	#define MIN_PADDING 10
	/* ------ */

	/* Button */
	#define BUTTON_BACKGROUND_CLICK sf::Color(140, 140, 140)
	#define BUTTON_BACKGROUND_DEFAULT sf::Color(230, 230, 230)
	/* ------ */

	/* FileManager */
	#define FILE_PATH L"./"
	#define FILE_NAME L"IControlData"
	/* ----------- */
}


#ifdef __WIN32
#pragma warning(disable : 4996)
#pragma warning(disable : 26812)
#endif

#endif /* SFML_MACRO_H_ */
