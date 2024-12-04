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
extern RectangleShape button;

typedef bool (*b_fptr_2V)(Vector2i, Vector2i);
typedef int (*i_fptr_i)(int);

#endif // !GLOBALS_H_
