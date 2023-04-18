#include "Application.hpp"


Application::Application()
{
	this->window.create(sf::VideoMode(window::WIN_WIDTH, window::WIN_HEIGHT), window::winName);
	this->window.setVerticalSyncEnabled(true);
	this->window.setKeyRepeatEnabled(false);

	UI::DataManger manager(std::wstring(FILE_PATH) + std::wstring(FILE_NAME));
	if (manager.ReadData())
		std::cout << "Data file load" << std::endl;
	else
		throw new Exception("Cannot to read data file", __FILE__, __LINE__);

	time_t now = ::time(0);
	tm* ltm = localtime(&now);
	int minutes = ltm->tm_hour * 60 + ltm->tm_min;

	AmountDealsData amountDealsData;
	// Min 1 //
	amountDealsData.lableData = manager.GetData(elements::LABLE_MIN1);
	amountDealsData.lableText = elements::LABLE_MIN1_LABLE;
	amountDealsData.buyData = manager.GetData(elements::BUY_MIN1);
	amountDealsData.buyValue = elements::BUY_MIN1_LABLE;
	amountDealsData.sellData = manager.GetData(elements::SELL_MIN1);
	amountDealsData.sellValue = elements::SELL_MIN1_LABLE;
	amountDealsData.timeData = manager.GetData(elements::TIME_MIN1);
	amountDealsData.timeText = elements::TIME_MIN1_LABLE;

	this->amountDeals.push_back(AmountDeals(amountDealsData, MIN_1, minutes));
	// ----- //

	// Min 5 //
	amountDealsData.lableData = manager.GetData(elements::LABLE_MIN5);
	amountDealsData.lableText = elements::LABLE_MIN5_LABLE;
	amountDealsData.buyData = manager.GetData(elements::BUY_MIN5);
	amountDealsData.buyValue = elements::BUY_MIN5_LABLE;
	amountDealsData.sellData = manager.GetData(elements::SELL_MIN5);
	amountDealsData.sellValue = elements::SELL_MIN5_LABLE;
	amountDealsData.timeData = manager.GetData(elements::TIME_MIN5);
	amountDealsData.timeText = elements::TIME_MIN5_LABLE;

	this->amountDeals.push_back(AmountDeals(amountDealsData, MIN_5, minutes));
	// ----- //

	// Min 15 //
	amountDealsData.lableData = manager.GetData(elements::LABLE_MIN15);
	amountDealsData.lableText = elements::LABLE_MIN15_LABLE;
	amountDealsData.buyData = manager.GetData(elements::BUY_MIN15);
	amountDealsData.buyValue = elements::BUY_MIN15_LABLE;
	amountDealsData.sellData = manager.GetData(elements::SELL_MIN15);
	amountDealsData.sellValue = elements::SELL_MIN15_LABLE;
	amountDealsData.timeData = manager.GetData(elements::TIME_MIN15);
	amountDealsData.timeText = elements::TIME_MIN15_LABLE;

	this->amountDeals.push_back(AmountDeals(amountDealsData, MIN_15, minutes));
	// ----- //

	// Min 30 //
	amountDealsData.lableData = manager.GetData(elements::LABLE_MIN30);
	amountDealsData.lableText = elements::LABLE_MIN30_LABLE;
	amountDealsData.buyData = manager.GetData(elements::BUY_MIN30);
	amountDealsData.buyValue = elements::BUY_MIN30_LABLE;
	amountDealsData.sellData = manager.GetData(elements::SELL_MIN30);
	amountDealsData.sellValue = elements::SELL_MIN30_LABLE;
	amountDealsData.timeData = manager.GetData(elements::TIME_MIN30);
	amountDealsData.timeText = elements::TIME_MIN30_LABLE;

	this->amountDeals.push_back(AmountDeals(amountDealsData, MIN_30, minutes));
	// ----- //

	// Hour 1 //
	amountDealsData.lableData = manager.GetData(elements::LABLE_HOUR1);
	amountDealsData.lableText = elements::LABLE_HOUR1_LABLE;
	amountDealsData.buyData = manager.GetData(elements::BUY_HOUR1);
	amountDealsData.buyValue = elements::BUY_HOUR1_LABLE;
	amountDealsData.sellData = manager.GetData(elements::SELL_HOUR1);
	amountDealsData.sellValue = elements::SELL_HOUR1_LABLE;
	amountDealsData.timeData = manager.GetData(elements::TIME_HOUR1);
	amountDealsData.timeText = elements::TIME_HOUR1_LABLE;

	this->amountDeals.push_back(AmountDeals(amountDealsData, HOUR_1, minutes));
	// ------ //

	// Hour 4 //
	amountDealsData.lableData = manager.GetData(elements::LABLE_HOUR4);
	amountDealsData.lableText = elements::LABLE_HOUR4_LABLE;
	amountDealsData.buyData = manager.GetData(elements::BUY_HOUR4);
	amountDealsData.buyValue = elements::BUY_HOUR4_LABLE;
	amountDealsData.sellData = manager.GetData(elements::SELL_HOUR4);
	amountDealsData.sellValue = elements::SELL_HOUR4_LABLE;
	amountDealsData.timeData = manager.GetData(elements::TIME_HOUR4);
	amountDealsData.timeText = elements::TIME_HOUR4_LABLE;

	this->amountDeals.push_back(AmountDeals(amountDealsData, HOUR_4, minutes));
	// ------ //


	UI::IControlData tempData;
	// Lable's //
	tempData = manager.GetData(elements::BUY_LABLE);
	this->lables.push_back(UI::TextLable<std::wstring>(elements::BUY_LABLE_LABLE, tempData.coords, window::TEXT_SIZE));
	auto lableIt = this->lables.rbegin();
	lableIt->SetRect(tempData.rect);	// First by end
	lableIt->SetBackground(elements::BUY_BACKGROUND_COLOR);

	tempData = manager.GetData(elements::SELL_LABLE);
	this->lables.push_back(UI::TextLable<std::wstring>(elements::SELL_LABLE_LABLE, tempData.coords, window::TEXT_SIZE));
	lableIt = this->lables.rbegin();
	lableIt->SetRect(tempData.rect);
	lableIt->SetBackground(elements::SELL_BACKGROUND_COLOR);

	tempData = manager.GetData(elements::TIME_LABLE);
	this->lables.push_back(UI::TextLable<std::wstring>(elements::TIME_LABLE_LABLE, tempData.coords, window::TEXT_SIZE));
	lableIt = this->lables.rbegin();
	lableIt->SetRect(tempData.rect);
	lableIt->SetBackground(elements::TIME_BACKGROUND_COLOR);
	// ------- //

	// Background's //
	tempData = manager.GetData(elements::LABLE_BACKGROUND);
	this->backgrounds.push_back(UI::SolidBackground());
	
	auto backgroundIt = this->backgrounds.rbegin();
	backgroundIt->SetPosition(tempData.coords);
	backgroundIt->SetRect(tempData.rect);
	backgroundIt->SetBackground(elements::LABLE_BACKGROUND_COLOR);

	tempData = manager.GetData(elements::BUY_BACKGROUND);
	this->backgrounds.push_back(UI::SolidBackground());

	backgroundIt = this->backgrounds.rbegin();
	backgroundIt->SetPosition(tempData.coords);
	backgroundIt->SetRect(tempData.rect);
	backgroundIt->SetBackground(elements::BUY_BACKGROUND_COLOR);

	tempData = manager.GetData(elements::SELL_BACKGROUND);
	this->backgrounds.push_back(UI::SolidBackground());

	backgroundIt = this->backgrounds.rbegin();
	backgroundIt->SetPosition(tempData.coords);
	backgroundIt->SetRect(tempData.rect);
	backgroundIt->SetBackground(elements::SELL_BACKGROUND_COLOR);

	tempData = manager.GetData(elements::TIME_BACKGROUND);
	this->backgrounds.push_back(UI::SolidBackground());

	backgroundIt = this->backgrounds.rbegin();
	backgroundIt->SetPosition(tempData.coords);
	backgroundIt->SetRect(tempData.rect);
	backgroundIt->SetBackground(elements::TIME_BACKGROUND_COLOR);
	// ------------ //
	
	// Time //
	this->time = new UI::TextLable<std::wstring>(elements::CURRENT_TIME_LABLE, window::TEXT_SIZE);
	tempData = manager.GetData(elements::CURRENT_TIME);
	this->time->SetPosition(tempData.coords);
	this->time->SetRect(tempData.rect);
	// ---- //

	// Input //
	this->input = new UI::TextLable<std::wstring>(elements::INPUT_LABLE_LABLE, window::TEXT_SIZE);
	tempData = manager.GetData(elements::INPUT_LABLE);
	this->input->SetPosition(tempData.coords);
	this->input->SetRect(tempData.rect);
	// ----- //
}
Application::Application(const Application& app)
{
	*this = app;
}

