#include "GameManager.h"

GameManager::GameManager()
{
	bool useAllDisplays = m_configManager.get(UseAllDisplaysKey);
	if (useAllDisplays) GetWindowRect(FindWindowA(NULL, "Program Manager"), &m_desktop);
	else GetWindowRect(GetDesktopWindow(), &m_desktop);
	
	if (!m_font.loadFromFile("OpenSans.ttf"))
	{
		MessageBox(NULL, L"Cannot load \"OpenSans.ttf\". File might be missing or corrupted.", L"Error", MB_OK | MB_ICONERROR);
		std::exit(EXIT_FAILURE);
	}

	m_maxScore = m_configManager.get(WinScoreKey);
	
	m_leftPaddle = new Paddle(&m_desktop, true, &m_configManager);
	m_rightPaddle = new Paddle(&m_desktop, false, &m_configManager);
	m_scoreBoard = new ScoreBoard(&m_desktop, &m_configManager, &m_font);
	m_ball = new Ball(&m_desktop, &m_configManager, m_leftPaddle, m_rightPaddle, m_scoreBoard);

	m_gameElements.push_back(m_leftPaddle);
	m_gameElements.push_back(m_rightPaddle);
	m_gameElements.push_back(m_scoreBoard);
	m_gameElements.push_back(m_ball);
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

void GameManager::update(sf::Time timePerFrame)
{
	if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key)m_configManager.get(QuitKey)))
	{
		m_gameOver = true;
		for (auto& i : m_gameElements)
			i->closeWindow();
	}
	for (auto& i : m_gameElements)
		i->update(timePerFrame);

	if (m_leftPaddle->getScore() >= m_maxScore)
	{
		MessageBox(m_ball->getWindow()->getSystemHandle(), L"Left paddle won!", L"Game Over", MB_OK);
		m_gameOver = true;
		for (auto& i : m_gameElements)
			i->closeWindow();
	}
	if (m_rightPaddle->getScore() >= m_maxScore)
	{
		MessageBox(m_ball->getWindow()->getSystemHandle(), L"Right paddle won!", L"Game Over", MB_OK);
		m_gameOver = true;
		for (auto& i : m_gameElements)
			i->closeWindow();
	}
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
		m_deltaTime += m_deltaClock.restart();
		while (m_deltaTime > m_timePerFrame)
		{
			m_deltaTime -= m_timePerFrame;
			handleEvents();
			update(m_timePerFrame);
		}
		draw();
	}
}
