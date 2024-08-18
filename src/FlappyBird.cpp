#include "FlappyBird.h"

FlappyBird::FlappyBird()
	: m_window(sf::VideoMode(800, 600), "FlappyBird")
{}

FlappyBird::~FlappyBird() {}

void FlappyBird::processEvents() {
	sf::Event event;
	while (m_window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			m_window.close();
		}
		if (event.type == sf::Event::Resized) {
			sf::FloatRect visibleArea(0.f, 0.f, static_cast<float>(event.size.width), static_cast<float>(event.size.height));
			m_window.setView(sf::View(visibleArea));
		}
		if (event.type == sf::Event::MouseButtonPressed) {
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				m_player.setVelocity(sf::Vector2f(0.f, -800.f));
			}
		}
	}
}

void FlappyBird::update(sf::Time deltaTime) {
	m_player.update(deltaTime);
	m_pipe.update(deltaTime);
}

void FlappyBird::render() {
	m_window.clear();

	m_player.render();
	m_pipe.render();

	m_window.display();
}

void FlappyBird::run() {

	sf::Clock clock;
	while (m_window.isOpen()) {
		processEvents();
		update(clock.restart());
		render();
	}
}


FlappyBird game{};
int main() {
	game.run();


	return EXIT_SUCCESS;
}