#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <Windows.h>

class GameElement
{
protected:
	sf::RenderWindow m_window;
	sf::Color m_clearColor;
	RECT *m_desktop;
public:
	GameElement();
	GameElement(RECT* desktop);
	GameElement(const GameElement&) = default;
	GameElement& operator=(const GameElement&) = default;
	void closeWindow();
	void handleEvents();
	void setClearColor(sf::Color newColor);
	sf::Color getClearColor();
	virtual void update(sf::Time deltaTime);
	virtual void draw();
};
