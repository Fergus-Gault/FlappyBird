#pragma once

#include <SFML/Graphics.hpp>

class Player {
public:
	Player(float radius);
	~Player();

	void update(sf::Time& deltaTime);
	void render();

	void setGravity(sf::Vector2f& gravity) { m_gravity = gravity; }
	sf::Vector2f getGravity() { return m_gravity; }

	void setVelocity(sf::Vector2f velocity) { m_velocity = velocity; }
	sf::Vector2f getVelocity() { return m_velocity; }

	sf::RectangleShape getRect() { return m_rect; }

	void setPos(sf::Vector2f pos) { m_rect.setPosition(pos); }

	bool checkBounds();

private:
	sf::RectangleShape m_rect{};
	sf::Vector2f m_gravity{0.f, .5f};
	sf::Vector2f m_velocity{};
};