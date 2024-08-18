#pragma once

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Pipe.h"

class FlappyBird {
public:
	FlappyBird();
	~FlappyBird();

	void processEvents();
	void update(sf::Time deltaTime);
	void render();

	void run();

	sf::RenderWindow& getWindow() { return m_window; }

private:
	sf::RenderWindow m_window{};
	Player m_player{ 20.f };
	Pipe m_pipe{ 40.f, 300.f };
};

extern FlappyBird game; // Declare external game