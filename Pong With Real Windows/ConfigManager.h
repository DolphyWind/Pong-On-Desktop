#pragma once
#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <map>
#include <tuple>
#include <unordered_map>
#include <filesystem>
#include "keyvalues.h"

class ConfigManager
{
private:
	std::vector<std::string> m_stringifiedKeys;
	std::ofstream m_fileWrite;
	std::ifstream m_fileRead;
	const std::string m_filename = "GameConfig.txt";
	std::map<std::string, std::tuple<int, std::string>, std::greater<std::string>> m_values;
	void loadFile();
	void createFile();
	void resetSettings();
	std::string lrTrim(const std::string& str);
public:
	ConfigManager();
	~ConfigManager();
	int get(const std::string& key);
};

