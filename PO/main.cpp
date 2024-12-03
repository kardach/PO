#include <SFML/Graphics.hpp>
#include <iostream>

#include "globals.h"
#include "piece.h"
#include "tiles.h"

using namespace sf;
using namespace std;

class Move {
public:
    Vector2i from;
    Vector2i to;
    Move* next;
    Move(Vector2i, Vector2i);
    ~Move();
};
Move::Move(Vector2i from, Vector2i to) {
    this->from = Vector2i(from);
    this->to = Vector2i(to);
    this->next = nullptr;
    cout << "FROM: " << from.x << " " << from.y << endl;
}
Move::~Move() {
}

bool test(Vector2i from, Vector2i to) {
    cout << "TEST CALLED" << endl;
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
                Tiles.push_back(make_shared<BorderTile>(tile_size, (float)i, (float)j, 'a' + i - 1));
            }
            //top and bottom board border
            else if ((i == 0 || i == board_size - 1) && j != 0 && j != board_size - 1) {
                Tiles.push_back(make_shared<BorderTile>(tile_size, (float)i, (float)j, '0' + j - 1));
            }
            //corners
            else {
                Tiles.push_back(make_shared<CornerTile>(tile_size, (float)i, j));
            }
        }
    }
    
    vector<Move> moves;
    bool flag = false;
    Vector2i temp = Vector2i();
    f_ptr function_pointer = nullptr;
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
                shared_ptr<MainTile> start_tile = nullptr;
                cout << "CORDS: " << board_cords.x << " " << board_cords.y << endl;
                //check if move is possible
                if (cords.x > x_offset + tile_size && cords.x < x_offset + tile_size * (board_size - 1) &&
                    cords.y > y_offset + tile_size && cords.y < y_offset + tile_size * (board_size - 1)) {
                    shared_ptr<MainTile> selected_tile = dynamic_pointer_cast<MainTile>(Tiles.at((size_t)board_cords.x * board_size + board_cords.y));
                    if (selected_tile != nullptr) {
                        if (moves.size() == 0 && selected_tile->has_piece() && flag == false) {
                            //cout << "FIRST: " << board_cords.x << " " << board_cords.y << endl;
                            flag = true;
                            temp = Vector2i(board_cords);
                            function_pointer = selected_tile->get_piece_moveset();
                        }
                        else if (moves.size() == 0 && flag == true) {
                            //cout << "SECOND: " << board_cords.x << " " << board_cords.y << endl;
                            if (function_pointer != nullptr && function_pointer(temp, board_cords)) {
                                moves.push_back(Move(temp, board_cords));
                                flag = false;
                                selected_tile = nullptr;
                            }
                        }
                    }                    
                }
                //move piece
                if (moves.size() == 1) {
                    Vector2i start = moves.at(0).from;
                    Vector2i end = moves.at(0).to;
                    //cout << "START: " << start.x << " " << start.y << endl;
                    //cout << "END: " << end.x << " " << end.y << endl;
                    Piece* piece = dynamic_pointer_cast<MainTile>(Tiles.at((size_t)start.x * board_size + start.y))->remove_piece();
                    dynamic_pointer_cast<MainTile>(Tiles.at((size_t)end.x * board_size + end.y))->place_piece(piece);
                    moves.clear();
                    temp = Vector2i();
                    function_pointer = nullptr;
                }
            }
        }
        //drawing
        window.clear();
        window.draw(background);
        for (size_t i = 0; i < board_size; i++) {
            for (size_t j = 0; j < board_size; j++) {
                Tiles.at(i * board_size + j)->draw();
            }
        }
        window.display();
    }

    return 0;
}