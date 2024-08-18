#include "Pipe.h"
#include "FlappyBird.h"
#include <random>

Pipe::Pipe(float width) 
{
	generateRandomPipe(width); // Create a random pipe on initialisation
}

void Pipe::generateRandomPipe(float width) {

	m_upperRect.setSize(sf::Vector2f(width, randomOffset())); // Give the upper pipe a random height
	m_lowerRect.setSize(sf::Vector2f(width, game.getWindowY() - (m_upperRect.getSize().y + m_gap))); // Give the lower pipe a height that fills in the remaining space with a gap

	setPos(sf::Vector2f(game.getWindowX(), 0.f)); // Set position of both pipes
}

// Generate a random offset
float Pipe::randomOffset() {
	// Create a random device to seed the generator
	std::random_device rd;

	std::mt19937 gen(rd());

	// Define a uniform integer distribution in the range [0, 300]
	std::uniform_int_distribution<> dis(0, 300);

	return static_cast<float>(dis(gen));
}

// Check if pipe has passed left side of screen
bool Pipe::checkIfOnLeft() {
	if (m_upperRect.getPosition().x < -m_upperRect.getSize().x) { // Pipe has passed the left side of screen if its x position is less than its width
		m_playerPassed = false;
		return true;
	}
	return false;
}

// Set position of pipe
void Pipe::setPos(sf::Vector2f pos) {
	float upperRectY{ m_upperRect.getSize().y };
	m_upperRect.setPosition(pos); 
	m_lowerRect.setPosition(sf::Vector2f(m_upperRect.getPosition().x, upperRectY + m_gap)); // Set lower pipe to be directly below upper pipe with a gap
}

// Check if the player collides with a pipe 
bool Pipe::checkCollision() { 
	sf::FloatRect playerRect{ game.getPlayer().getRect().getGlobalBounds() };
	sf::FloatRect upperPipeRect{ m_upperRect.getGlobalBounds() };
	sf::FloatRect lowerPipeRect{ m_lowerRect.getGlobalBounds() };

	if (upperPipeRect.intersects(playerRect) || lowerPipeRect.intersects(playerRect)) { // If either pipe intersects with player
		return true;
	}
	return false;
}

// Check if the player has passed a pipe
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

// Render pipe
void Pipe::render() {
	game.getWindow().draw(m_upperRect);
	game.getWindow().draw(m_lowerRect);
}


// Update pipe
void Pipe::update(sf::Time& deltaTime) {
	if (checkIfOnLeft()) { // If pipe has left the screen, change its properties and move it to the right
		generateRandomPipe(m_upperRect.getSize().x);
	}
	if (checkCollision()) { // Stop game if player collides with a pipe
		game.stopGame();
	}
	if (checkPlayerPass()) {
		game.getPlayer().setScore(game.getPlayer().getScore() + 1); // Increase score
	}

	// Move the pipe horizontally across screen
	m_upperRect.move(sf::Vector2(getVelocity().x * deltaTime.asSeconds(), 0.f)); 
	m_lowerRect.move(sf::Vector2(getVelocity().x * deltaTime.asSeconds(), 0.f)); 
}