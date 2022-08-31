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
	m_desktop = NULL;
}

GameElement::GameElement(RECT* desktop)
{
	m_clearColor = sf::Color::Black;
	m_desktop = desktop;
}


void GameElement::update(sf::Time deltaTime)
{

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
