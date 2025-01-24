#pragma once

#ifndef MOVE_H_
#define MOVE_H_

class Move {
public:
	enum Type : bool { Jump, Capture };
private:
	sf::Vector2u m_from;
	sf::Vector2u m_to;
	Type m_type;
public:
	Move(const sf::Vector2u&, const sf::Vector2u&, const Type& m_type);
	~Move();
	sf::Vector2u from();
	sf::Vector2u to();
	Type type();
};

#endif // MOVE_H_