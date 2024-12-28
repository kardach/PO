#include <SFML/Graphics.hpp>
#include <iostream>

#include "RoundedRectangle.h"
#include "Settings.h"
#include "Button.h"
#include "Radio.h"
#include "Option.h"
#include "Board.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Draughts", sf::Style::Close | sf::Style::Titlebar);

    Settings settings(window.getSize());

    sf::RectangleShape background(sf::Vector2f(window.getSize()));
    background.setPosition(0.f, 0.f);
    background.setFillColor(sf::Color(128, 128, 128));

    Board board(window.getSize(), settings);

    Button new_game_button;
    {
        new_game_button.setSize(sf::Vector2f(200.f, 100.f));
        new_game_button.setPosition(sf::Vector2f(200.f, 0.f));
        new_game_button.setFillColor(sf::Color::Red);
        new_game_button.setTextColor(sf::Color::Blue);
        new_game_button.setString("NEW GAME");
    }

    Button exit_button;
    {
        exit_button.setSize(sf::Vector2f(200.f, 100.f));
        exit_button.setPosition(sf::Vector2f(200.f, 100.f));
        exit_button.setFillColor(sf::Color::Red);
        exit_button.setTextColor(sf::Color::Blue);
        exit_button.setString("EXIT");
    }

    Radio board_size;
    board_size.setPosition(sf::Vector2f(0.f, 0.f));
    board_size.addOption("8 x 8", "|8 x 8|");
    board_size.addOption("10 x 10", "|10 x 10|");
    board_size.addOption("12 x 12", "|12 x 12|");

    Radio row_count;
    row_count.setPosition(sf::Vector2f(0.f, 100.f));
    row_count.addOption("1", "|1|");
    row_count.addOption("2", "|2|");
    row_count.addOption("3", "|3|");
    row_count.addOption("4", "|4|");
    row_count.addOption("5", "|5|");

    Radio first_move;
    
    first_move.addOption("BLACK", "|BLACK|");
    first_move.addOption("WHITE", "|WHITE|");
    first_move.setPosition(sf::Vector2f(0.f, 200.f));

    first_move.option("BLACK");

    Button start_game_button;
    {
        start_game_button.setSize(sf::Vector2f(200.f, 100.f));
        start_game_button.setPosition(sf::Vector2f(0.f, 400.f));
        start_game_button.setFillColor(sf::Color::Red);
        start_game_button.setTextColor(sf::Color::Blue);
        start_game_button.setString("START GAME");
    }

    bool game_started = false;

    bool settings_chosen = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
            else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f cords = sf::Vector2f(sf::Mouse::getPosition(window));
                if (!game_started) {
                    if (new_game_button.contains(cords)) {
                        game_started = true;
                    }
                    if (exit_button.contains(cords)) {
                        window.close();
                    }
                }
                else if (!settings_chosen) {
                    if (board_size["8 x 8"].isEnabled() && board_size["8 x 8"].contains(cords)) {
                        settings.setBoardSize(8);
                        row_count["4"].disable();
                        row_count["5"].disable();
                    }
                    else if (board_size["10 x 10"].isEnabled() && board_size.option("10 x 10").contains(cords)) {
                        settings.setBoardSize(10);
                        row_count.option("5").disable();
                        row_count.option("4").disable();
                    }
                    else if (board_size["12 x 12"].isEnabled() && board_size.option("12 x 12").contains(cords)) {
                        settings.setBoardSize(12);
                        row_count["5"].enable();
                        row_count["4"].enable();
                    }
                    else if (row_count["1"].isEnabled() && row_count.option("1").contains(cords)) {
                        settings.setPieceRowCount(1);
                        board_size["10 x 10"].enable();
                        board_size["8 x 8"].enable();
                    }
                    else if (row_count["2"].isEnabled() && row_count.option("2").contains(cords)) {
                        settings.setPieceRowCount(2);
                        board_size["10 x 10"].enable();
                        board_size["8 x 8"].enable();
                    }
                    else if (row_count["3"].isEnabled() && row_count.option("3").contains(cords)) {
                        settings.setPieceRowCount(3);
                        board_size["10 x 10"].enable();
                        board_size["8 x 8"].enable();
                    }
                    else if (row_count["4"].isEnabled() && row_count.option("4").contains(cords)) {
                        settings.setPieceRowCount(4);
                        board_size["10 x 10"].enable();
                        board_size["8 x 8"].disable();
                    }
                    else if (row_count["5"].isEnabled() && row_count.option("5").contains(cords)) {
                        settings.setPieceRowCount(5);
                        board_size["10 x 10"].disable();
                        board_size["8 x 8"].disable();
                    }
                    else if (first_move.option("BLACK").contains(cords)) {
                        settings.setFirstMove(Settings::FirstMove::Black);
                        first_move["WHITE"];
                    }
                    else if (first_move.option("WHITE").contains(cords)) {
                        settings.setFirstMove(Settings::FirstMove::White);
                    }
                    else if (start_game_button.contains(cords)) {
                        settings_chosen = true;
                        board = Board(window.getSize(), settings);
                    }
                }
            }
        }
        window.clear();
        window.draw(background);
        if (!game_started) {
            window.draw(new_game_button);
            window.draw(exit_button);
        }
        else if (!settings_chosen) {
            window.draw(board_size);
            window.draw(row_count);
            window.draw(first_move);
            window.draw(start_game_button);
        }
        else {
            window.draw(board);
        }
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