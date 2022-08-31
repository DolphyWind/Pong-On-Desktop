#include "Paddle.h"

Paddle::Paddle(RECT *desktop, bool firstPlayer, ConfigManager *configManager) : GameElement(desktop)
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
	m_speed = 5;
}

void Paddle::update(sf::Time deltaTime)
{
	sf::Vector2i prevPos = m_paddlePos;
	if (sf::Keyboard::isKeyPressed(m_upKey))
	{
		m_paddlePos.y -= m_speed;
		m_window.setPosition(m_paddlePos);
	}
	if (sf::Keyboard::isKeyPressed(m_downKey))
	{
		m_paddlePos.y += m_speed;
		m_window.setPosition(m_paddlePos);
	}
	
	if (m_paddlePos.y < m_desktop->top) m_paddlePos = prevPos;
	if (m_paddlePos.y + m_paddleSize.y > m_desktop->bottom) m_paddlePos = prevPos;

	// Make always on top
	SetWindowPos(m_window.getSystemHandle(), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
}
