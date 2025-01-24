#include <SFML/Graphics.hpp>
#include <array>

#include "Settings.h"
#include "Team.h"
#include "Rules.h"

Settings::Settings(const sf::Vector2u& window_dimensions) :
    m_window_dimensions(window_dimensions),
    m_board_size(0),
    m_piece_row_count(0),
    m_first_move(Team::Black),
    m_rules()
    {
}

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

void Settings::setFirstMove(const Team& first_move) {
    m_first_move = first_move;
}

const Team Settings::getFirstMove() const {
    return m_first_move;
}

void Settings::setGameplayRules(const bool mandatory_capture, const bool men_move_backwards, const bool men_capture_backwards, const bool kings_fly) {
    m_rules = Rules(mandatory_capture, men_move_backwards, men_capture_backwards, kings_fly);
}

const Rules Settings::getGameplayRules() const {
    return m_rules;
}