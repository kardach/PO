#include <SFML/Graphics.hpp>

#include "globals.h"
#include "piece.h"
#include "tiles.h"

Tile::Tile(float size, float x, float y, int rgb) {
    this->size = size;
    this->x = x;
    this->y = y;
    this->rgb = rgb;
}
Tile::~Tile() {
}
void Tile::draw() {
    color.r = rgb >> 16 & 0xFF;
    color.g = rgb >> 8 & 0xFF;
    color.b = rgb & 0xFF;

    tile.setSize(Vector2f(tile_size, tile_size));
    tile.setPosition(x * tile_size + x_offset, y * tile_size + y_offset);
    tile.setFillColor(color);
    window.draw(tile);
}
CornerTile::CornerTile(float size, float x, float y) : Tile(size, x, y, 0xDEB887) {
}
CornerTile::~CornerTile() {
}
void CornerTile::draw() {
    Tile::draw();
}
BorderTile::BorderTile(float size, float x, float y, char sign) : Tile(size, x, y, 0xDEB887) {
    this->sign = sign;
}
BorderTile::~BorderTile() {
}
void BorderTile::draw() {
    Tile::draw();

    text.setString(sign);
    text.setPosition(x * tile_size + x_offset + (tile_size - text.getLocalBounds().width) / 2, y * tile_size + y_offset + (tile_size - text.getLocalBounds().height) / 2);
    window.draw(text);
}
MainTile::MainTile(float size, float x, float y, bool team) : Tile(size, x, y, team ? 0xFFE4C4 : 0x8B4513) {
    this->piece = nullptr;
}
MainTile::~MainTile() {
}
void MainTile::draw() {
    Tile::draw();

    if (piece != nullptr) {
        piece->draw();
    }
}
void MainTile::place_piece(Piece* piece) {
    this->piece = piece;
    this->piece->set_position((int)this->x, (int)this->y);
}
bool MainTile::has_piece() {
    return this->piece != nullptr;
}
Piece* MainTile::remove_piece() {
    Piece* temp = this->piece;
    this->piece = nullptr;
    return temp;
}
f_ptr MainTile::get_piece_moveset() {
    return this->piece->can_move_to;
}