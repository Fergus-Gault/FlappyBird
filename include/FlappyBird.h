#pragma once

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Pipe.h"
#include "Text.h"
#include <vector>

class FlappyBird {
public:
	FlappyBird();
	~FlappyBird();

	void processEvents();
	void update(sf::Time deltaTime);
	void render();

	void run();

	sf::RenderWindow& getWindow() { return m_window; }

	Player& getPlayer() { return m_player; }

	void generatePipes();

	void stopGame();

	void setupFont();

	Text& getScoreText() { return m_score; }

private:
	sf::RenderWindow m_window{};
	Player m_player{ 20.f };
	std::vector<Pipe> m_pipes{};
	Text m_score{};
	sf::Font m_font;
};

extern FlappyBird game; // Declare external game