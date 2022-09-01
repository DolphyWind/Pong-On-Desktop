#pragma once
#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <iostream>
#include <vector>
#include "GameElement.h"
#include "ConfigManager.h"
#include "Paddle.h"
#include "Ball.h"

class GameManager
{
private:
	RECT m_desktop;
	bool m_gameOver = false;
	sf::Clock m_deltaClock;
	sf::Time m_deltaTime;
	std::vector<GameElement*> m_gameElements;
	ConfigManager m_configManager;
public:
	GameManager();
	~GameManager();
	void handleEvents();
	void update();
	void draw();
	void mainLoop();
};

