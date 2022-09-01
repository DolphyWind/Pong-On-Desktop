#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <Windows.h>
#include "ConfigManager.h"

class GameElement
{
protected:
	sf::RenderWindow m_window;
	sf::Color m_clearColor;
	RECT *m_desktop;
	ConfigManager* m_configManager;
	float m_time = 0;
public:
	GameElement();
	GameElement(RECT* desktop, ConfigManager* configManager);
	GameElement(const GameElement&) = default;
	GameElement& operator=(const GameElement&) = default;
	void closeWindow();
	void handleEvents();
	void setClearColor(sf::Color newColor);
	sf::Color getClearColor();
	virtual void update(sf::Time deltaTime);
	virtual void draw();
	void setPosition(sf::Vector2i pos);
	sf::Vector2i getPosition();
	void setSize(sf::Vector2u size);
	sf::Vector2u getSize();
	void resetTime();
	sf::RenderWindow* getWindow();
};
