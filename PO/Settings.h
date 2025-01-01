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

    bool m_mandatory_capture;

    bool m_men_move_backwards;

    bool m_men_capture_backwards;

    bool m_kings_fly;
public:
    Settings(const sf::Vector2u&);

    //Settings(const sf::Vector2u&, const unsigned int, const unsigned int, FirstMove);

    const sf::Vector2u getWindowDimensions() const;

    void setBoardSize(const unsigned int);

    const unsigned int getBoardSize() const;

    void setPieceRowCount(const unsigned int);

    const unsigned int getPieceRowCount() const;

    void setFirstMove(const FirstMove);

    const FirstMove getFirstMove() const;

    void setGameplayRules(const bool, const bool, const bool, const bool);

    const std::array<bool, 4> getGameplayRules();
};

#endif // SETTINGS_H_