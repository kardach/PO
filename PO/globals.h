#pragma once

#ifndef GLOBALS_H_
#define GLOBALS_H_

#include <SFML/Graphics.hpp>

using namespace sf;

extern RenderWindow window;

extern float window_heigth;
extern float window_width;

extern RectangleShape background;

extern int board_size;

extern float tile_size;
//extern int tile_count;

extern float x_offset;
extern float y_offset;

extern int piece_count;

extern Font font;
extern Text text;
extern RectangleShape tile;
extern CircleShape circ;
extern Color color;

typedef bool (*f_ptr)(Vector2i, Vector2i);

#endif // !GLOBALS_H_
