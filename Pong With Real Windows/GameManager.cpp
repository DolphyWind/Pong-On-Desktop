#include "GameManager.h"

GameManager::GameManager()
{
	bool useAllDisplays = m_configManager.get(UseAllDisplaysKey);
	if (useAllDisplays) GetWindowRect(FindWindowA(NULL, "Program Manager"), &m_desktop);
	else GetWindowRect(GetDesktopWindow(), &m_desktop);
	m_gameElements.push_back(new Paddle(&m_desktop, true, &m_configManager));
	m_gameElements.push_back(new Paddle(&m_desktop, false, &m_configManager));
	m_gameElements.push_back(new Ball(&m_desktop, &m_configManager, (Paddle*)m_gameElements[0], (Paddle*)m_gameElements[1]));
}

GameManager::~GameManager()
{
	for (int i = 0; i < m_gameElements.size(); i++)
		delete m_gameElements[i];
}

void GameManager::handleEvents()
{
	for (auto& i : m_gameElements)
		i->handleEvents();
}

void GameManager::update()
{
	m_deltaTime = m_deltaClock.restart();
	if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key)m_configManager.get(QuitKey)))
	{
		m_gameOver = true;
		for (auto& i : m_gameElements)
			i->closeWindow();
	}
	for (auto& i : m_gameElements)
		i->update(m_deltaTime);
}

void GameManager::draw()
{
	for (auto& i : m_gameElements)
		i->draw();
}

void GameManager::mainLoop()
{
	while (!m_gameOver)
	{
		handleEvents();
		update();
		draw();
	}
}
