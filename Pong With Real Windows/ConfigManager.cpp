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
				m_values[key] = std::make_tuple(value, std::get<std::string>(m_values.at(key)));
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
		m_fileWrite << p.first << "=" << std::get<int>(p.second) << " #" << std::get<std::string>(p.second) << std::endl;
	m_fileWrite << std::endl << "# Visit https://documentation.help/SFML.Net/7aeaa645-3732-3c60-a542-8732c47880e2.htm to see which number corresponds to which key";
	m_fileWrite.close();
}

void ConfigManager::resetSettings()
{
	m_values.insert({ UseAllDisplaysKey, std::make_tuple(0, "Uses all monitors that you have. 0: False, 1: True") });
	m_values.insert({ WinScoreKey, std::make_tuple(10, "The amount of score a player get in order to win") });
	m_values.insert({ Paddle1RKey, std::make_tuple(255, "R component of left paddle's color") });
	m_values.insert({ Paddle1GKey, std::make_tuple(255, "G component of left paddle's color") });
	m_values.insert({ Paddle1BKey, std::make_tuple(255, "B component of left paddle's color") });
	m_values.insert({ Paddle2RKey, std::make_tuple(255, "R component of right paddle's color") });
	m_values.insert({ Paddle2GKey, std::make_tuple(255, "G component of right paddle's color") });
	m_values.insert({ Paddle2BKey, std::make_tuple(255, "B component of right paddle's color") });
	m_values.insert({ BallRKey, std::make_tuple(255, "R component of ball's color") });
	m_values.insert({ BallGKey, std::make_tuple(255, "G component of ball's color") });
	m_values.insert({ BallBKey, std::make_tuple(255, "B component of ball's color") });
	m_values.insert({ Paddle1UpKey, std::make_tuple(sf::Keyboard::Key::W, "Left paddle up key") });
	m_values.insert({ Paddle1DownKey, std::make_tuple(sf::Keyboard::Key::S, "Left paddle down key") });
	m_values.insert({ Paddle2UpKey, std::make_tuple(sf::Keyboard::Key::Up, "Right paddle up key") });
	m_values.insert({ Paddle2DownKey, std::make_tuple(sf::Keyboard::Key::Down, "Right paddle down key") });
	m_values.insert({ QuitKey, std::make_tuple(sf::Keyboard::Key::Escape, "Key to press in order to quit game") });
	m_values.insert({ BallStarterSpeedKey, std::make_tuple(600, "Starter speed of the ball") });
	m_values.insert({ BallSpeedIncrementKey, std::make_tuple(15, "Every time ball collides with a paddle it increases its speed by this value") });
	m_values.insert({ PaddleSpeedKey, std::make_tuple(700, "Speed of each paddle") });
}

std::string ConfigManager::lrTrim(const std::string& str)
{
	std::size_t firstNonSpace = str.find_first_not_of(' ');
	std::size_t lastNonSpace = str.find_last_not_of(' ') + 1;
	return str.substr(firstNonSpace, lastNonSpace);
}

int ConfigManager::get(const std::string& key)
{
	return std::get<int>(m_values.at(key));
}

ConfigManager::ConfigManager()
{
	resetSettings();
	loadFile();
}

ConfigManager::~ConfigManager()
{
	
}
