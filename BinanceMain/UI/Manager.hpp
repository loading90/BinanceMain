#ifndef MANAGER_H_
#define MANAGER_H_
#include "Macro.hpp"
#include "Element.hpp"
#include "Exception.hpp"
#include <fstream>
#include <iostream>
#include <locale>
#include <string>
#include <codecvt>

namespace UI
{
	struct IControlData
	{
		sf::Vector2f coords;
		sf::IntRect rect;

		IControlData();
		IControlData(sf::Vector2f coords, sf::IntRect rect);
	};

	class DataManger
	{
		std::wstring filePath;

		std::vector<IControlData> items;
		std::vector<std::wstring> names;

	public:
		DataManger(std::wstring filePath);

		bool SaveData(std::vector<IControl*>& items, std::vector<std::wstring>& names);

		bool ReadData();
		IControlData GetData(int index);
		IControlData GetData(std::wstring name);
	};

	class Debug
	{
		std::vector<IControl*> items;
		std::vector<std::wstring> names;
		int currentItem;

		bool isCtrlPressed;
		bool isShiftPressed;

		DataManger dataManger;

	public:
		Debug(std::wstring dataFilePath = std::wstring(FILE_PATH) + std::wstring(FILE_NAME), bool isEnable = true);

		void AddItem(IControl* item, std::wstring name);
		void GetInConsoleItemsCoords();

		ElementCode Update(sf::RenderWindow& window, EventControl& eventControl);

		~Debug();
	};
}

#endif /* MANAGER_H_ */
