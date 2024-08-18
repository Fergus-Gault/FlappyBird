#include "FlappyBird.h"

FlappyBird::FlappyBird()
	: m_window(sf::VideoMode(800, 600), "FlappyBird")
{
	setupFont(); // Setup font on initialisation
}

// Generate unique pipes
void FlappyBird::generatePipes() {
	float windowSizeX{ static_cast<float>(m_window.getSize().x)};
	for (size_t i{ 0 }; i < 5; i++) { // Creates 5 pipes

		Pipe newPipe{ 40.f }; // Create a new pipe with a fixed width.
		newPipe.setPos(sf::Vector2f(newPipe.getPos().x + i*(windowSizeX / 5), newPipe.getPos().y)); // Moves the pipe further off screen to allow it to slowly come in after the one before
		m_pipes.push_back(newPipe); // Add to vector
	}
}

// Process events
void FlappyBird::processEvents() {
	sf::Event event;
	while (m_window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			m_window.close();
		}
		if (event.type == sf::Event::Resized) { // Resize view when user resizes window
			sf::FloatRect visibleArea(0.f, 0.f, static_cast<float>(event.size.width), static_cast<float>(event.size.height));
			m_window.setView(sf::View(visibleArea));
		}
		if (event.type == sf::Event::MouseButtonPressed) {
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				m_player.setVelocity(sf::Vector2f(0.f, -700.f)); // When LMB clicked, player "jumps"
			}
		}
	}
}

// Initialise font
void FlappyBird::setupFont() {
	if (!m_font.loadFromFile("../assets/font.ttf")) { // Load font from file
		throw std::runtime_error("Failed to load font");
	}

	float windowSizeX{ static_cast<float>(m_window.getSize().x) };

	// Set font settings
	m_score.setFont(m_font);
	m_score.setSize(48);
	m_score.setPos(sf::Vector2f(windowSizeX / 2, 50.f));
	m_score.setColor(sf::Color::Red);
	m_score.getText().setString("0");
}

// Stop game
void FlappyBird::stopGame() {
	for (Pipe& pipe : m_pipes) {
		pipe.setVelocity(sf::Vector2f(0.f, 0.f)); // Stop all of the pipes from moving
	}
}

// Update game
void FlappyBird::update(sf::Time deltaTime) {
	m_player.update(deltaTime); // Update player
	for (Pipe& pipe : m_pipes) { // Update each pipe
		pipe.update(deltaTime);
	}
}

// Render game
void FlappyBird::render() {
	m_window.clear();

	m_player.render();
	for (Pipe& pipe : m_pipes) { // Render each pipe
		pipe.render();
	}
	m_score.render();

	m_window.display();
}

// Run game
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