std::wstring Application::GetStrTime(tm* ltm)
{
	std::wstring data = L"";
	std::wostringstream strValue;
	
	strValue << ltm->tm_hour;
	data += strValue.str() + L":";
	strValue.str(L"");

	strValue << ltm->tm_min;
	if (ltm->tm_min < 10)
		data += L"0";
	data += strValue.str() + L":";
	strValue.str(L"");

	strValue << ltm->tm_sec;
	if (ltm->tm_sec < 10)
		data += L"0";
	data += strValue.str();

	return data;
}
std::wstring Application::GetStrFullTime(tm* ltm)
{
	std::wstring data = L"";
	std::wostringstream strValue;

	strValue << ltm->tm_hour;
	data += strValue.str() + L":";
	strValue.str(L"");

	strValue << ltm->tm_min;
	if (ltm->tm_min < 10)
		data += L"0";
	data += strValue.str() + L":";
	strValue.str(L"");

	strValue << ltm->tm_sec;
	if (ltm->tm_sec < 10)
		data += L"0";
	data += strValue.str();

	return data;
}

void Application::Run()
{

	while (this->window.isOpen())
	{
		UI::EventControl eventControl;
		sf::Event event;

		while (this->window.pollEvent(event))
		{
			eventControl.events.push_back(event);
			switch (event.type)
			{
			case sf::Event::Closed:
				this->window.close();
				break;

			case sf::Event::MouseButtonPressed:
				break;

			case sf::Event::MouseButtonReleased:
				break;

			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Escape)
				{
					this->window.close();
				}

				break;

			case sf::Event::KeyReleased:

				break;

			default:
				break;
			}
		}

		sf::Vector2i pixelPosition = sf::Mouse::getPosition(this->window);
		sf::Vector2f mousePosition = this->window.mapPixelToCoords(pixelPosition);

		eventControl.cursorPosition = mousePosition;

		this->window.clear(sf::Color::White);

		time_t now = ::time(0);
		tm* ltm = localtime(&now);
		int minutes = ltm->tm_hour * 60 + ltm->tm_min;

		// Update All //
		for (auto& background : this->backgrounds)
			background.Update(this->window, eventControl);
		for (auto& amountDeal : this->amountDeals)
			amountDeal.Update(this->window, eventControl, minutes);
		for (auto& lable : this->lables)
			lable.Update(this->window, eventControl);

		this->time->SetText(GetStrTime(ltm));
		this->time->Update(this->window, eventControl);

		this->input->Update(this->window, eventControl);
		// ---------- //

		this->window.display();
	}

}

Application& Application::operator=(const Application& app)
{
	if (this == &app)
		return *this;

	this->window.create(sf::VideoMode(window::WIN_WIDTH, window::WIN_HEIGHT), window::winName);
	this->window.setVerticalSyncEnabled(true);
	this->window.setKeyRepeatEnabled(false);

	for (auto& background : app.backgrounds)
		this->backgrounds.push_back(background);
	for (auto& amountDeal : app.amountDeals)
		this->amountDeals.push_back(amountDeal);
	for (auto& lable : app.lables)
		this->lables.push_back(lable);

	this->time = new UI::TextLable<std::wstring>(*(app.time));
	this->input = new UI::TextLable<std::wstring>(*(app.input));

	return *this;
}

Application::~Application()
{
	if (this->time != nullptr) delete this->time;
	if (this->input != nullptr) delete this->input;
}
