#pragma once

#ifndef SETTINGS_H_
#define SETTINGS_H_

class Settings {
public:
    enum FirstMove : bool { Black, White };
private:
    sf::Vector2u m_window_dimensions;

    unsigned int m_board_size;

    unsigned int m_piece_row_count;
    
    FirstMove m_first_move;
public:
    Settings(const sf::Vector2u&);

    Settings(const sf::Vector2u&, const unsigned int, const unsigned int, FirstMove);

    void setBoardSize(const unsigned int);

    const unsigned int getBoardSize() const;

    void setPieceRowCount(const unsigned int);

    const unsigned int getPieceRowCount() const;

    void setFirstMove(const FirstMove);

    const FirstMove getFirstMove() const;
};

#endif // SETTINGS_H_