#include <SFML/Graphics.hpp>
#include <iostream>
//#include <array>

#include "RoundedRectangle.h"
#include "Settings.h"
#include "Button.h"
#include "Radio.h"
//#include "Option.h"
#include "Checkbox.h"
#include "Board.h"

class Arrow : public sf::Drawable {
private:
    sf::CircleShape m_head;
    sf::RectangleShape m_shaft;
    sf::Vector2f m_from;
    sf::Vector2f m_to;
public:
    Arrow() {
        m_from = sf::Vector2f();
        m_to = sf::Vector2f();
        m_head = sf::CircleShape();
        m_shaft = sf::RectangleShape();
    }
    Arrow(const sf::Vector2f& from, const sf::Vector2f& to) {
        m_from = from;
        m_to = to;
        float delta_x = to.x - from.x;
        float delta_y = to.y - from.y;
        static const float pi = 3.141592654f;
        float length = std::sqrt(std::pow(delta_x, 2.f) + std::pow(delta_y, 2.f));
        float radians = std::atan(delta_y / delta_x);
        float angle =  radians * 180.f / pi;

        float head_x = (length - 20.f) * std::cos(radians) * (delta_x < 0 ? -1.f : 1.f);
        float head_y = (length - 20.f) * std::sin(radians) * (delta_x < 0 ? -1.f : 1.f);
        std::cout << delta_x << " " << delta_y << std::endl;
        std::cout << "ANGLE: " << angle << " " << std::sin(angle) << " " << std::cos(angle) << std::endl;
        std::cout << head_x << " " << head_y << std::endl;

        m_head = sf::CircleShape();
        m_head.setPosition(sf::Vector2f(from.x + head_x, from.y + head_y));
        m_head.setPointCount(3);
        m_head.setRadius(20.f);
        m_head.setOrigin(sf::Vector2f(20.f, 20.f));
        m_head.setFillColor(sf::Color(255, 0, 0, 192));
        m_head.rotate((delta_x < 0 ? -90.f : 90.f) + angle);

        m_shaft = sf::RectangleShape();
        m_shaft.setPosition(from);
        m_shaft.setSize(sf::Vector2f(20.f, length - 10.f - 20.f));
        m_shaft.setOrigin(sf::Vector2f(10.f, 0.f));
        m_shaft.setFillColor(sf::Color(255, 0, 0, 192));
        m_shaft.rotate((delta_x < 0 ? 90.f : -90.f) + angle);
    }
    void setThickness(float thickness) {
        sf::Vector2f size = m_shaft.getSize();
        size.x = thickness;
        m_shaft.setSize(size);
        m_shaft.setOrigin(sf::Vector2f(thickness / 2, 0.f));
    }
    void setHeadSize(float radius) {
        sf::Vector2f size = m_shaft.getSize();
        float delta_x = m_to.x - m_from.x;
        float delta_y = m_to.y - m_from.y;
        float radians = std::atan(delta_y / delta_x);
        float length = std::sqrt(std::pow(delta_x, 2.f) + std::pow(delta_y, 2.f));
        size.y = length - 1.5f * radius;
        float head_x = (length - radius) * std::cos(radians) * (delta_x < 0 ? -1.f : 1.f);
        float head_y = (length - radius) * std::sin(radians) * (delta_x < 0 ? -1.f : 1.f);

        m_head.setPosition(sf::Vector2f(m_from.x + head_x, m_from.y + head_y));
        m_head.setRadius(radius);
        m_head.setOrigin(sf::Vector2f(radius, radius));
        
        m_shaft.setSize(size);
    }
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        target.draw(m_head, states);
        target.draw(m_shaft, states);
    }
};

class Move : public sf::Drawable {
private:
    class SubMove : public sf::Drawable {
    public:
        sf::Vector2i from;
        sf::Vector2i to;
    private:
        Move& m_move;
        Arrow m_arrow;
    public:
        SubMove(Move& move, const sf::Vector2i& from, const sf::Vector2i& to) : m_move(move), from(from), to(to) {
            sf::Vector2f arrow_from(from);
            arrow_from *= m_move.m_tile_size;
            arrow_from += sf::Vector2f(m_move.m_tile_size / 2, m_move.m_tile_size /2);
            arrow_from += m_move.m_offset;
            sf::Vector2f arrow_to(to);
            arrow_to *= m_move.m_tile_size;
            arrow_to += sf::Vector2f(m_move.m_tile_size / 2, m_move.m_tile_size / 2);
            arrow_to += m_move.m_offset;
            m_arrow = Arrow(arrow_from, arrow_to);
        }
        ~SubMove() {
        }
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
            
            target.draw(m_arrow, states);
        }
    };
    std::vector<std::shared_ptr<SubMove>> m_submoves;
    sf::Vector2f m_offset;
    float m_tile_size;
