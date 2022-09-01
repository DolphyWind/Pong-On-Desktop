#pragma once
#include "GameElement.h"
#include "ConfigManager.h"
#include <format>

class ScoreBoard : public GameElement
{
private:
	sf::Font* m_font;
	sf::Text m_scoreText;
	unsigned int m_maxScore;
public:
	ScoreBoard(RECT* desktop, ConfigManager* configManager, sf::Font* font);
	void updateScoreBoard(int scoreLeft, int scoreRight);
	void draw() override;
};

