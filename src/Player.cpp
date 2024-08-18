#include "Player.h"
#include "FlappyBird.h"

// Create a rectangle with the specified radius
Player::Player(float radius) : m_rect(sf::Vector2f(radius, radius)) {
	setPos(sf::Vector2f(200.f, 300.f));
}

// Returns true if player is out of bounds
bool Player::checkBounds() {
	float windowSizeY{ static_cast<float>(game.getWindow().getSize().y) };
	float playerPosY{ m_rect.getPosition().y };

	if (playerPosY > windowSizeY) { // Collision with bottom of screen
		return true; 
	}
	return false;
}

// Render player
void Player::render() {
	game.getWindow().draw(m_rect);
}

// Update player
void Player::update(sf::Time& deltaTime) {
	if (checkBounds()) { // Stop game if player is out of bounds
		game.stopGame();
	}

	game.getScoreText().update(getScore()); // Update score

	setVelocity(sf::Vector2f(0.f, getVelocity().y + getGravity().y)); // Set the new velocity to velocity+gravity

	m_rect.move(sf::Vector2f(0, getVelocity().y * deltaTime.asSeconds())); // Move by the velocity
}