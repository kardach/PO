#include <SFML/Graphics.hpp>
#include <iostream>
#include <array>

#include "Team.h"
#include "Settings.h"
#include "Button.h"
#include "Radio.h"
#include "Checkbox.h"
#include "Board.h"
#include "MainTile.h"
#include "Piece.h"
#include "Arrow.h"
#include "Move.h"
#include "Turn.h"
#include "MovePlanner.h"
#include "MoveDepiction.h"

enum GameVerdict : int { On, Draw, BlackWon, WhiteWon };

int gameEndCheck(const Settings& settings, const Board& board) {
    struct Check {
    public:
        int counter;
        bool cant_move;
        std::vector<sf::Vector2u> pieces_cords;
        MovePlanner tester;
        Check(const Settings& settings, const Turn& turn, const Board& board) : tester(settings, turn, board) {
            counter = 0;
            cant_move = true;
        }
    };

    int man_counter = 0;
    int king_counter = 0;
    const MainTile* tile;
    Turn black_turn(settings);
    Turn white_turn(settings);
    if (settings.getFirstMove() == Team::Black) {
        white_turn.change();
    }
    else {
        black_turn.change();
    }
    Check check_black(settings, black_turn, board);
    Check check_white(settings, white_turn, board);
    
    bool draw = true;

    for (unsigned int i = 1; i <= settings.getBoardSize(); i++) {
        for (unsigned int j = 1; j <= settings.getBoardSize(); j++) {
            tile = board.at(sf::Vector2u(i, j));
            if (tile->hasPiece()) {
                check_black.counter += tile->getPiece()->getTeam() == Team::Black;
                check_white.counter += tile->getPiece()->getTeam() == Team::White;
                man_counter += tile->getPiece()->getType() == Piece::Man;
                king_counter += tile->getPiece()->getType() == Piece::King;
                if (tile->getPiece()->getTeam() == Team::Black) {
                    check_black.pieces_cords.push_back(sf::Vector2u(i, j));
                }
                else {
                    check_white.pieces_cords.push_back(sf::Vector2u(i, j));
                }
            }
        }
    }
    if (check_black.counter == 0) {
        return WhiteWon;
    }
    if (check_white.counter == 0) {
        return BlackWon;
    }
    if (man_counter == 0 && king_counter > 0) {
        for (Check* check : {&check_black, &check_white}) {
            for (sf::Vector2u from : check->pieces_cords) {
                sf::Vector2u to;
                std::vector<int> range;
                for (int i = -(int)settings.getBoardSize(); i <= (int)settings.getBoardSize(); i++) {
                    if (std::abs(i) > 1) {
                        range.push_back(i);
                    }
                }
                for (int x : range) {
                    for (int y : { -x, x }) {
                        check->tester.clear();
                        to = sf::Vector2u(sf::Vector2i(from) + sf::Vector2i(x, y));
                        if (check->tester.tryAdding(from, to) == 1 && check->tester.getMoves().at(0).type() == Move::Capture) {
                            draw = false;
                        }
                    }
                }
            }
        }
        if (draw) {
            return Draw;
        }
    }
    for (Check* check : {&check_black, &check_white}) {
        for (sf::Vector2u from : check->pieces_cords) {
            sf::Vector2u to;
            std::vector<int> range;
            if (board.at(from)->getPiece()->getType() == Piece::Man) {
                range = { -2, -1, 1, 2 };
            }
            else if (board.at(from)->getPiece()->getType() == Piece::King) {
                for (int i = -(int)settings.getBoardSize(); i <= (int)settings.getBoardSize(); i++) {
                    if (std::abs(i) > 1) {
                        range.push_back(i);
                    }
                }
            }
            for (int x : range) {
                for (int y : { -x, x }) {
                    check->tester.clear();
                    to = sf::Vector2u(sf::Vector2i(from) + sf::Vector2i(x, y));
                    if (check->tester.tryAdding(from, to) == 1) {
                        check->cant_move = false;
                    }
                }
            }
        }
    }
    if (check_black.cant_move) {
        return WhiteWon;
    }
    if (check_white.cant_move) {
        return BlackWon;
    }
    return On;
}

