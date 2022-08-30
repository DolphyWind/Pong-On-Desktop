#include "ConfigManager.h"

void ConfigManager::loadFile()
{
	if (std::filesystem::exists(m_filename))
	{
		m_fileRead.open(m_filename);

		std::string line;
		while (std::getline(m_fileRead, line))
		{
			std::size_t hashTagPos = line.find_first_of('#');
			line = line.substr(0, hashTagPos);
			if (line.empty()) continue;
			line = lrTrim(line);
			if (line.empty()) continue;
			
			try
			{
				std::size_t equalSign = line.find_first_of('=');
				std::string key = line.substr(0, equalSign);
				std::string valueStr = line.substr(equalSign + 1);
				for (char& c : valueStr)
				{
					if (isalpha(c)) throw std::exception();
				}
				int value = std::stoi(valueStr);
				m_values[key] = value;
			}
			catch (std::exception& e)
			{
				m_fileRead.close();
				resetSettings();
				createFile();
			}
		}

		m_fileRead.close();
	}
	else
		createFile();
}

void ConfigManager::createFile()
{
	m_fileWrite.open(m_filename);
	m_fileWrite << "# The symbol '#' makes rest of the line a comment." << std::endl << std::endl;
	for (auto& p : m_values)
		m_fileWrite << p.first << "=" << p.second << std::endl;
	m_fileWrite << std::endl << "# Visit https://documentation.help/SFML.Net/7aeaa645-3732-3c60-a542-8732c47880e2.htm to see which number corresponds to which key";
	m_fileWrite.close();
}

void ConfigManager::resetSettings()
{
	m_values.insert({ "General_UseAllDisplays", 0 });
	m_values.insert({ "General_WinScore", 10 });
	m_values.insert({ "Color_Paddle1_R", 255 });
	m_values.insert({ "Color_Paddle1_G", 255 });
	m_values.insert({ "Color_Paddle1_B", 255 });
	m_values.insert({ "Color_Paddle2_R", 255 });
	m_values.insert({ "Color_Paddle2_G", 255 });
	m_values.insert({ "Color_Paddle2_B", 255 });
	m_values.insert({ "Color_Ball_R", 255 });
	m_values.insert({ "Color_Ball_G", 255 });
	m_values.insert({ "Color_Ball_B", 255 });
	m_values.insert({ "Keyboard_Paddle1_UpKey", sf::Keyboard::Key::W });
	m_values.insert({ "Keyboard_Paddle1_DownKey", sf::Keyboard::Key::S });
	m_values.insert({ "Keyboard_Paddle2_UpKey", sf::Keyboard::Key::Up });
	m_values.insert({ "Keyboard_Paddle2_DownKey", sf::Keyboard::Key::Down });
}

std::string ConfigManager::lrTrim(const std::string& str)
{
	std::size_t firstNonSpace = str.find_first_not_of(' ');
	std::size_t lastNonSpace = str.find_last_not_of(' ') + 1;
	return str.substr(firstNonSpace, lastNonSpace);
}

ConfigManager::ConfigManager()
{
	resetSettings();
	loadFile();
}

ConfigManager::~ConfigManager()
{
	
}
