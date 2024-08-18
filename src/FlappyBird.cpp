#include "FlappyBird.h"

FlappyBird::FlappyBird()
	: m_window(sf::VideoMode(800, 600), "FlappyBird")
{
	setupFont();
}

FlappyBird::~FlappyBird() {}

void FlappyBird::generatePipes() {
	for (size_t i{ 0 }; i < 5; i++) {
		Pipe newPipe{ 40.f };
		newPipe.setPos(sf::Vector2f(newPipe.getPos().x + i*(m_window.getSize().x / 5), newPipe.getPos().y));
		m_pipes.push_back(newPipe);
	}
}

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
				m_player.setVelocity(sf::Vector2f(0.f, -700.f));
			}
		}
	}
}

void FlappyBird::setupFont() {
	if (!m_font.loadFromFile("../assets/font.ttf")) {
		throw std::runtime_error("Failed to load font");
	}

	m_score.setFont(m_font);
	m_score.setSize(48);
	m_score.setPos(sf::Vector2f(m_window.getSize().x / 2, 50.f));
	m_score.setColor(sf::Color::Red);
	m_score.getText().setString("0");
}

void FlappyBird::stopGame() {
	for (Pipe& pipe : m_pipes) {
		pipe.setVelocity(sf::Vector2f(0.f, 0.f));
	}
}

void FlappyBird::update(sf::Time deltaTime) {
	m_player.update(deltaTime);
	for (Pipe& pipe : m_pipes) {
		pipe.update(deltaTime);
	}
}

void FlappyBird::render() {
	m_window.clear();

	m_player.render();
	for (Pipe& pipe : m_pipes) {
		pipe.render();
	}
	m_score.render();

	m_window.display();
}

void FlappyBird::run() {

	generatePipes();
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