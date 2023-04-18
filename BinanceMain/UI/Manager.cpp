#ifdef __linux__
#include "Manager.hpp"
#elif _WIN32
#include "Manager.hpp"
#endif

using namespace UI;
#include <dirent.h>
bool UI::isDebug = false;

/* IControlData */
IControlData::IControlData() {}
IControlData::IControlData(sf::Vector2f coords, sf::IntRect rect)
{
	this->coords = coords;
	this->rect = rect;
}
/* ------------ */


/* DataManager */
DataManger::DataManger(std::wstring filePath)
{
	this->filePath = filePath;
}

bool DataManger::SaveData(std::vector<IControl*>& items, std::vector<std::wstring>& names)
{
	if (!(items.size() > 0 && items.size() == names.size()))
		return false;

	// �������� ����� //
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    std::string filename = converter.to_bytes(this->filePath);
	std::wofstream file(filename);
	if (!file.is_open())
		return false;
	// -------------- //

	// ���������� ������ ��� ������ //
	std::wstring data = L"";
	std::wostringstream strValue;

	for (size_t i = 0; i < items.size(); i++)
	{
		strValue << i;

		// ������
		data += L"@" + strValue.str() + L";";
		strValue.str(L"");

		// ���
		data += names[i] + L";";

		// Coords
		strValue << items[i]->GetPosition().x;
		data += strValue.str() + L";";
		strValue.str(L"");

		strValue << items[i]->GetPosition().y;
		data += strValue.str() + L";";
		strValue.str(L"");

		// Rect
		strValue << items[i]->GetRect().width;
		data += strValue.str() + L";";
		strValue.str(L"");

		strValue << items[i]->GetRect().height;
		data += strValue.str() + L";";
		strValue.str(L"");

		// �����
		data += L"\n";

		file << data;
		data = L"";
	}
	// ---------------------------- //

	file.close();

	return true;
}

bool DataManger::ReadData()
{
	// �������� ����� //
	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    std::string filename = converter.to_bytes(this->filePath);
	std::wifstream file(filename);
	if (!file.is_open())
		return false;
	// -------------- //

	// �������� ������ �� �����
	std::wstring data = L"";
	std::wstring fileData;
	while (file >> fileData)
	{
		data += fileData;
	}
	// ----------

	// ������������ ������ IControl //
	size_t index = 0;
	std::wstring controlData;

	// �������� �� ����� �����
	while (index < data.size())
	{
		size_t currentPos = 0;
		while ((data[index + currentPos] != L'@' || (index == 0 && currentPos == 0)) && (index + currentPos) < data.size())
		{
			currentPos++;
		}

		if (index != 0)
		{
			for (size_t i = 0; i < currentPos; i++)
			{
				controlData += data[i + index];
			}
		}
		else
		{
			for (size_t i = 1; i < currentPos; i++)
			{
				controlData += data[i + index];
			}
		}

		currentPos++;
		index += currentPos;

		// ������ ������ //
		if (this->items.size() < 10)
			controlData.erase(0, 2); // ������� ������ (< 10)
		else if (this->items.size() < 100)
			controlData.erase(0, 3); // ������� ������ (< 100)
		else if (this->items.size() < 1000)
			controlData.erase(0, 4); // ������� ������ (< 1000)
		else
			throw new Exception("index more than 1000", __FILE__, __LINE__);

		// ��� ������� //
		size_t tempIndex = 0;
		while (controlData[tempIndex] != L';')
		{
			tempIndex++;
		}

		this->names.push_back(controlData.substr(0, tempIndex));
		controlData.erase(0, tempIndex + 1);
		// ----------- //

		std::wstringstream* numberValue = new std::wstringstream;

		// ���������� ������� //
		sf::Vector2f coords;
		tempIndex = 0;
		while (controlData[tempIndex] != L';')
		{
			tempIndex++;
		}
		numberValue->str(controlData.substr(0, tempIndex));
		numberValue->operator>>(coords.x);
		numberValue->str(L"");
		controlData.erase(0, tempIndex + 1);

		delete numberValue;
		numberValue = new std::wstringstream;

		tempIndex = 0;
		while (controlData[tempIndex] != L';')
		{
			tempIndex++;
		}
		numberValue->str(controlData.substr(0, tempIndex));
		numberValue->operator>>(coords.y);
		numberValue->str(L"");
		controlData.erase(0, tempIndex + 1);

		delete numberValue;
		numberValue = new std::wstringstream;
		// ------------------ //

		// ������� ������� //
		sf::IntRect rect;

		tempIndex = 0;
		while (controlData[tempIndex] != L';')
		{
			tempIndex++;
		}
		numberValue->str(controlData.substr(0, tempIndex));
		numberValue->operator>>(rect.width);
		numberValue->str(L"");
		controlData.erase(0, tempIndex + 1);

		delete numberValue;
		numberValue = new std::wstringstream;

		tempIndex = 0;
		while (controlData[tempIndex] != L';')
		{
			tempIndex++;
		}
		numberValue->str(controlData.substr(0, tempIndex));
		numberValue->operator>>(rect.height);
		numberValue->str(L"");
		controlData.erase(0, tempIndex + 1);
		// --------------- //

		// ���������� ������ //
		this->items.push_back(IControlData(coords, rect));
		// ----------------- //

		// ------------- //

		controlData = L"";
	}
	// ---------------------------- //

	return true;
}
IControlData DataManger::GetData(int index)
{
	if (index < 0 || static_cast<size_t>(index) >= this->items.size())
		throw new Exception("Index under zero!", __FILE__, __LINE__);

	return this->items[index];
}
IControlData DataManger::GetData(std::wstring name)
{
	for (size_t i = 0; i < this->names.size(); i++)
	{
		if (this->names[i] == name)
			return this->items[i];
	}

	std::wcout << name << std::endl;
	throw new Exception("Name not found", __FILE__, __LINE__);
}
/* ----------- */


