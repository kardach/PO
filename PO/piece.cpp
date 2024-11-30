#include <SFML/Graphics.hpp>

#include "globals.h"
#include "piece.h"

Piece::Piece(bool team, bool type, bool (*can_move_to)(Vector2i, Vector2i), bool (*can_capture)(Vector2i, Vector2i)) {
	this->rgb = team ? 0xFFFFFF : 0x000000;
	this->type = type;
	this->can_move_to = can_move_to;
	this->can_capture = can_capture;
	set_position(2, 2);
}
Piece::~Piece() {
}
void Piece::set_position (int x, int y) {
	this->x = x;
	this->y = y;
}
void Piece::draw() {
	circ.setRadius(tile_size / 2);
	circ.setFillColor(color);
	circ.setPosition(x * tile_size + x_offset, y * tile_size + y_offset);
	window.draw(circ);
}