#pragma once

#ifndef PIECE_H_
#define PIECE_H_

#include "Board.h"


class Piece : public sf::Transformable, public sf::Drawable {
public:
	enum Type : bool { Man, King };

	enum Team : bool { Black, White };
private:
	Type m_type;

	sf::CircleShape m_circle;
public:
	Piece(const float, const Type, const Team);

	~Piece();;

	void draw(sf::RenderTarget&, sf::RenderStates) const;
};

#endif // PIECE_H_