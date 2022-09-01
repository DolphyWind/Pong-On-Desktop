#include "ScoreBoard.h"

ScoreBoard::ScoreBoard(RECT* desktop, ConfigManager* configManager, sf::Font* font) : GameElement(desktop, configManager)
{
	m_font = font;
	m_maxScore = configManager->get(WinScoreKey);

	m_scoreText.setFont(*m_font);
	m_scoreText.setString(std::format("{}-{}", m_maxScore, m_maxScore));
	m_scoreText.setCharacterSize(30);

	sf::FloatRect textRect = m_scoreText.getGlobalBounds();
	float textWidth = textRect.width + textRect.left;
	float textHeight = textRect.height + textRect.top;

	m_window.create(sf::VideoMode(textWidth, textHeight), "ScoreBoard", sf::Style::None);
	m_window.setPosition(sf::Vector2i(
		(desktop->right - desktop->left) / 2 - textWidth / 2,
		desktop->top
	));

	updateScoreBoard(0, 0);

	m_clearColor = sf::Color::Black;
}

void ScoreBoard::updateScoreBoard(int scoreLeft, int scoreRight)
{
	m_scoreText.setString(std::format("{}-{}", scoreLeft, scoreRight));

	sf::FloatRect textRect = m_scoreText.getLocalBounds();
	m_scoreText.setOrigin(
		textRect.left + textRect.width / 2,
		textRect.top + textRect.height / 2
	);

	m_scoreText.setPosition(
		m_window.getSize().x / 2,
		m_window.getSize().y / 2
	);
}

void ScoreBoard::draw()
{
	m_window.clear();

	m_window.draw(m_scoreText);

	m_window.display();
}
