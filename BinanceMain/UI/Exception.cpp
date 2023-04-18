#ifdef __linux__
#include "Exception.hpp"
#elif _WIN32
#include "Exception.hpp"
#endif

Exception::Exception(std::string message, std::string file, int line)
	:message(message), file(file), line(line)
{
	sf::RenderWindow exceptionWin(sf::VideoMode(350, 250), "Exception");
	UI::TextButton<std::wstring> exit(L"Exception!", sf::Vector2f(0, 0), 20);
	exit.SetRect(sf::IntRect(0, 0, 200, 70));

	std::cout << message << ", in file: " << file << ", line: " << line << std::endl;

	while (exceptionWin.isOpen())
	{
		UI::EventControl eventControl;
		sf::Event event;

		while (exceptionWin.pollEvent(event))
		{
			eventControl.events.push_back(event);
			switch (event.type)
			{
			case sf::Event::Closed:
				exceptionWin.close();
				::exit(-1);
				break;

			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Escape)
				{
					exceptionWin.close();
					::exit(-1);
				}

				break;

			default:
				break;
			}
		}

		// ���������� ���������� ���� //
		sf::Vector2i pixelPosition = sf::Mouse::getPosition(exceptionWin);
		sf::Vector2f mousePosition = exceptionWin.mapPixelToCoords(pixelPosition);

		eventControl.cursorPosition = mousePosition;
		// -------------------------- //

		// ������� ������
		exceptionWin.clear(sf::Color::White);

		UI::ElementCode code = exit.Update(exceptionWin, eventControl);
		if (code == UI::ONCLICK_L)
		{
			::exit(-1);
		}

		// ��������� ��������
		exceptionWin.display();
	}
}
