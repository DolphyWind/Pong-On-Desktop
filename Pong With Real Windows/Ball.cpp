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
	while (true)
	{
		float angle;
		angle = (rand() % 360) * M_PI / 180 - M_PI;
		m_moveVector.x = m_speed * cos(angle);
		m_moveVector.y = m_speed * sin(angle);
		if (std::fabs(angle) > M_PI / 3 && std::fabs(angle) < 2 * M_PI / 3) continue;
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
	randomizeAngle();

	m_paddleLeft->reposition(true);
	m_paddleRight->reposition(false);

	resetTime();
	m_paddleLeft->resetTime();
	m_paddleRight->resetTime();
}

Ball::Ball(RECT* desktop, ConfigManager* configManager, Paddle* paddleLeft, Paddle* paddleRight) : GameElement(desktop, configManager)
{
	m_radius = 15;
	m_speed = 500;
	m_paddleLeft = paddleLeft;
	m_paddleRight = paddleRight;

	m_window.create(sf::VideoMode(2 * m_radius, 2 * m_radius), "Ball", sf::Style::None);
	m_window.setPosition(sf::Vector2i(
		((int)desktop->right - (int)desktop->left) / 2 - m_radius,
		((int)desktop->bottom - (int)desktop->top) / 2 - m_radius
	));
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
	m_window.setPosition(sf::Vector2i(
		m_window.getPosition().x + m_moveVector.x * deltaTime.asSeconds(),
		m_window.getPosition().y + m_moveVector.y * deltaTime.asSeconds()
	));
	checkWallCollision();
	checkPaddleCollision();

	// Make always on top
	SetWindowPos(m_window.getSystemHandle(), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
}

void Ball::checkWallCollision()
{
	sf::Vector2i windowPos = m_window.getPosition();
	if (windowPos.y < m_desktop->top || windowPos.y + 2 * m_radius > m_desktop->bottom)
		m_moveVector.y *= -1;
	if (windowPos.x < m_desktop->left)
	{
		m_paddleLeft->increaseScore();
		restartGame();
	}
	if (windowPos.x + 2 * m_radius > m_desktop->right)
	{
		m_paddleRight->increaseScore();
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

	if (ballShape.getGlobalBounds().intersects(paddleLeftShape.getGlobalBounds()) && m_moveVector.x < 0)
	{
		// For now multiply by -1 I'll add a better system later on
		m_moveVector.x *= -1;
	}
	if (ballShape.getGlobalBounds().intersects(paddleRightShape.getGlobalBounds()) && m_moveVector.x > 0)
	{
		// For now multiply by -1 I'll add a better system later on
		m_moveVector.x *= -1;
	}
}
