#pragma once
#include <SFML/Graphics.hpp>

class Pipe {
public:
	Pipe(float width, float height);
	~Pipe();

	void update(sf::Time& deltaTime);
	void render();

	void setVelocity(sf::Vector2f velocity) { m_velocity = velocity; }
	sf::Vector2f getVelocity() { return m_velocity; }

	sf::RectangleShape getRect() { return m_rect; }

	void setPos(sf::Vector2f pos) { m_rect.setPosition(pos); }

private:
	sf::RectangleShape m_rect;
	sf::Vector2f m_velocity{-100.f, 0.f};

};