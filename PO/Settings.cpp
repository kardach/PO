#include <SFML/Graphics.hpp>

#include "Settings.h"

Settings::Settings(const sf::Vector2u& window_dimensions)
    : m_window_dimensions(window_dimensions), m_board_size(0), m_piece_count(0) {
}

Settings::Settings(const sf::Vector2u& window_dimensions, const unsigned int board_size, const unsigned int piece_count)
    : m_window_dimensions(window_dimensions), m_board_size(board_size), m_piece_count(piece_count) {
}

void Settings::setBoardSize(const unsigned int board_size) {
    m_board_size = board_size;
}

const unsigned int Settings::getBoardSize() const {
    return m_board_size;
}

void Settings::setPieceCount(const unsigned int piece_count) {
    m_piece_count = piece_count;
}

const unsigned int Settings::getPieceCount() const {
    return m_piece_count;
}