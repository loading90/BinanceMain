#ifndef APPLICATION_H_
#define APPLICATION_H_
#include "Macro.hpp"
#include "UI/Manager.hpp"
#include "AmountDeals.hpp"


class Application
{
	sf::RenderWindow window;

	std::vector<AmountDeals> amountDeals;	// 1 min, 5 min, 15 min, 30 min, 1 hour, 4 hour
	
	std::vector<UI::SolidBackground> backgrounds;
	std::vector<UI::TextLable<std::wstring>> lables;


	UI::TextLable<std::wstring>* time = nullptr;
	UI::TextLable<std::wstring>* input = nullptr;

	std::wstring GetStrTime(tm* ltm);
	std::wstring GetStrFullTime(tm* ltm);

public:
	Application();
	Application(const Application& app);

	void Run();

	Application& operator=(const Application& app);

	~Application();
};

#endif /* APPLICATION_H_ */
