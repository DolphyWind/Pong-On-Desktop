#pragma once
#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <iostream>
#include <vector>
#include "GameElement.h"
#include "ConfigManager.h"
#include "Paddle.h"
#include "Ball.h"
#include "ScoreBoard.h"

class GameManager
{
private:
	RECT m_desktop;
	bool m_gameOver = false;
	sf::Clock m_deltaClock;
	sf::Time m_deltaTime;
	std::vector<GameElement*> m_gameElements;
	ConfigManager m_configManager;
	sf::Font m_font;
	unsigned int m_maxScore;
	Paddle* m_leftPaddle;
	Paddle* m_rightPaddle;
	Ball* m_ball;
	ScoreBoard* m_scoreBoard;
public:
	GameManager();
	~GameManager();
	void handleEvents();
	void update();
	void draw();
	void mainLoop();
};

