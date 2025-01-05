#include <SFML/Graphics.hpp>

#include "Move.h"

Move::Move(const sf::Vector2u& from, const sf::Vector2u& to) {
	m_from = from;
	m_to = to;
}

Move::~Move() {
}

sf::Vector2u Move::from() {
	return m_from;
}

sf::Vector2u Move::to() {
	return m_to;
}