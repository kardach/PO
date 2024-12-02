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
     
    vector<shared_ptr<Tile>> Tiles;

    Piece** Pieces = new Piece * [piece_count];
    for (int i = 0; i < piece_count; i++) {
        Pieces[i] = new Piece(true, test, test);
    }

    int rows = (board_size * board_size - piece_count * 2) / board_size / 2 - 1;
    int counter = 0;
    
    for (int i = 0; i < board_size; i++) {
        for (int j = 0; j < board_size; j++) {
            //inner tiles
            if (i != 0 && i != board_size - 1 && j != 0 && j != board_size - 1) {
                MainTile temp = MainTile(tile_size, (float)i, (float)j, (i + j) % 2);
                if (((j >= 1 && j < board_size / 2 - rows) || (j >= board_size / 2 + rows && j <= 10)) && (i + j) % 2 == 0) {
                    Pieces[counter]->set_color(j < board_size / 2);
                    temp.place_piece(Pieces[counter++]);
                }
                Tiles.push_back(make_shared<MainTile>(temp));
            }
            //left and right board border
            else if (i != 0 && i != board_size - 1 && (j == 0 || j == board_size - 1)) {
                Tiles.push_back(make_shared<BorderTile>(tile_size, i, j, 'a' + i - 1));
            }
            //top and bottom board border
            else if ((i == 0 || i == board_size - 1) && j != 0 && j != board_size - 1) {
                Tiles.push_back(make_shared<BorderTile>(tile_size, i, j, '0' + j - 1));
            }
            //corners
            else {
                Tiles.push_back(make_shared<CornerTile>(tile_size, i, j));
            }
        }
    }
    
    vector<Vector2i> move;
    
    //game
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed || event.type == Event::KeyReleased && event.key.code == Keyboard::Escape) {
                window.close();
            }
            else if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
                Vector2f cords = Vector2f(Mouse::getPosition(window));
                Vector2i board_cords = Vector2i((int)((cords.x - x_offset) / tile_size), (int)((cords.y - y_offset) / tile_size));
                //check if move is possible
                if (cords.x > x_offset && cords.x < x_offset + tile_size * (board_size - 2) &&
                    cords.y > y_offset && cords.y < y_offset + tile_size * (board_size - 2)) {
                    shared_ptr<MainTile> temp = dynamic_pointer_cast<MainTile>(Tiles.at(board_cords.x * board_size + board_cords.y));
                    if (temp != nullptr) {
                        if (move.size() == 0 && temp->has_piece() || move.size() == 1 && !(temp->has_piece())) {
                            move.push_back(Vector2i(board_cords.x, board_cords.y));
                        }
                    }                    
                }
                //move piece
                if (move.size() == 2) {
                    Vector2i start = move.at(0);
                    Vector2i end = move.at(1);
                    Piece* piece = dynamic_pointer_cast<MainTile>(Tiles.at(start.x * board_size + start.y))->remove_piece();
                    dynamic_pointer_cast<MainTile>(Tiles.at(end.x * board_size + end.y))->place_piece(piece);
                    move.clear();
                }
            }
        }
        //drawing
        window.clear();
        window.draw(background);
        for (int i = 0; i < board_size; i++) {
            for (int j = 0; j < board_size; j++) {
                Tiles.at(i * board_size + j)->draw();
            }
        }
        window.display();
    }

    return 0;
}