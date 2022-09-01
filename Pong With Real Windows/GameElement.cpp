#include "GameElement.h"

void GameElement::closeWindow()
{
	m_window.close();
}



void GameElement::handleEvents()
{
	sf::Event e;
	while (m_window.pollEvent(e))
	{
		switch (e.type)
		{
		case sf::Event::Closed:
			m_window.close();
			break;
		default:
			break;
		}
	}
}


GameElement::GameElement()
{
	m_desktop = nullptr;
	m_configManager = nullptr;
}

GameElement::GameElement(RECT* desktop, ConfigManager* configManager)
{
	m_clearColor = sf::Color::Black;
	m_desktop = desktop;
	m_configManager = configManager;
}


void GameElement::update(sf::Time deltaTime)
{
	m_time += deltaTime.asSeconds();
}

void GameElement::draw()
{
	m_window.clear(m_clearColor);

	m_window.display();
}

void GameElement::setClearColor(sf::Color newColor)
{
	m_clearColor = newColor;
}

sf::Color GameElement::getClearColor()
{
	return m_clearColor;
}

void GameElement::setPosition(sf::Vector2i pos)
{
	m_window.setPosition(pos);
}

sf::Vector2i GameElement::getPosition()
{
	return m_window.getPosition();
}

void GameElement::setSize(sf::Vector2u size)
{
	m_window.setSize(size);
}

sf::Vector2u GameElement::getSize()
{
	return m_window.getSize();
}

void GameElement::resetTime()
{
	m_time = 0;
}
