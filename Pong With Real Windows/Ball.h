#pragma once
#define _USE_MATH_DEFINES
#include "GameElement.h"
#include <Windows.h>
#include <cmath>
#include <cstdlib>
#include <atltypes.h>
#include "ConfigManager.h"
#include "Paddle.h"

class Ball : public GameElement
{
private:
	const float m_defaultSpeed = 500;
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
public:
	Ball(RECT* desktop, ConfigManager* configManager, Paddle* paddleLeft, Paddle* paddleRight);
	void update(sf::Time deltaTime) override;
};

