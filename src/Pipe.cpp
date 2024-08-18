#include "Pipe.h"
#include "FlappyBird.h"

Pipe::Pipe(float width, float height) : m_rect(sf::Vector2f(width, height)) {
	setPos(sf::Vector2f(static_cast<float>(game.getWindow().getSize().x), 0.f));
}

Pipe::~Pipe() {}

void Pipe::render() {
	game.getWindow().draw(m_rect);
}

void Pipe::update(sf::Time& deltaTime) {
	m_rect.move(sf::Vector2(getVelocity().x * deltaTime.asSeconds(), 0.f)); // Move the pipe horizontally across screen
}