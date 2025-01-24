#include <SFML/Graphics.hpp>

#include "Tile.h"
#include "CornerTile.h"

CornerTile::CornerTile(const float size, const sf::Vector2f& position)
    : Tile(size, position, sf::Color(222, 184, 135)) {
}

CornerTile::~CornerTile() {
}

void CornerTile::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(m_rectangle, states);
}