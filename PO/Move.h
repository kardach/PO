#pragma once

#ifndef MOVE_H_
#define MOVE_H_

class Move {
private:
	sf::Vector2u m_from;
	sf::Vector2u m_to;
public:
	Move(const sf::Vector2u&, const sf::Vector2u&);
	~Move();
	sf::Vector2u from();
	sf::Vector2u to();
};

#endif // MOVE_H_