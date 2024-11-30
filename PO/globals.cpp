#include "globals.h"

RenderWindow window(VideoMode(800, 600), "Draughts", Style::Close | Style::Titlebar);

float window_heigth = window.getSize().y;
float window_width = window.getSize().x;

RectangleShape background = RectangleShape(Vector2f(window_width, window_heigth));

int board_size = 10 + 2;
float tile_size = ((window_heigth < window_width) ? window_heigth : window_width) / board_size;
int tile_count = board_size * board_size;

float x_offset = (window_heigth < window_width) ? (window_width - board_size * tile_size) / 2 : 0;
float y_offset = (window_heigth < window_width) ? 0 : (window_width - board_size * tile_size) / 2;

Font font;
Text text;
RectangleShape tile;
CircleShape circ;
Color color;