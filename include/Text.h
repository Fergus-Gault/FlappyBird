#pragma once
#include <SFML/Graphics.hpp>

class Text {
public:
    Text() = default;
    ~Text() = default;
    void render();
    void update(int score);
    sf::Text& getText() { return m_text; }
    void setSize(int size) { m_text.setCharacterSize(size); }
    void setColor(sf::Color color) { m_text.setFillColor(color); }

    void setPos(sf::Vector2f pos) { m_text.setPosition(pos); }
    void setFont(const sf::Font& font);

private:
    sf::Text m_text;
};