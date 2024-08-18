#pragma once
#include <SFML/Graphics.hpp>

class Pipe {
public:
	Pipe(float width);
	~Pipe() = default;

	void update(sf::Time& deltaTime);
	void render();

	void setVelocity(sf::Vector2f velocity) { m_velocity = velocity; }
	sf::Vector2f& getVelocity() { return m_velocity; }


	void setPos(sf::Vector2f pos);
	sf::Vector2f getPos() { return m_upperRect.getPosition(); }

	bool checkIfOnLeft();
	bool checkCollision();
	bool checkPlayerPass();

	static float randomOffset();

	void generateRandomPipe(float width);

private:
	sf::RectangleShape m_upperRect{};
	sf::RectangleShape m_lowerRect{};
	float m_gap{150.f};
	sf::Vector2f m_velocity{-100.f, 0.f};
	float m_offset{};
	bool m_playerPassed{};
};


