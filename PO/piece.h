#pragma once

#ifndef PIECE_H_
#define PIECE_H_

#include <SFML/Graphics.hpp>
#include "globals.h"

class Piece {
private:
	bool type;
	int x;
	int y;
	int rgb;
public:
	//bool (*can_move_to)(Vector2i, Vector2i);
	//bool (*can_capture)(Vector2i, Vector2i);
	f_ptr can_move_to;
	f_ptr can_capture;
	Piece();
	//Piece(bool, bool(*can_move_to)(Vector2i, Vector2i), bool (*can_capture)(Vector2i, Vector2i));
	Piece(bool, f_ptr, f_ptr);
	~Piece();
	void set_position(int, int);
	void set_color(bool);
	void draw() const;
};

#endif