#include <SFML/Graphics.hpp>

#include "Tile.h"

Tile::Tile(const float size, const sf::Vector2f& position, const sf::Color& color) {
    m_rectangle = sf::RectangleShape(sf::Vector2f(size, size));
    m_rectangle.setPosition(position);
    m_rectangle.setFillColor(color);
}

Tile::~Tile() {
}

void Tile::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(m_rectangle, states);
}