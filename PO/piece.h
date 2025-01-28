#pragma once

#ifndef PIECE_H_
#define PIECE_H_

enum class Team : bool;

class Piece : public sf::Drawable {
public:
	enum Type : bool { Man, King };
private:
	Type m_type;

	Team m_team;

	sf::CircleShape m_circle;

	sf::Texture m_texture;

	sf::Sprite m_sprite;
public:
	Piece(const float, const Type&, const Team&);

	~Piece();

	void setPosition(const sf::Vector2f&);

	Type getType() const;

	Team getTeam() const;

	void promote();

	void draw(sf::RenderTarget&, sf::RenderStates) const;
};

#endif // PIECE_H_