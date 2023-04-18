#ifndef AMOUNT_DEALS_H_
#define AMOUNT_DEALS_H_
#include "Macro.hpp"
#include "UI/Lable.hpp"
#include "UI/Button.hpp"
#include "UI/Manager.hpp"


enum TimeFrame
{
	MIN_1	= 1,
	MIN_5	= 5,
	MIN_15	= 15,
	MIN_30	= 30,
	HOUR_1	= 60,
	HOUR_4	= 240
};

struct AmountDealsData
{
	UI::IControlData lableData;
	std::wstring lableText;

	UI::IControlData buyData;
	double buyValue;

	UI::IControlData sellData;
	double sellValue;

	UI::IControlData timeData;
	std::wstring timeText;
};

class AmountDeals
{
	TimeFrame timeFrame;
	int lastTime;
	int startTime;

	UI::TextLable<std::wstring>* lable = nullptr;
	UI::TextLable<double>* buy = nullptr;
	UI::TextLable<double>* sell = nullptr;
	UI::TextLable<std::wstring>* time = nullptr;

	std::wstring GetTimeStr(int timeInMin);

public:
	AmountDeals(AmountDealsData& data, TimeFrame timeFrame, int timeInMin);
	AmountDeals(const AmountDeals& amountDeals);

	int Update(sf::RenderWindow& window, UI::EventControl eventControl, int timeInMin);

	int AddBuy(double buyPrice);
	int AddSell(double sellPrice);
	int Reset();

	AmountDeals& operator=(const AmountDeals& amountDeals);

	~AmountDeals();
};

#endif // AMOUNT_DEALS_H_
