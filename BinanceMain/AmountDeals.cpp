#include "AmountDeals.hpp"

const sf::Color DEFAULT_COLOR = sf::Color(230, 230, 230);
const sf::Color ACTIVE_COLOR = sf::Color::Green;

AmountDeals::AmountDeals(AmountDealsData& data, TimeFrame timeFrame, int timeInMin)
{
	this->lable = new UI::TextLable<std::wstring>(data.lableText, data.lableData.coords, window::TEXT_SIZE);
	this->lable->SetRect(data.lableData.rect);
	this->lable->SetBackground(DEFAULT_COLOR);

	this->buy = new UI::TextLable<double>(data.buyValue, data.buyData.coords, window::TEXT_SIZE);
	this->buy->SetRect(data.buyData.rect);

	this->sell = new UI::TextLable<double>(data.sellValue, data.sellData.coords, window::TEXT_SIZE);
	this->sell->SetRect(data.sellData.rect);

	this->time = new UI::TextLable<std::wstring>(data.timeText, data.timeData.coords, window::TEXT_SIZE);
	this->time->SetRect(data.timeData.rect);

	this->timeFrame = timeFrame;
	this->lastTime = 0;

	timeInMin /= timeFrame;
	timeInMin *= timeFrame;

	this->time->SetText(GetTimeStr(timeInMin));
}
AmountDeals::AmountDeals(const AmountDeals& amountDeals)
{
	*this = amountDeals;
}

std::wstring AmountDeals::GetTimeStr(int timeInMin)
{
	std::wstring data = L"";
	std::wostringstream strValue;

	int hours = timeInMin / 60;
	int minutes = timeInMin % 60;

	strValue << hours;
	data += strValue.str() + L":";
	strValue.str(L"");

	strValue << minutes;
	if (minutes < 10)
		data += L"0";
	data += strValue.str();

	return data;
}

int AmountDeals::Update(sf::RenderWindow& window, UI::EventControl eventControl, int timeInMin)
{
	this->lable->Update(window, eventControl);
	this->buy->Update(window, eventControl);
	this->sell->Update(window, eventControl);
	this->time->Update(window, eventControl);

	// Update all
	if ((timeInMin % static_cast<int>(this->timeFrame) == 0)
		&& timeInMin > this->lastTime)
	{
		this->lastTime = timeInMin;
	
		// Update time lable
		this->time->SetText(GetTimeStr(timeInMin));

		// Reset buy and sell values
		Reset();
	}


	return 0;
}

int AmountDeals::AddBuy(double buyPrice)
{
	double tempPrice = 0.0;
	tempPrice = this->buy->GetText();
	tempPrice += buyPrice;

	this->buy->SetText(tempPrice);

	return 0;
}
int AmountDeals::AddSell(double sellPrice)
{
	double tempPrice = 0.0;

	tempPrice = this->sell->GetText();
	tempPrice += sellPrice;

	return 0;
}
int AmountDeals::Reset()
{
	// Reset the buy and sell values
	this->buy->SetText(0.0);
	this->sell->SetText(0.0);

	return 0;
}

AmountDeals& AmountDeals::operator=(const AmountDeals& amountDeals)
{
	if (this == &amountDeals)
		return *this;

	this->timeFrame = amountDeals.timeFrame;
	this->lastTime = amountDeals.lastTime;

	this->lable = new UI::TextLable<std::wstring>(*(amountDeals.lable));
	this->buy = new UI::TextLable<double>(*(amountDeals.buy));
	this->sell = new UI::TextLable<double>(*(amountDeals.sell));
	this->time = new UI::TextLable<std::wstring>(*(amountDeals.time));

	return *this;
}

AmountDeals::~AmountDeals()
{
	if (this->lable != nullptr) delete this->lable;
	if (this->buy != nullptr) delete this->buy;
	if (this->sell != nullptr) delete this->sell;
	if (this->time != nullptr) delete this->time;
}
