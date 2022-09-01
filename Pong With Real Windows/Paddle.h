#pragma once
#include "GameElement.h"
#include <Windows.h>
#include <SFML/Graphics.hpp>
#include "ConfigManager.h"

class Paddle : public GameElement
{
private:
	sf::Vector2u m_paddleSize;
	sf::Vector2i m_paddlePos;
	sf::Keyboard::Key m_upKey, m_downKey;
	float m_speed;
	unsigned int m_score;
	int m_movementScalar;
public:
	Paddle(RECT *desktop, bool firstPlayer, ConfigManager *configManager);
	void update(sf::Time deltaTime) override;
	void reposition(bool firstPlayer);
	unsigned int getScore();
	void setScore(unsigned int score);
	int getMovementScalar();
};

