#include <SFML/Graphics.hpp>
#include <array>

#include "Settings.h"

Settings::Settings(const sf::Vector2u& window_dimensions) :
    m_window_dimensions(window_dimensions),
    m_board_size(0),
    m_piece_row_count(0),
    m_first_move(FirstMove::Black),
    m_mandatory_capture(false),
    m_men_move_backwards(false),
    m_men_capture_backwards(false),
    m_kings_fly(false) {
}

//Settings::Settings(
//    const sf::Vector2u& window_dimensions,
//    const unsigned int board_size,
//    const unsigned int piece_row_count,
//    FirstMove first_move
//) : 
//    m_window_dimensions(window_dimensions), 
//    m_board_size(board_size + 2), 
//    m_piece_row_count(piece_row_count), 
//    m_first_move(first_move) {
//}

const sf::Vector2u Settings::getWindowDimensions() const {
    return m_window_dimensions;
}

void Settings::setBoardSize(const unsigned int board_size) {
    m_board_size = board_size;
}

const unsigned int Settings::getBoardSize() const {
    return m_board_size;
}

void Settings::setPieceRowCount(const unsigned int piece_row_count) {
    m_piece_row_count = piece_row_count;
}

const unsigned int Settings::getPieceRowCount() const {
    return m_piece_row_count;
}

void Settings::setFirstMove(const FirstMove first_move) {
    m_first_move = first_move;
}

const Settings::FirstMove Settings::getFirstMove() const {
    return m_first_move;
}

void Settings::setGameplayRules(const bool mandatory_capture, const bool men_move_backwards, const bool men_capture_backwards, const bool kings_fly) {
    m_mandatory_capture = mandatory_capture;
    m_men_move_backwards = men_move_backwards;
    m_men_capture_backwards = men_capture_backwards;
    m_kings_fly = kings_fly;
}

const std::array<bool, 4> Settings::getGameplayRules() {
    return std::array<bool, 4>{ m_mandatory_capture, m_men_move_backwards, m_men_capture_backwards, m_kings_fly };
}