public:
    Move(const Board& board) {
        m_offset = board.getOffset();
        m_tile_size = board.getTileSize();
    }
    ~Move() {
    }
    void add(const sf::Vector2i& from, const sf::Vector2i& to) {
        
        if (m_submoves.size() > 0) {
            if (m_submoves.at(m_submoves.size() - 1)->from == to && m_submoves.at(m_submoves.size() - 1)->to == from) {
                m_submoves.pop_back();
            }
        }
        m_submoves.push_back(std::make_shared<SubMove>(*this, from, to));
        std::cout << "ADDED" << m_submoves.size() << std::endl;
    }
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        
        for (std::size_t i = 0; i < m_submoves.size(); i++) {
            m_submoves.at(i)->draw(target, states);
        }
    }
};

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Draughts", sf::Style::Close | sf::Style::Titlebar);

    Settings settings(window.getSize());

    sf::RectangleShape background(sf::Vector2f(window.getSize()));
    background.setPosition(0.f, 0.f);
    background.setFillColor(sf::Color(128, 128, 128));

    Board board(settings);

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
    {
        board_size.setPosition(sf::Vector2f(0.f, 0.f));
        board_size.addOption("8 x 8", "|8 x 8|");
        board_size.addOption("10 x 10", "|10 x 10|");
        board_size.addOption("12 x 12", "|12 x 12|");
    }

    Radio row_count;
    {
        row_count.setPosition(sf::Vector2f(0.f, 100.f));
        row_count.addOption("1", "|1|");
        row_count.addOption("2", "|2|");
        row_count.addOption("3", "|3|");
        row_count.addOption("4", "|4|");
        row_count.addOption("5", "|5|");
        row_count.addOption("5", "|5|");
    }

    Radio first_move;
    {
        first_move.addOption("BLACK", "|BLACK|");
        first_move.addOption("WHITE", "|WHITE|");
        first_move.setPosition(sf::Vector2f(0.f, 200.f));
    }

    Button start_game_button;
    {
        start_game_button.setSize(sf::Vector2f(200.f, 100.f));
        start_game_button.setPosition(sf::Vector2f(400.f, 400.f));
        start_game_button.setFillColor(sf::Color::Red);
        start_game_button.setTextColor(sf::Color::Blue);
        start_game_button.setString("START GAME");
    }

    Checkbox men_capture_backwards("|Men can capture backwards|");
    men_capture_backwards.setPosition(sf::Vector2f(0.f, 300.f));

    Checkbox mandatory_capture("|Mandatory capture|");
    mandatory_capture.setPosition(sf::Vector2f(0.f, 350.f));

    Checkbox kings_move_any_dist("|Kings can move any distance|");
    kings_move_any_dist.setPosition(sf::Vector2f(0.f, 400.f));

    Checkbox men_move_backwards("|Men can move backwards|");
    men_move_backwards.setPosition(sf::Vector2f(0.f, 450.f));

    Button confirm_move_button;
    {
        confirm_move_button.setSize(sf::Vector2f(100.f, 100.f));
        confirm_move_button.setPosition(sf::Vector2f(0.f, 0.f));
        confirm_move_button.setFillColor(sf::Color::Red);
        confirm_move_button.setTextColor(sf::Color::Blue);
        confirm_move_button.setString("CONFIRM MOVE");
    }

    Button quit_game_button;
    {
        quit_game_button.setSize(sf::Vector2f(100.f, 100.f));
        quit_game_button.setPosition(sf::Vector2f(0.f, 200.f));
        quit_game_button.setFillColor(sf::Color::Red);
        quit_game_button.setTextColor(sf::Color::Blue);
        quit_game_button.setString("QUIT GAME");
    }
    
    bool game_started = false;

    bool settings_chosen = false;

    auto test = []() {std::cout << "AAA" << std::endl; };
    test();

    enum Turn : bool { Black, White };

    Turn turn = Black;

    Move move(board);

    //bool test[4] = { false, false, false, false };

    /*sf::Vector2f from(200.f, 200.f);
    sf::Vector2f to(200.f, 100.f);

    sf::CircleShape pointA;
    pointA.setRadius(10.f);
    pointA.setPosition(from);
    pointA.setOrigin(sf::Vector2f(pointA.getRadius(), pointA.getRadius()));
    pointA.setFillColor(sf::Color::Red);

    sf::CircleShape pointB;
    pointB.setPosition(to);
    pointB.setRadius(10.f);
    pointB.setOrigin(sf::Vector2f(pointB.getRadius(), pointB.getRadius()));
    pointB.setFillColor(sf::Color::Green);

    Arrow arrow(from ,to);*/
    //arrow.setHeadSize(40.f);
    //arrow.setThickness(100.f);
    //Arrow arrow(from ,to);
    
    sf::Vector2i from;
    sf::Vector2i to;
    

    //to = sf::Vector2f(sf::Mouse::getPosition(window));
    while (window.isOpen()) {
        sf::Event event;

        /*if (sf::Vector2f(sf::Mouse::getPosition(window)) != to) {
            to = sf::Vector2f(sf::Mouse::getPosition(window));
            arrow = Arrow(from, to);
            arrow.setHeadSize(40.f);
            arrow.setThickness(100.f);
        }*/
        

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
            //std::cout << board_size.selected() << std::endl; // UNSELECTED ERROR
            if (!game_started) {
                if (new_game_button.onClick(window, event)) {
                    game_started = true;
                }
                if (exit_button.onClick(window, event)) {
                    window.close();
                }
            }
            else if (!settings_chosen) {
                if (board_size.onClick(window, event)) {
                    std::string name = board_size.selected();
                    std::cout << name << std::endl;
                    if (name == "8 x 8") {
                        row_count.disable("4");
                        row_count.disable("5");
                    }
                    else if (name == "10 x 10") {
                        row_count.enable("4");
                        row_count.disable("5");
                    }
                    else if (name == "12 x 12") {
                        row_count.enable("4");
                        row_count.enable("5");
                    }
                }
                if (row_count.onClick(window, event)) {
                    std::string name = row_count.selected();
                    std::cout << name << std::endl;
                    if (name == "1" || name == "2" || name == "3") {
                        board_size.enable("8 x 8");
                        board_size.enable("10 x 10");
                    }
                    else if (name == "4") {
                        board_size.disable("8 x 8");
                        board_size.enable("10 x 10");
                    }
                    else if (name == "5") {
                        board_size.disable("8 x 8");
                        board_size.disable("10 x 10");
                        }
                }
                first_move.onClick(window, event);

                men_capture_backwards.onClick(window, event);
                mandatory_capture.onClick(window, event);
                kings_move_any_dist.onClick(window, event);
                men_move_backwards.onClick(window, event);

                if (start_game_button.onClick(window, event)) {
                    settings_chosen = true;
                    std::string name = board_size.selected();
                    if (name == "8 x 8") {
                        settings.setBoardSize(8);
                    }
                    else if (name == "10 x 10") {
                        settings.setBoardSize(10);
                    }
                    else if (name == "12 x 12") {
                        settings.setBoardSize(12);
                    }
                    name = row_count.selected();
                    if (name == "1") {
                        settings.setPieceRowCount(1);
                    }
                    else if (name == "2") {
                        settings.setPieceRowCount(2);
                    }
                    else if (name == "3") {
                        settings.setPieceRowCount(3);
                    }
                    else if (name == "4") {
                        settings.setPieceRowCount(4);
                    }
                    else if (name == "5") {
                        settings.setPieceRowCount(5);
                    }
                    name = first_move.selected();
                    if (name == "BLACK") {
                        settings.setFirstMove(Settings::FirstMove::Black);
                    }
                    else if (name == "WHITE") {
                        settings.setFirstMove(Settings::FirstMove::White);
                    }
                    board = Board(settings);
                    turn = Turn(settings.getFirstMove());
                    move = Move(board);
                }
            }
            else {
                
                if (board.onClick(window, event)) {
                    sf::Vector2i cords(board.getTileCords(sf::Vector2f(sf::Mouse::getPosition(window))));
                    int board_size = (int)settings.getBoardSize();
                    //std::cout << cords.x << " " << cords.y << " " << board_size << std::endl;
                    if (1 <= cords.x && cords.x <= board_size && 1 <= cords.y && cords.y <= board_size) {
                        
                        if (from == sf::Vector2i(0, 0)) {
                            from = cords;
                            std::cout << from.x << " " << from.y << " " << to.x << " " << to.y << std::endl;
                        }
                        else if (to == sf::Vector2i(0, 0)) {
                            to = cords;
                            move.add(from, to);
                            std::cout << from.x << " " << from.y << " " << to.x << " " << to.y << std::endl;

                            from = sf::Vector2i(0, 0);
                            to = sf::Vector2i(0, 0);
                        }
                        

                    }
                }
                if (confirm_move_button.onClick(window, event)) {
                    turn = (Turn)!turn;
                    move = Move(board);
                    // MAKE MOVE ON BOARD
                }
                if (quit_game_button.onClick(window, event)) {
                    settings_chosen = false;
                    game_started = false;
                    board_size.unselect();
                    board_size.enable("8 x 8");
                    board_size.enable("10 x 10");
                    board_size.enable("12 x 12");
                    row_count.unselect();
                    row_count.enable("1");
                    row_count.enable("2");
                    row_count.enable("3");
                    row_count.enable("4");
                    row_count.enable("5");
                    first_move.unselect();
                    men_capture_backwards.uncheck();
                    men_move_backwards.uncheck();
                    mandatory_capture.uncheck();
                    kings_move_any_dist.uncheck();
                }
                
            }
        }
        window.clear();
        window.draw(background);
        /*window.draw(pointA);
        window.draw(pointB);
        window.draw(arrow);*/
        if (!game_started) {
            window.draw(new_game_button);
            window.draw(exit_button);
        }
        else if (!settings_chosen) {
            window.draw(board_size);
            window.draw(row_count);
            window.draw(first_move);
            window.draw(men_capture_backwards);
            window.draw(mandatory_capture);
            window.draw(kings_move_any_dist);
            window.draw(men_move_backwards);
            window.draw(start_game_button);
        }
        else {
            window.draw(board);
            window.draw(confirm_move_button);
            window.draw(quit_game_button);
            window.draw(move);
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