#include "Pipe.h"
#include "FlappyBird.h"
#include <random>

Pipe::Pipe(float width) 
{
	generateRandomPipe(width);
}

Pipe::~Pipe() {}

void Pipe::generateRandomPipe(float width) {
	m_upperRect.setSize(sf::Vector2f(width, randomOffset()));
	m_lowerRect.setSize(sf::Vector2f(width, game.getWindow().getSize().y - (m_upperRect.getSize().y + m_gap)));

	m_upperRect.setPosition(sf::Vector2f(game.getWindow().getSize().x, 0.f));
	m_lowerRect.setPosition(sf::Vector2f(m_upperRect.getPosition().x, m_upperRect.getSize().y + m_gap));
}

float Pipe::randomOffset() {
	// Create a random device to seed the generator
	std::random_device rd;

	// Create a Mersenne Twister random number generator seeded with rd
	std::mt19937 gen(rd());

	// Define a uniform integer distribution in the range [0, 300]
	std::uniform_int_distribution<> dis(0, 300);

	// Generate and return the random number
	return static_cast<float>(dis(gen));
}

bool Pipe::checkIfOnLeft() {
	if (m_upperRect.getPosition().x < -m_upperRect.getSize().x) { // Pipe has passed the left side of screen if its x position is less than its width
		m_playerPassed = false;
		return true;
	}
	return false;
}

bool Pipe::checkCollision() { // Check if the player collides with a pipe 
	if (m_upperRect.getGlobalBounds().intersects(game.getPlayer().getRect().getGlobalBounds())) {
		return true;
	}
	else if (m_lowerRect.getGlobalBounds().intersects(game.getPlayer().getRect().getGlobalBounds())) {
		return true;
	}
	return false;
}

bool Pipe::checkPlayerPass() {

	// Get player and pipe positions
	int playerPosition = static_cast<int>(game.getPlayer().getRect().getPosition().x);
	int pipePosition = static_cast<int>(m_upperRect.getPosition().x);

	// Check if the player has passed the pipe and it hasn't been passed before
	if (!m_playerPassed && playerPosition == pipePosition) {
		m_playerPassed = true;
		return true;
	}
	return false;
}

void Pipe::render() {
	game.getWindow().draw(m_upperRect);
	game.getWindow().draw(m_lowerRect);
}

void Pipe::update(sf::Time& deltaTime) {
	if (checkIfOnLeft()) {
		generateRandomPipe(m_upperRect.getSize().x);
	}
	if (checkCollision()) {
		game.stopGame();
	}
	if (checkPlayerPass()) {
		game.getPlayer().setScore(game.getPlayer().getScore() + 1); // Increase score
	}
	m_upperRect.move(sf::Vector2(getVelocity().x * deltaTime.asSeconds(), 0.f)); // Move the pipe horizontally across screen
	m_lowerRect.move(sf::Vector2(getVelocity().x * deltaTime.asSeconds(), 0.f)); // Move the pipe horizontally across screen
}