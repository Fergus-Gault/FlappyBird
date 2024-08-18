#include "Player.h"
#include "FlappyBird.h"

// Create a rectangle with the specified radius
Player::Player(float radius) : m_rect(sf::Vector2f(radius, radius)) {
	setPos(sf::Vector2f(200.f, 300.f));
}

Player::~Player() {};


bool Player::checkBounds() {
	if (m_rect.getPosition().y > game.getWindow().getSize().y) { // Collision with bottom of screen
		return true; 
	}
	return false;
}


void Player::render() {
	game.getWindow().draw(m_rect);
}


void Player::update(sf::Time& deltaTime) {
	if (checkBounds()) {
		game.stopGame();
	}

	game.getScoreText().update(getScore()); // Update score

	setVelocity(sf::Vector2f(0.f, getVelocity().y + getGravity().y)); // Set the new velocity to velocity+gravity

	m_rect.move(sf::Vector2f(0, getVelocity().y * deltaTime.asSeconds())); // Move by the velocity
}