/* Debug */
Debug::Debug(std::wstring dataFilePath, bool isEnable)
	:dataManger(dataFilePath)
{
	UI::isDebug = isEnable;
	this->currentItem = -1;

	this->isCtrlPressed = false;
	this->isShiftPressed = false;
}

void Debug::AddItem(IControl* item, std::wstring name)
{
	if (item != nullptr)
	{
		this->items.push_back(item);
		this->names.push_back(name);
	}
}
void Debug::GetInConsoleItemsCoords()
{
	if (UI::isDebug == true)
	{
		for (size_t i = 0; i < this->items.size(); i++)
		{
			std::wcout << "Name: " << this->names[i] << ", X: " << this->items[i]->GetPosition().x << ", Y: " << this->items[i]->GetPosition().y << std::endl;
		}
	}
}

ElementCode Debug::Update(sf::RenderWindow& window, EventControl& eventControl)
{
	for (size_t i = 0; i < this->items.size(); i++)
	{
		// ��������� ��� �� ������ �����-�� �������
		if (this->items[i]->Update(window, eventControl) == ONCLICK_R)
		{
			// ���� ������ �������� ��������� � ����������, �� "���������" �������
			if (this->currentItem == static_cast<int>(i))
			{
				this->currentItem = -1;
			}
			// ����� ��������� ������ ��������
			else
			{
				this->currentItem = static_cast<int>(i);
			}
		}
	}

	if (UI::isDebug == true)
	{
		// ��������� ������� ������ ����������
		for (size_t i = 0; i < eventControl.events.size(); i++)
		{
			switch (eventControl.events[i].type)
			{
			case sf::Event::KeyPressed:
				if (eventControl.events[i].key.code == sf::Keyboard::LControl)
				{
					this->isCtrlPressed = true;
				}
				if (eventControl.events[i].key.code == sf::Keyboard::LShift)
				{
					this->isShiftPressed = true;
				}

				if (this->currentItem != -1)
				{
					if (this->isShiftPressed == true)
					{
						sf::IntRect rect = this->items[this->currentItem]->GetRect();
						if (eventControl.events[i].key.code == sf::Keyboard::Up)
						{
							rect.height -= 1;
							this->items[this->currentItem]->SetRect(rect);
						}
						else if (eventControl.events[i].key.code == sf::Keyboard::Right)
						{
							rect.width += 1;
							this->items[this->currentItem]->SetRect(rect);
						}
						else if (eventControl.events[i].key.code == sf::Keyboard::Down)
						{
							rect.height += 1;
							this->items[this->currentItem]->SetRect(rect);
						}
						else if (eventControl.events[i].key.code == sf::Keyboard::Left)
						{
							rect.width -= 1;
							this->items[this->currentItem]->SetRect(rect);
						}
					}
					else
					{
						sf::Vector2f coords = this->items[this->currentItem]->GetPosition();
						if (eventControl.events[i].key.code == sf::Keyboard::Up)
						{
							this->items[this->currentItem]->SetPosition(sf::Vector2f(coords.x, coords.y - 1));
						}
						else if (eventControl.events[i].key.code == sf::Keyboard::Right)
						{
							this->items[this->currentItem]->SetPosition(sf::Vector2f(coords.x + 1, coords.y));
						}
						else if (eventControl.events[i].key.code == sf::Keyboard::Down)
						{
							this->items[this->currentItem]->SetPosition(sf::Vector2f(coords.x, coords.y + 1));
						}
						else if (eventControl.events[i].key.code == sf::Keyboard::Left)
						{
							this->items[this->currentItem]->SetPosition(sf::Vector2f(coords.x - 1, coords.y));
						}
					}
				}

				break;

			case sf::Event::KeyReleased:
				if (eventControl.events[i].key.code == sf::Keyboard::LControl)
				{
					this->isCtrlPressed = false;
				}
				if (eventControl.events[i].key.code == sf::Keyboard::LShift)
				{
					this->isCtrlPressed = false;
				}
				break;

			default:
				break;
			}
		}

		if (this->isCtrlPressed == true)
		{
			if (this->currentItem != -1)
			{
				this->items[this->currentItem]->SetPosition(eventControl.cursorPosition);
			}
		}
	}

	return NONE;
}

Debug::~Debug()
{
	this->dataManger.SaveData(this->items, this->names);
	GetInConsoleItemsCoords();
}
/* ----- */
