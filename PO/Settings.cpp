#include <SFML/Graphics.hpp>

#include "Settings.h"

Settings::Settings(const sf::Vector2u& window_dimensions)
    : m_window_dimensions(window_dimensions), m_board_size(2), m_piece_row_count(0), m_first_move(FirstMove::Black) {
}

Settings::Settings(const sf::Vector2u& window_dimensions, const unsigned int board_size, const unsigned int piece_row_count, FirstMove first_move)
    : m_window_dimensions(window_dimensions), m_board_size(board_size + 2), m_piece_row_count(piece_row_count), m_first_move(first_move) {
}

void Settings::setBoardSize(const unsigned int board_size) {
    m_board_size = board_size + 2;
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