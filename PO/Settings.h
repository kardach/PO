#pragma once

#ifndef SETTINGS_H_
#define SETTINGS_H_

class Settings {
private:
    sf::Vector2u m_window_dimensions;

    unsigned int m_board_size;

    unsigned int m_piece_count;

public:
    Settings(const sf::Vector2u&);

    Settings(const sf::Vector2u&, const unsigned int, const unsigned int);

    void setBoardSize(const unsigned int);

    const unsigned int getBoardSize() const;

    void setPieceCount(const unsigned int);

    const unsigned int getPieceCount() const;
};

#endif // SETTINGS_H_