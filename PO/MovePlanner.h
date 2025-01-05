#pragma once

#ifndef MOVEPLANNER_H_
#define MOVEPLANNER_H_

class Settings;
class Turn;
class Move;

class MovePlanner {
private:
    unsigned int m_board_size;

    std::shared_ptr<Turn> m_turn;

    std::vector<Move> m_moves;
public:
    MovePlanner(const Settings&, const Turn&);

    ~MovePlanner();

    int tryAdding(const sf::Vector2u&, const sf::Vector2u&);

    std::vector<Move> getMoves();

    void clear();
};

#endif // MOVEPLANNER_H_