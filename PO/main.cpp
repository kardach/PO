#include <SFML/Graphics.hpp>
#include <iostream>

#include "RoundedRectangle.h"
#include "Settings.h"
#include "Button.h"
#include "Board.h"
/*std::vector<std::shared_ptr<Tile>> create_board(Piece** Pieces) {
    int rows = (board_size * board_size - piece_count * 2) / board_size / 2 - 1;
    int counter = 0;
    vector<shared_ptr<Tile>> Tiles;
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
    return Tiles;
}*/

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Draughts", sf::Style::Close | sf::Style::Titlebar);

    Settings settings(window.getSize());
    settings.setBoardSize(10);
    settings.setPieceCount(24);

    sf::RectangleShape background(sf::Vector2f(window.getSize()));
    background.setPosition(0.f, 0.f);
    background.setFillColor(sf::Color(128, 128, 128));

    sf::Font font;
    font.loadFromFile("ariblk.ttf");
    
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color(128, 0, 0));

    Board board(window.getSize(), settings);

    bool game_started = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
            else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                if (!game_started) {
                    sf::Vector2f cords = sf::Vector2f(sf::Mouse::getPosition(window));
                }
                else {

                }
            }
        }
        window.clear();
        window.draw(background);
        window.draw(board);
        window.display();
    }

    /*Piece** Pieces = new Piece * [piece_count];
    for (int i = 0; i < piece_count; i++) {
        Pieces[i] = new Piece(true, test, test);
    }

    vector<shared_ptr<Tile>> Tiles;
    
    vector<Move> moves;
    bool click_flag = false; //false - select tile to move from, true - select tile to move to
    Vector2i temp = Vector2i();
    b_fptr_2V function_pointer = nullptr;

    int game_started = 0;
    Button start(100.0f, 100.0f, 0.0f, 0.0f, 0xFF0000, start_game);
    Radio board_radio(100.0f, 300.0f, 0.0f, 100.0f, 0x00FF00, 3, set_board_size);
    Checkbox rule(100.0f, 100.0f, 0.0f, 200.0f, 0x0000FF);

    X x;
    x.setSize(Vector2f(50.0f, 50.0f));
    x.setPosition(Vector2f(0.0f, 300.0f));
    x.setFillColor(Color::Yellow);
    //game
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed || event.type == Event::KeyReleased && event.key.code == Keyboard::Escape) {
                window.close();
            }
            else if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
                if (game_started == 1) {
                    
                    Vector2f cords = Vector2f(Mouse::getPosition(window));
                    Vector2i board_cords = Vector2i((int)((cords.x - x_offset) / tile_size), (int)((cords.y - y_offset) / tile_size));
                    shared_ptr<MainTile> start_tile = nullptr;
                    
                    cout << "CORDS: " << board_cords.x << " " << board_cords.y << endl;
                    //check if move is possible
                    if (cords.x > x_offset + tile_size && cords.x < x_offset + tile_size * (board_size - 1) &&
                        cords.y > y_offset + tile_size && cords.y < y_offset + tile_size * (board_size - 1)) {
                        
                        shared_ptr<MainTile> selected_tile = dynamic_pointer_cast<MainTile>(Tiles.at((size_t)board_cords.x * board_size + board_cords.y));
                        
                        if (selected_tile != nullptr) {
                            if (moves.size() == 0 && selected_tile->has_piece() && click_flag == false) {
                                //cout << "FIRST: " << board_cords.x << " " << board_cords.y << endl;
                                click_flag = true;
                                temp = Vector2i(board_cords);
                                function_pointer = selected_tile->get_piece_moveset();
                            }
                            else if (moves.size() == 0 && click_flag == true) {
                                //cout << "SECOND: " << board_cords.x << " " << board_cords.y << endl;
                                if (function_pointer != nullptr && function_pointer(temp, board_cords)) {
                                    click_flag = false;
                                    moves.push_back(Move(temp, board_cords));
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
                else {
                    Vector2f cords = Vector2f(Mouse::getPosition(window));
                    if (start.contains(cords)) {
                        game_started = start.on_click(game_started) & (int)board_radio.is_checked();
                    }
                    else if (board_radio.contains(cords)) {
                        board_size = board_radio.select(cords);
                        tile_size = ((window_heigth < window_width) ? window_heigth : window_width) / board_size;
                        //int tile_count = board_size * board_size;

                        x_offset = (window_heigth < window_width) ? (window_width - board_size * tile_size) / 2 : 0;
                        y_offset = (window_heigth < window_width) ? 0 : (window_width - board_size * tile_size) / 2;
                        Tiles = create_board(Pieces);
                    }
                    else if (rule.contains(cords)) {
                        rule.on_click();
                    }
                }
            }
        }
        //drawing
        window.clear();
        window.draw(background);
        if (game_started == 1) {
            for (size_t i = 0; i < board_size; i++) {
                for (size_t j = 0; j < board_size; j++) {
                    Tiles.at(i * board_size + j)->draw();
                }
            }
        }
        else {
            start.draw();
            board_radio.draw();
            rule.draw();
            window.draw(x);
        }
        window.display();
    }*/

    return 0;
}