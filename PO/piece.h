#pragma once

#ifndef PIECE_H_
#define PIECE_H_

#include <SFML/Graphics.hpp>
#include "globals.h"

class Piece {
public:
	bool type;
	int x;
	int y;
	int rgb;
	bool (*can_move_to)(Vector2i, Vector2i);
	bool (*can_capture)(Vector2i, Vector2i);

	Piece(bool, bool, bool(*can_move_to)(Vector2i, Vector2i), bool (*can_capture)(Vector2i, Vector2i));
	~Piece();
	void set_position(int, int);
	void draw();
};

#endif