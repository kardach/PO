#include <SFML/Graphics.hpp>

#include "Board.h"
#include "Piece.h"

Piece::Piece(const float radius, const Type type, const Team team) {
	m_type = type;
	m_circle = sf::CircleShape();
	m_circle.setRadius(radius);
	m_circle.setPosition(sf::Vector2f(0.f, 0.f));
	m_circle.setFillColor(team ? sf::Color::White : sf::Color::Black);
}

Piece::~Piece() {
}


void Piece::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	target.draw(m_circle, states);
}