#pragma once
#define _USE_MATH_DEFINES
#include "GameElement.h"
#include <Windows.h>
#include <cmath>
#include <cstdlib>
#include <atltypes.h>
#include "ConfigManager.h"
#include "Paddle.h"
#include "ScoreBoard.h"

class Ball : public GameElement
{
private:
	float m_defaultSpeed;
	float m_speedIncrement;
	float m_radius;
	float m_speed;
	void makeCircular();
	void randomizeAngle();
	void restartGame();
	void checkWallCollision();
	void checkPaddleCollision();
	sf::Vector2f m_moveVector;
	Paddle* m_paddleLeft;
	Paddle* m_paddleRight;
	sf::Vector2f normalizeVector(const sf::Vector2f& vec);
	ScoreBoard* m_scoreBoard;
public:
	Ball(RECT* desktop, ConfigManager* configManager, Paddle* paddleLeft, Paddle* paddleRight, ScoreBoard* scoreBoard);
	void update(sf::Time deltaTime) override;
};

