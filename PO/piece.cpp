#include <SFML/Graphics.hpp>

#include "Piece.h"

#include <iostream>
Piece::Piece(const float radius, const Type& type, const Team& team) {
	m_type = type;
	m_team = team;
	m_circle = sf::CircleShape();
	m_circle.setRadius(radius);
	m_circle.setPosition(sf::Vector2f(0.f, 0.f));
	m_circle.setFillColor((bool)m_team ? sf::Color::White : sf::Color::Black);
}

Piece::~Piece() {
}

void Piece::setPosition(const sf::Vector2f& position) {
	m_circle.setPosition(position);
}

Piece::Type Piece::getType() const {
	return m_type;
}

Team Piece::getTeam() const {
	return m_team;
}

void Piece::promote() {
	m_type = King;
	m_circle.setFillColor(m_circle.getFillColor() == sf::Color::Black ? sf::Color::Blue : sf::Color::Red);
}

void Piece::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(m_circle, states);
}