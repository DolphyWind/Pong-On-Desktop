#include "Paddle.h"

Paddle::Paddle(RECT *desktop, bool firstPlayer, ConfigManager *configManager) : GameElement(desktop, configManager)
{
	m_paddleSize = sf::Vector2u(25, ((int)desktop->bottom - (int)desktop->top) / 6);

	if (firstPlayer)
	{
		m_paddlePos.x = (int)desktop->left;
		m_paddlePos.y = ((int)desktop->bottom - (int)desktop->top) / 2 - (int)m_paddleSize.y / 2;
		m_upKey = (sf::Keyboard::Key)configManager->get(Paddle1UpKey);
		m_downKey = (sf::Keyboard::Key)configManager->get(Paddle1DownKey);
		setClearColor(sf::Color(
			configManager->get(Paddle1RKey),
			configManager->get(Paddle1GKey),
			configManager->get(Paddle1BKey)
		));
	}
	else
	{
		m_paddlePos.x = (int)desktop->right - m_paddleSize.x;
		m_paddlePos.y = ((int)desktop->bottom - (int)desktop->top) / 2 - (int)m_paddleSize.y / 2;
		m_upKey = (sf::Keyboard::Key)configManager->get(Paddle2UpKey);
		m_downKey = (sf::Keyboard::Key)configManager->get(Paddle2DownKey);
		setClearColor(sf::Color(
			configManager->get(Paddle2RKey),
			configManager->get(Paddle2GKey),
			configManager->get(Paddle2BKey)
		));
	}

	m_window.create(sf::VideoMode(m_paddleSize.x, m_paddleSize.y), "Paddle", sf::Style::None);
	m_window.setPosition(m_paddlePos);
	m_window.setFramerateLimit(60);
	m_speed = m_configManager->get(PaddleSpeedKey);
	m_score = 0;
}

void Paddle::update(sf::Time deltaTime)
{
	m_time += deltaTime.asSeconds();
	if (m_time < 1) return;

	m_movementScalar = 0;

	sf::Vector2i prevPos = m_paddlePos;
	if (sf::Keyboard::isKeyPressed(m_upKey))
		m_movementScalar = -1;
		
	else if (sf::Keyboard::isKeyPressed(m_downKey))
		m_movementScalar = 1;
	
	m_paddlePos.y += m_movementScalar * m_speed * deltaTime.asSeconds();
	
	if (m_paddlePos.y < m_desktop->top) m_paddlePos.y = m_desktop->top;
	if (m_paddlePos.y + m_paddleSize.y > m_desktop->bottom) m_paddlePos.y = m_desktop->bottom - m_paddleSize.y;

	if(prevPos != m_paddlePos)
		m_window.setPosition(m_paddlePos);

	// Make always on top
	SetWindowPos(m_window.getSystemHandle(), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
}

void Paddle::reposition(bool firstPlayer)
{
	if (firstPlayer)
	{
		m_paddlePos.x = (int)m_desktop->left;
		m_paddlePos.y = ((int)m_desktop->bottom - (int)m_desktop->top) / 2 - (int)m_paddleSize.y / 2;
	}
	else
	{
		m_paddlePos.x = (int)m_desktop->right - m_paddleSize.x;
		m_paddlePos.y = ((int)m_desktop->bottom - (int)m_desktop->top) / 2 - (int)m_paddleSize.y / 2;
	}
	m_window.setPosition(m_paddlePos);
}

unsigned int Paddle::getScore()
{
	return m_score;
}

void Paddle::setScore(unsigned int score)
{
	m_score = score;
}

int Paddle::getMovementScalar()
{
	return m_movementScalar;
}
