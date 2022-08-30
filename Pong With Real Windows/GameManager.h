#pragma once
#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <iostream>
#include <vector>
#include "GameElement.h"
#include "ConfigManager.h"

class GameManager
{
private:
	RECT desktop;
	std::vector<GameElement> m_gameElements;
	ConfigManager m_configManager;
public:
	GameManager();
	void mainLoop();
};