std::vector<sf::Vector2u> mandatoryCaptureCheck(const Settings& settings, const Turn& turn, const Board& board, std::vector<Move> moves) {
    std::vector<sf::Vector2u> missed_captures;
    if (moves.at(0).type() == Move::Capture) {
        return missed_captures;
    }
    const MainTile* tile;
    MovePlanner tester(settings, turn, board);
    std::vector<sf::Vector2u> pieces_cords;
    for (unsigned int i = 1; i <= settings.getBoardSize(); i++) {
        for (unsigned int j = 1; j <= settings.getBoardSize(); j++) {
            tile = board.at(sf::Vector2u(i, j));
            if (tile->hasPiece() && tile->getPiece()->getTeam() == turn.getTeam()) {
                pieces_cords.push_back(sf::Vector2u(i, j));
            }
        }
    }
    for (sf::Vector2u from : pieces_cords) {
        sf::Vector2u to;
        std::vector<int> range;
        if (board.at(from)->getPiece()->getType() == Piece::Man) {
            range = { -2, 2 };
        }
        else if(board.at(from)->getPiece()->getType() == Piece::King) {
            for (int i = -(int)settings.getBoardSize(); i <= (int)settings.getBoardSize(); i++) {
                if (std::abs(i) > 1) {
                    range.push_back(i);
                }
            }
        }
        for (int x : range) {
            for (int y : { -x , x }) {
                tester.clear();
                to = sf::Vector2u(sf::Vector2i(from) + sf::Vector2i(x, y));
                if (tester.tryAdding(from, to) == 1 && tester.getMoves().at(0).type() == Move::Capture) {
                    if (moves.at(0).from() == from) {
                        missed_captures.push_back(moves.at(moves.size() - 1).to());
                    }
                    else {
                        missed_captures.push_back(from);
                    }
                }
            }
        }
    }
    return missed_captures;
}


class TreeNode {
private:
    sf::Vector2u m_from;
    sf::Vector2u m_to;
    int m_value;
    std::vector<TreeNode> m_next;
public:
    TreeNode(const sf::Vector2u& from, const sf::Vector2u& to, const int value) {
        m_from = from;
        m_to = to;
        m_value = value;
    }
    ~TreeNode() {
    }
    void add(const TreeNode& node) {
        m_next.push_back(node);
    }
    int getValue() {
        return m_value;
    }
    sf::Vector2u getFrom() {
        return m_from;
    }
    sf::Vector2u getTo() {
        return m_to;
    }
    std::vector<TreeNode> getNext() {
        return m_next;
    }
};

