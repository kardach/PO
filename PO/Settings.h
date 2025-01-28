#pragma once

#ifndef SETTINGS_H_
#define SETTINGS_H_

#include <SFML/Graphics.hpp> // ???
#include "Rules.h"
#include "Gamemode.h"

enum class Team : bool;

class Settings {
private:
    sf::Vector2u m_window_dimensions;

    unsigned int m_board_size;

    unsigned int m_piece_row_count;
    
    Team m_first_move;
    
    Rules m_rules;
    
    Gamemode m_gamemode;
public:
    Settings(const sf::Vector2u&);

    const sf::Vector2u getWindowDimensions() const;

    void setBoardSize(const unsigned int);

    const unsigned int getBoardSize() const;

    void setPieceRowCount(const unsigned int);

    const unsigned int getPieceRowCount() const;

    void setFirstMove(const Team&);

    const Team getFirstMove() const;

    void setGameplayRules(const bool, const bool, const bool, const bool);

    const Rules getGameplayRules() const;

    void setGamemode(const Gamemode&);

    const Gamemode getGamemode();
};

#endif // SETTINGS_H_