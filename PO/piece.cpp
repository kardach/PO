#include <SFML/Graphics.hpp>

#include "globals.h"
#include "piece.h"
Piece::Piece() {
	this->rgb = 0;
	this->type = 0;
	this->can_move_to = nullptr;
	this->can_capture = nullptr;
	this->x = 0;
	this->y = 0;

}
/*Piece::Piece(bool type, bool (*can_move_to)(Vector2i, Vector2i), bool (*can_capture)(Vector2i, Vector2i)) {
	this->type = type;
	this->can_move_to = can_move_to;
	this->can_capture = can_capture;
	set_position(0, 0);
}*/
Piece::Piece(bool type, b_fptr_2V can_move_to, b_fptr_2V can_capture) {
	this->type = type;
	this->can_move_to = can_move_to;
	this->can_capture = can_capture;
	set_position(0, 0);
}
Piece::~Piece() {
}
void Piece::set_position(int x, int y) {
	this->x = x;
	this->y = y;
}
void Piece::set_color(bool team) {
	this->rgb = team ? 0xFFFFFF : 0x000000;
}
void Piece::draw() const {
	color.r = rgb >> 16 & 0xFF;
	color.g = rgb >> 8 & 0xFF;
	color.b = rgb & 0xFF;

	circ.setRadius(tile_size / 2);
	circ.setFillColor(color);
	circ.setPosition(x * tile_size + x_offset, y * tile_size + y_offset);
	window.draw(circ);
}