#ifndef MACRO_H_
#define MACRO_H_
#include "UI/Macro.hpp"
#include <SFML/Audio.hpp>

namespace elements
{
	// InputLable //
	const std::wstring INPUT_LABLE = L"InputLable";
	const std::wstring INPUT_LABLE_LABLE = L"BTCUSDT";
	// ---------- //

	// CurrentTime //
	const std::wstring CURRENT_TIME = L"CurrentTime";
	const std::wstring CURRENT_TIME_LABLE = L"12::29:20";
	// ---------- //

	// Lable's //
	const std::wstring LABLE_BACKGROUND = L"LableBackground";
	const sf::Color LABLE_BACKGROUND_COLOR = sf::Color(105, 89, 89);
	
	const std::wstring LABLE_MIN1 = L"Lable_MIN1";
	const std::wstring LABLE_MIN1_LABLE = L"1 Min";
	const std::wstring LABLE_MIN5 = L"Lable_MIN5";
	const std::wstring LABLE_MIN5_LABLE = L"5 Min";
	const std::wstring LABLE_MIN15 = L"Lable_MIN15";
	const std::wstring LABLE_MIN15_LABLE = L"15 Min";
	const std::wstring LABLE_MIN30 = L"Lable_MIN30";
	const std::wstring LABLE_MIN30_LABLE = L"30 Min";
	const std::wstring LABLE_HOUR1 = L"Lable_HOUR1";
	const std::wstring LABLE_HOUR1_LABLE = L"1 Hour";
	const std::wstring LABLE_HOUR4 = L"Lable_HOUR4";
	const std::wstring LABLE_HOUR4_LABLE = L"4 Hour";
	// ------- //

	// Buy's //
	const std::wstring BUY_BACKGROUND = L"BuyBackground";
	const sf::Color BUY_BACKGROUND_COLOR = sf::Color(46, 201, 28);

	const std::wstring BUY_LABLE = L"BuyLable";
	const std::wstring BUY_LABLE_LABLE = L"Buy";

	const std::wstring BUY_MIN1 = L"Buy_MIN1";
	const double BUY_MIN1_LABLE = 100000.0;
	const std::wstring BUY_MIN5 = L"Buy_MIN5";
	const double BUY_MIN5_LABLE = 100000.0;
	const std::wstring BUY_MIN15 = L"Buy_MIN15";
	const double BUY_MIN15_LABLE = 100000.0;
	const std::wstring BUY_MIN30 = L"Buy_MIN30";
	const double BUY_MIN30_LABLE = 100000.0;
	const std::wstring BUY_HOUR1 = L"Buy_HOUR1";
	const double BUY_HOUR1_LABLE = 100000.0;
	const std::wstring BUY_HOUR4 = L"Buy_HOUR4";
	const double BUY_HOUR4_LABLE = 100000.0;
	// ------- //

	// Sell's //
	const std::wstring SELL_BACKGROUND = L"SellBackground";
	const sf::Color SELL_BACKGROUND_COLOR = sf::Color(255, 54, 54);

	const std::wstring SELL_LABLE = L"SellLable";
	const std::wstring SELL_LABLE_LABLE = L"Sell";

	const std::wstring SELL_MIN1 = L"Sell_MIN1";
	const double SELL_MIN1_LABLE = 100000.0;
	const std::wstring SELL_MIN5 = L"Sell_MIN5";
	const double SELL_MIN5_LABLE = 100000.0;
	const std::wstring SELL_MIN15 = L"Sell_MIN15";
	const double SELL_MIN15_LABLE = 100000.0;
	const std::wstring SELL_MIN30 = L"Sell_MIN30";
	const double SELL_MIN30_LABLE = 100000.0;
	const std::wstring SELL_HOUR1 = L"Sell_HOUR1";
	const double SELL_HOUR1_LABLE = 100000.0;
	const std::wstring SELL_HOUR4 = L"Sell_HOUR4";
	const double SELL_HOUR4_LABLE = 100000.0;
	// ------- //

	// Time's //
	const std::wstring TIME_BACKGROUND = L"TimeBackground";
	const sf::Color TIME_BACKGROUND_COLOR = sf::Color(105, 89, 89);

	const std::wstring TIME_LABLE = L"TimeLable";
	const std::wstring TIME_LABLE_LABLE = L"Time";

	const std::wstring TIME_MIN1 = L"Time_MIN1";
	const std::wstring TIME_MIN1_LABLE = L"12:29";
	const std::wstring TIME_MIN5 = L"Time_MIN5";
	const std::wstring TIME_MIN5_LABLE = L"12:29";
	const std::wstring TIME_MIN15 = L"Time_MIN15";
	const std::wstring TIME_MIN15_LABLE = L"12:29";
	const std::wstring TIME_MIN30 = L"Time_MIN30";
	const std::wstring TIME_MIN30_LABLE = L"12:29";
	const std::wstring TIME_HOUR1 = L"Time_HOUR1";
	const std::wstring TIME_HOUR1_LABLE = L"12:29";
	const std::wstring TIME_HOUR4 = L"Time_HOUR4";
	const std::wstring TIME_HOUR4_LABLE = L"12:29";
	// ------- //
}

namespace window
{
	const int WIN_WIDTH = 900;
	const int WIN_HEIGHT = 800;
	const std::wstring winName = L"Main";
	const int TEXT_SIZE = 20;
}

#endif /* MACRO_H_ */
