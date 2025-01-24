#pragma once

#ifndef MOVEPLANNER_H_
#define MOVEPLANNER_H_

#include <functional>
class Settings;
class Board;
class Turn;
class Move;

class MovePlanner {
private:
    unsigned int m_board_size;

    const Turn* m_turn;

    const Board* m_board;

    std::vector<Move> m_moves;

    std::function<bool(const sf::Vector2u&, const sf::Vector2u&)> m_man_can_jump;

    std::function<bool(const sf::Vector2u&, const sf::Vector2u&)> m_man_can_capture;

    std::function<bool(const sf::Vector2u&, const sf::Vector2u&)> m_king_can_jump;

    std::function<bool(const sf::Vector2u&, const sf::Vector2u&)> m_king_can_capture;

    enum MoveType : int {None, Jump, Capture};

    MoveType m_move_type;

    bool m_promote_flag;
public:
    MovePlanner(const Settings&, const Turn&, const Board&);

    ~MovePlanner();

    int tryAdding(const sf::Vector2u&, const sf::Vector2u&);

    std::vector<Move> getMoves();

    void clear();
};

#endif // MOVEPLANNER_H_