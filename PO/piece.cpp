#include <SFML/Graphics.hpp>

#include "Piece.h"
#include "Team.h"

#include <iostream>
Piece::Piece(const float radius, const Type& type, const Team& team) {
	m_type = type;
	m_team = team;
	m_circle = sf::CircleShape();
	m_circle.setRadius(radius);
	m_circle.setPosition(sf::Vector2f(0.f, 0.f));
	m_circle.setFillColor((bool)m_team ? sf::Color::White : sf::Color::Black);

	m_texture = sf::Texture();
	if (m_team == Team::Black && m_type == Piece::Man) {
		m_texture.loadFromFile("man_black.png");
	}
	else if (m_team == Team::Black && m_type == Piece::King) {
		m_texture.loadFromFile("king_black.png");
	}
	else if (m_team == Team::White && m_type == Piece::Man) {
		m_texture.loadFromFile("man_white.png");
	}
	else if (m_team == Team::White && m_type == Piece::King) {
		m_texture.loadFromFile("king_white.png");
	}
	
	m_sprite = sf::Sprite();
	m_sprite.setTexture(m_texture);
	m_sprite.setScale(sf::Vector2f(2 * radius / 100.f, 2 * radius / 100.f));
	m_sprite.setPosition(sf::Vector2f(0.f, 0.f));
}

Piece::~Piece() {
}

void Piece::setPosition(const sf::Vector2f& position) {
	m_circle.setPosition(position);
	m_sprite.setPosition(position);
}

Piece::Type Piece::getType() const {
	return m_type;
}

Team Piece::getTeam() const {
	return m_team;
}

void Piece::promote() {
	m_type = King;
	if (m_team == Team::Black) {
		m_texture.loadFromFile("king_black.png");
	}
	else {
		m_texture.loadFromFile("king_white.png");
	}
	m_sprite.setTexture(m_texture);
	m_circle.setFillColor(m_circle.getFillColor() == sf::Color::Black ? sf::Color::Blue : sf::Color::Red);
}

void Piece::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	//target.draw(m_circle, states);
	target.draw(m_sprite, states);
}