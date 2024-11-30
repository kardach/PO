#include <SFML/Graphics.hpp>
#include <iostream>

#include "globals.h"
#include "piece.h"
#include "tiles.h"

using namespace sf;
using namespace std;

bool test(Vector2i from, Vector2i to) {
    return true;
}

int main() {
    color.r = color.g = color.b = 128;
    background.setPosition(0, 0);
    background.setFillColor(color);

    font.loadFromFile("ariblk.ttf");

    color.g = color.b = 0;
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(color);

    Tile*** TILES = new Tile * *[board_size];
    for (int i = 0; i < board_size; i++) {
        TILES[i] = new Tile * [board_size];
    }

    for (int i = 0; i < board_size; i++) {
        for (int j = 0; j < board_size; j++) {
            //inner tiles
            if (i != 0 && i != board_size - 1 && j != 0 && j != board_size - 1) {
                TILES[i][j] = new MainTile(tile_size, i, j, (i + j) % 2);
                
            }
            //left and right board border
            else if (i != 0 && i != board_size - 1 && (j == 0 || j == board_size - 1)) {
                TILES[i][j] = new BorderTile(tile_size, i, j, 'a' + i - 1);
            }
            //top and bottom board border
            else if ((i == 0 || i == board_size - 1) && j != 0 && j != board_size - 1) {
                TILES[i][j] = new BorderTile(tile_size, i, j, '0' + j - 1);
            }
            //corners
            else {
                TILES[i][j] = new CornerTile(tile_size, i, j);
            }
        }
    }

    //game
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }
        window.clear();
        window.draw(background);
        for (int i = 0; i < board_size; i++) {
            for (int j = 0; j < board_size; j++) {
                TILES[i][j]->draw();
            }
        }
        window.display();
    }

    return 0;
}