void predict(const Settings& settings, Board& board) {
    enum Pieces { bM, wM, bK, wK };
    int size = settings.getBoardSize();
    
    Team player_turn = settings.getFirstMove();
    Team bot_turn = !player_turn;
    std::cout << (bool)bot_turn << " " << (bool)player_turn << std::endl;
    
    Rules rules = settings.getGameplayRules();
    
    const MainTile* tile;
    int code = 0;
    std::vector<int> board_repre;
    std::vector<sf::Vector2u> bot_pieces;
    std::vector<sf::Vector2u> player_pieces;
    for (int i = 1; i <= size; i++) {
        for (int j = 1; j <= size; j++) {
            tile = board.at(sf::Vector2u(i, j));
            code = 0;
            if (tile->hasPiece()) {
                if (tile->getPiece()->getTeam() == Team::Black) {
                    code |= 0;
                    if (bot_turn == Team::Black) {
                        bot_pieces.push_back(sf::Vector2u(i, j));
                    }
                    else {
                        player_pieces.push_back(sf::Vector2u(i, j));
                    }
                }
                else {
                    code |= 1;
                    if (bot_turn == Team::White) {
                        bot_pieces.push_back(sf::Vector2u(i, j));
                    }
                    else {
                        player_pieces.push_back(sf::Vector2u(i, j));
                    }
                }
                if (tile->getPiece()->getType() == Piece::Man) {
                    code |= 0;
                }
                else {
                    code |= 2;
                }
            }
            else {
                code = -1;
            }
            board_repre.push_back(code);
        }
    }
    
    std::vector<sf::Vector2i> bM_move;
    std::vector<sf::Vector2i> wM_move;
    std::vector<sf::Vector2i> bK_move;
    std::vector<sf::Vector2i> wK_move;

    std::vector<sf::Vector2i> bM_capture;
    std::vector<sf::Vector2i> wM_capture;
    std::vector<sf::Vector2i> bK_capture;
    std::vector<sf::Vector2i> wK_capture;
    if (rules.men_move_backwards) {
        for (int i : {-1, 1,}) {
            for (int j : {-i, i}) {
                bM_move.push_back(sf::Vector2i(i, j));
                wM_move.push_back(sf::Vector2i(i, j));
                std::cout << i << " " << j << std::endl;
            }
        }
    }
    else {
        for (int i : {1}) {
            for (int j : {-i, i}) {
                bM_move.push_back(sf::Vector2i(i, j));
                wM_move.push_back(sf::Vector2i(-i, j));
            }
        }
    }

    if (rules.men_capture_backwards) {
        for (int i : {-2, 2}) {
            for (int j : {-i, i}) {
                bM_capture.push_back(sf::Vector2i(i, j));
                wM_capture.push_back(sf::Vector2i(i, j));
            }
        }
    }
    else {
        for (int i : {2}) {
            for (int j : {-i, i}) {
                bM_capture.push_back(sf::Vector2i(i, j));
                wM_capture.push_back(sf::Vector2i(-i, j));
            }
        }
    }

    if (rules.kings_fly) {
        for (int i = -size; i <= size; i++) {
            if (i != 0) {
                for (int j : {-i, i}) {
                    bK_move.push_back(sf::Vector2i(i, j));
                    wK_move.push_back(sf::Vector2i(i, j));
                    if (std::abs(j) != 1) {
                        bK_capture.push_back(sf::Vector2i(i, j));
                        wK_capture.push_back(sf::Vector2i(i, j));
                    }
                }
            }
        }
    }
    else {
        for (int i : {-1, 1, }) {
            for (int j : {-i, i}) {
                bM_move.push_back(sf::Vector2i(i, j));
                wM_move.push_back(sf::Vector2i(i, j));
                std::cout << i << " " << j << std::endl;
            }
        }
        for (int i : {-2, 2}) {
            for (int j : {-i, i}) {
                bM_capture.push_back(sf::Vector2i(i, j));
                wM_capture.push_back(sf::Vector2i(i, j));
            }
        }
    }

    std::vector<std::vector<sf::Vector2u>> possible;
    sf::Vector2u to;
    for (sf::Vector2u from : bot_pieces) {
        if (board_repre.at((from.x - 1) * size + (from.y - 1)) == bM) {
            for (sf::Vector2i delta : bM_move) {
                if (1 <= from.x + delta.x && from.x + delta.x <= size &&
                    1 <= from.y + delta.y && from.y + delta.y <= size) {
                    to = sf::Vector2u(sf::Vector2i(from) + delta);
                }
            }
        }
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(1200, 800), "Draughts", sf::Style::Close | sf::Style::Titlebar);

    sf::RectangleShape background(sf::Vector2f(window.getSize()));
    background.setPosition(0.f, 0.f);
    background.setFillColor(sf::Color(128, 128, 128));

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
    }

    Radio first_move;
    {
        first_move.addOption("BLACK", "|BLACK|");
        first_move.addOption("WHITE", "|WHITE|");
        first_move.setPosition(sf::Vector2f(0.f, 200.f));
    }

    Radio game_mode;
    {
        game_mode.addOption("HOT SEAT", "|HOT SEAT|");
        game_mode.addOption("VS BOT", "|VS BOT|");
        game_mode.setPosition(sf::Vector2f(0.f, 300.f));
    }

    Button start_game_button;
    {
        start_game_button.setSize(sf::Vector2f(200.f, 100.f));
        start_game_button.setPosition(sf::Vector2f(500.f, 400.f));
        start_game_button.setFillColor(sf::Color::Red);
        start_game_button.setTextColor(sf::Color::Blue);
        start_game_button.setString("START GAME");
    }

    Checkbox men_capture_backwards("|Men can capture backwards|");
    men_capture_backwards.setPosition(sf::Vector2f(0.f, 350.f));

    Checkbox mandatory_capture("|Mandatory capture|");
    mandatory_capture.setPosition(sf::Vector2f(0.f, 400.f));

    Checkbox kings_move_any_dist("|Kings can move any distance|");
    kings_move_any_dist.setPosition(sf::Vector2f(0.f, 450.f));

    Checkbox men_move_backwards("|Men can move backwards|");
    men_move_backwards.setPosition(sf::Vector2f(0.f, 500.f));

    Button confirm_move_button;
    {
        confirm_move_button.setSize(sf::Vector2f(250.f, 100.f));
        confirm_move_button.setPosition(sf::Vector2f(0.f, 0.f));
        confirm_move_button.setFillColor(sf::Color::Red);
        confirm_move_button.setTextColor(sf::Color::Blue);
        confirm_move_button.setString("CONFIRM MOVE");
    }

    Button quit_game_button;
    {
        quit_game_button.setSize(sf::Vector2f(250.f, 100.f));
        quit_game_button.setPosition(sf::Vector2f(0.f, 200.f));
        quit_game_button.setFillColor(sf::Color::Red);
        quit_game_button.setTextColor(sf::Color::Blue);
        quit_game_button.setString("QUIT GAME");
    }
    
    bool game_started = false;

    bool settings_chosen = false;

    std::unique_ptr<Settings> settings;

    std::unique_ptr<Board> board;

    std::unique_ptr<Turn> turn;

    std::unique_ptr<MovePlanner> move_planner;

    std::unique_ptr<MoveDepiction> move_depiction;
    
    std::vector<Move> move;

    sf::Vector2u previous_click;
    sf::Vector2u curr_click;

    int game_state = On;

    sf::Font font;
    font.loadFromFile("ariblk.ttf");

    sf::Text game_end_msg;
    game_end_msg.setFont(font);
    game_end_msg.setCharacterSize(24);
    game_end_msg.setPosition(sf::Vector2f(0.f, 500.f));
    game_end_msg.setFillColor(sf::Color::Green);

    sf::Text turn_msg;
    turn_msg.setFont(font);
    turn_msg.setCharacterSize(24);
    turn_msg.setPosition(sf::Vector2f(0.f, 400.f));
    turn_msg.setFillColor(sf::Color::Green);

    while (window.isOpen()) {
        sf::Event event;

        if (settings != nullptr && turn != nullptr && board != nullptr && 
            settings->getGamemode() == Gamemode::VsBot && settings->getFirstMove() != turn->getTeam()) {
            std::cout << "Bot" << std::endl;

            predict(*settings, *board);
            //move = bot(*settings, *board);

            if (move.size() > 0) {
                std::vector<sf::Vector2u> missed_captures;
                if (settings->getGameplayRules().mandatory_capture) {
                    missed_captures = mandatoryCaptureCheck(*settings, *turn, *board, move);
                }
                board->makeMove(move);
                board->penaltyRemove(missed_captures);

                game_state = gameEndCheck(*settings, *board);
                if (game_state == Draw) {
                    game_end_msg.setString("|Draw|");
                }
                else if (game_state == BlackWon) {
                    game_end_msg.setString("|Black Won|");
                }
                else if (game_state == WhiteWon) {
                    game_end_msg.setString("|White Won|");
                }
            }
            turn->change();
            turn_msg.setString(turn->getTeam() == Team::Black ? "Black" : "White");
        }

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || 
                event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
            if (!game_started) {
                if (new_game_button.onClick(window, event)) {
                    game_started = true;
                }
                if (exit_button.onClick(window, event)) {
                    window.close();
                }
            }
            else if (!settings_chosen) {

                settings = std::make_unique<Settings>(window.getSize());

                if (board_size.onClick(window, event)) {
                    if (board_size.isSelected()) {
                        std::string name = board_size.selected();
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
                }
                if (row_count.onClick(window, event)) {
                    if (row_count.isSelected()) {
                        std::string name = row_count.selected();
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
                }
                first_move.onClick(window, event);
                game_mode.onClick(window, event);

                men_capture_backwards.onClick(window, event);
                mandatory_capture.onClick(window, event);
                kings_move_any_dist.onClick(window, event);
                men_move_backwards.onClick(window, event);

                if (start_game_button.onClick(window, event) && board_size.isSelected() && row_count.isSelected() &&
                    game_mode.isSelected() && first_move.isSelected()) {
                    settings_chosen = true;
                    std::string name = board_size.selected();
                    if (name == "8 x 8") {
                        settings->setBoardSize(8);
                    }
                    else if (name == "10 x 10") {
                        settings->setBoardSize(10);
                    }
                    else if (name == "12 x 12") {
                        settings->setBoardSize(12);
                    }
                    name = row_count.selected();
                    if (name == "1") {
                        settings->setPieceRowCount(1);
                    }
                    else if (name == "2") {
                        settings->setPieceRowCount(2);
                    }
                    else if (name == "3") {
                        settings->setPieceRowCount(3);
                    }
                    else if (name == "4") {
                        settings->setPieceRowCount(4);
                    }
                    else if (name == "5") {
                        settings->setPieceRowCount(5);
                    }
                    name = first_move.selected();
                    if (name == "BLACK") {
                        settings->setFirstMove(Team::Black);
                    }
                    else if (name == "WHITE") {
                        settings->setFirstMove(Team::White);
                    }
                    name = game_mode.selected();
                    if (name == "HOT SEAT") {
                        settings->setGamemode(Gamemode::HotSeat);
                    }
                    else if(name == "VS BOT") {
                        settings->setGamemode(Gamemode::VsBot);
                    }
                    settings->setGameplayRules(
                        mandatory_capture.isChecked(),
                        men_move_backwards.isChecked(),
                        men_capture_backwards.isChecked(),
                        kings_move_any_dist.isChecked()
                    );
                    
                    board = std::make_unique<Board>(*settings);
                    turn = std::make_unique<Turn>(*settings);
                    move_planner = std::make_unique<MovePlanner>(*settings, *turn, *board);
                    move = move_planner->getMoves();
                    move_depiction = std::make_unique<MoveDepiction>(*settings, *board);
                    turn_msg.setString(turn->getTeam() == Team::Black ? "Black" : "White");
                }
            }
            else {
                if (board->onClick(window, event) && game_state == On) {
                    if (settings->getGamemode() == Gamemode::HotSeat || settings->getGamemode() == Gamemode::VsBot && settings->getFirstMove() == turn->getTeam()) {
                        previous_click = curr_click;
                        curr_click = board->getTileCords(sf::Vector2f(sf::Mouse::getPosition(window)));
                        move_planner->tryAdding(previous_click, curr_click);
                        move = move_planner->getMoves();
                        move_depiction->update(move);
                    }
                    
                }
                if (confirm_move_button.onClick(window, event)) {
                    if (move.size() > 0) {
                        std::vector<sf::Vector2u> missed_captures;
                        if (settings->getGameplayRules().mandatory_capture) {
                            missed_captures = mandatoryCaptureCheck(*settings, *turn, *board, move);
                        }
                        board->makeMove(move);
                        board->penaltyRemove(missed_captures);

                        game_state = gameEndCheck(*settings, *board);
                        if (game_state == Draw) {
                            game_end_msg.setString("|Draw|");
                        }
                        else if (game_state == BlackWon) {
                            game_end_msg.setString("|Black Won|");
                        }
                        else if (game_state == WhiteWon) {
                            game_end_msg.setString("|White Won|");
                        }

                        move_planner->clear();
                        move = move_planner->getMoves();
                        move_depiction->update(move);
                        turn->change();
                        turn_msg.setString(turn->getTeam() == Team::Black ? "Black" : "White");
                        previous_click = sf::Vector2u(0, 0);
                        curr_click = sf::Vector2u(0, 0);
                    }
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
                    game_mode.unselect();
                    men_capture_backwards.uncheck();
                    men_move_backwards.uncheck();
                    mandatory_capture.uncheck();
                    kings_move_any_dist.uncheck();
                    previous_click = sf::Vector2u(0, 0);
                    curr_click = sf::Vector2u(0, 0);
                    game_state = On;
                    game_end_msg.setString("");
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
            window.draw(game_mode);
            window.draw(men_capture_backwards);
            window.draw(mandatory_capture);
            window.draw(kings_move_any_dist);
            window.draw(men_move_backwards);
            window.draw(start_game_button);

            //window.draw(man_sprite);
        }
        else {
            window.draw(*board);
            window.draw(confirm_move_button);
            window.draw(quit_game_button);
            window.draw(game_end_msg);
            window.draw(turn_msg);
            window.draw(*move_depiction);
        }
        window.display();
    }
    return 0;
}