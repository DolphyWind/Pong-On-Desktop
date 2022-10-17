#include "Ball.h"

void Ball::makeCircular()
{
	SetWindowLong(m_window.getSystemHandle(), GWL_STYLE, GetWindowLong(m_window.getSystemHandle(), GWL_STYLE)
		& (~(WS_CAPTION | WS_BORDER)));
	CRect rect;
	GetWindowRect(m_window.getSystemHandle(), &rect);
	int w = rect.Width();
	int h = rect.Height();

	SetWindowRgn(m_window.getSystemHandle(), CreateRoundRectRgn(0, 0, w, h, w, h), TRUE);
}

void Ball::randomizeAngle()
{
	float max_angle = 50;
	while (true)
	{
		float angle;
		angle = (rand() % 360) * M_PI / 180 - M_PI;
		m_moveVector.x = m_speed * cos(angle);
		m_moveVector.y = m_speed * sin(angle);
		if (std::fabs(angle) > max_angle * M_PI / 180.f && std::fabs(angle) < (180.f - max_angle) * M_PI / 180.f) continue;
		break;
	}
}

void Ball::restartGame()
{
	// Update Scoreboard later
	m_window.setPosition(sf::Vector2i(
		((int)m_desktop->right - (int)m_desktop->left) / 2 - m_radius,
		((int)m_desktop->bottom - (int)m_desktop->top) / 2 - m_radius
	));
	m_windowPosition = {(float)m_window.getPosition().x, (float)m_window.getPosition().y};

	m_speed = m_defaultSpeed;
	randomizeAngle();

	m_paddleLeft->reposition(true);
	m_paddleRight->reposition(false);

	resetTime();
	m_paddleLeft->resetTime();
	m_paddleRight->resetTime();
}

sf::Vector2f Ball::normalizeVector(const sf::Vector2f& vec)
{
	float length = std::hypotf(vec.x, vec.y);
	return sf::Vector2f(vec.x / length, vec.y / length);
}

Ball::Ball(RECT* desktop, ConfigManager* configManager, Paddle* paddleLeft, Paddle* paddleRight, ScoreBoard* scoreBoard) : GameElement(desktop, configManager)
{
	m_radius = 15;
	m_defaultSpeed = m_configManager->get(BallStarterSpeedKey);
	m_speed = m_defaultSpeed;
	m_speedIncrement = m_configManager->get(BallSpeedIncrementKey);
	m_paddleLeft = paddleLeft;
	m_paddleRight = paddleRight;
	m_scoreBoard = scoreBoard;

	m_window.create(sf::VideoMode(2 * m_radius, 2 * m_radius), "Ball", sf::Style::None);
	m_window.setPosition(sf::Vector2i(
		((int)desktop->right - (int)desktop->left) / 2 - m_radius,
		((int)desktop->bottom - (int)desktop->top) / 2 - m_radius
	));
	m_windowPosition.x = m_window.getPosition().x;
	m_windowPosition.y = m_window.getPosition().y;

	setClearColor(sf::Color(
		configManager->get(BallRKey),
		configManager->get(BallGKey),
		configManager->get(BallBKey)
	));
	makeCircular();
	randomizeAngle();
}

void Ball::update(sf::Time deltaTime)
{
	m_time += deltaTime.asSeconds();
	if (m_time < 1) return;

	m_windowPosition.x += m_moveVector.x * deltaTime.asSeconds();
	m_windowPosition.y += m_moveVector.y * deltaTime.asSeconds();

	m_window.setPosition(sf::Vector2i(
		m_windowPosition.x,
		m_windowPosition.y
	));

	checkWallCollision();
	checkPaddleCollision();

	// Make always on top
	SetWindowPos(m_window.getSystemHandle(), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
}

void Ball::checkWallCollision()
{
	if (m_windowPosition.y < m_desktop->top && m_moveVector.y < 0)
	{
		m_moveVector.y *= -1;
	}
	if (m_windowPosition.y + 2 * m_radius > m_desktop->bottom && m_moveVector.y > 0)
	{
		m_moveVector.y *= -1;
	}

	//std::cout << m_moveVector.y << std::endl;
	
	if (m_windowPosition.x < m_desktop->left)
	{
		m_paddleRight->setScore(m_paddleRight->getScore() + 1);
		m_scoreBoard->updateScoreBoard(m_paddleLeft->getScore(), m_paddleRight->getScore());
		restartGame();
	}
	if (m_windowPosition.x + 2 * m_radius > m_desktop->right)
	{
		m_paddleLeft->setScore(m_paddleLeft->getScore() + 1);
		m_scoreBoard->updateScoreBoard(m_paddleLeft->getScore(), m_paddleRight->getScore());
		restartGame();
	}
}

void Ball::checkPaddleCollision()
{
	sf::Vector2i windowPos = m_window.getPosition();
	sf::RectangleShape ballShape;
	ballShape.setPosition(windowPos.x, windowPos.y);
	ballShape.setSize(sf::Vector2f(2 * m_radius, 2 * m_radius));

	sf::RectangleShape paddleLeftShape;
	paddleLeftShape.setPosition(m_paddleLeft->getPosition().x, m_paddleLeft->getPosition().y);
	paddleLeftShape.setSize(sf::Vector2f(m_paddleLeft->getSize().x, m_paddleLeft->getSize().y));

	sf::RectangleShape paddleRightShape;
	paddleRightShape.setPosition(m_paddleRight->getPosition().x, m_paddleRight->getPosition().y);
	paddleRightShape.setSize(sf::Vector2f(m_paddleRight->getSize().x, m_paddleRight->getSize().y));

	const float ratioMultiple = 0.18f;
	const float movementMultiple = 0.15f;

	if (ballShape.getGlobalBounds().intersects(paddleLeftShape.getGlobalBounds()) && m_moveVector.x < 0)
	{
		m_speed += m_speedIncrement;
		m_moveVector.x *= -1;
		m_moveVector = normalizeVector(m_moveVector);
		float paddleHalfLength = paddleLeftShape.getSize().y / 2;
		float ratio = (paddleLeftShape.getPosition().y + paddleHalfLength - ballShape.getPosition().y - m_radius) / paddleHalfLength;
		m_moveVector.y -= ratio * ratioMultiple;
		m_moveVector.y += m_paddleLeft->getMovementScalar() * movementMultiple;
		m_moveVector = normalizeVector(m_moveVector);
		m_moveVector.x *= m_speed;
		m_moveVector.y *= m_speed;
	}

	if (ballShape.getGlobalBounds().intersects(paddleRightShape.getGlobalBounds()) && m_moveVector.x > 0)
	{
		m_speed += m_speedIncrement;
		m_moveVector.x *= -1;
		m_moveVector = normalizeVector(m_moveVector);
		float paddleHalfLength = paddleRightShape.getSize().y / 2;
		float ratio = (paddleRightShape.getPosition().y + paddleHalfLength - ballShape.getPosition().y - m_radius) / paddleHalfLength;
		m_moveVector.y -= ratio * ratioMultiple;
		m_moveVector.y += m_paddleRight->getMovementScalar() * movementMultiple;
		m_moveVector = normalizeVector(m_moveVector);
		m_moveVector.x *= m_speed;
		m_moveVector.y *= m_speed;
	}
}
