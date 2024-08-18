#include "Pipe.h"
#include "FlappyBird.h"
#include <random>
#include <iostream>

Pipe::Pipe(float width, float height) : m_rect(sf::Vector2f(width, height)) {
	setPos(sf::Vector2f(static_cast<float>(game.getWindow().getSize().x), randomOffset()));
}

Pipe::~Pipe() {}

float Pipe::randomOffset() {
	srand(static_cast<unsigned int>(time(nullptr)));
	return static_cast<float>(rand() % 100);
}

bool Pipe::checkIfOnLeft() {
	if (m_rect.getPosition().x < -m_rect.getSize().x) { // Pipe has passed the left side of screen if its x position is less than its width
		return true;
	}
	return false;
}

bool Pipe::checkCollision() { // Check if the player collides with a pipe 
	if (m_rect.getGlobalBounds().intersects(game.getPlayer().getRect().getGlobalBounds())) {
		return true;
	}
	return false;
}

void Pipe::render() {
	game.getWindow().draw(m_rect);
}

void Pipe::update(sf::Time& deltaTime) {
	if (checkIfOnLeft()) {
		setPos(sf::Vector2f(static_cast<float>(game.getWindow().getSize().x), randomOffset())); // Move back to right hand side if out of view
	}
	checkCollision();
	m_rect.move(sf::Vector2(getVelocity().x * deltaTime.asSeconds(), 0.f)); // Move the pipe horizontally across screen
}