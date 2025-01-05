#include <SFML/Graphics.hpp>
#include <vector>

#include "MovePlanner.h"
#include "Settings.h"
#include "Turn.h"
#include "Move.h"

#include <iostream>

MovePlanner::MovePlanner(const Settings& settings, const Turn& turn) {
    m_board_size = settings.getBoardSize();
    m_turn = std::make_shared<Turn>(turn);
}

MovePlanner::~MovePlanner() {
}

int MovePlanner::tryAdding(const sf::Vector2u& from, const sf::Vector2u& to) {
    std::cout << "FROM " << from.x << " " << from.y << " TO " << to.x << " " << to.y << std::endl;
    std::cout << "BOARD SIZE " << m_board_size << std::endl;
    if (1 <= from.x && from.x <= m_board_size && 1 <= from.y && from.y <= m_board_size
        && 1 <= to.x && to.x <= m_board_size && 1 <= to.y && to.y <= m_board_size && from != to) {
        if (m_moves.size() == 0) {
            m_moves.push_back(Move(from, to));
            std::cout << "ADDED1 " << m_moves.size() << std::endl;
            return 1;
        }
        else {
            if (m_moves.at(m_moves.size() - 1).to() == from) {
                if (m_moves.at(m_moves.size() - 1).from() == to) {
                    m_moves.pop_back();
                    std::cout << "REMOVED " << m_moves.size() << std::endl;
                    return -1;
                }
                else {
                    m_moves.push_back(Move(from, to));
                    std::cout << "ADDED2 " << m_moves.size() << std::endl;
                    return 1;
                }
            }
            else {
                std::cout << "DIDNT ADD2" << std::endl;
            }
        }
    }
    else {
        std::cout << "DIDNT ADD1" << std::endl;
        return 0;
    }
    std::cout << "DIDNT ADD3" << std::endl;
    return 0;
}

std::vector<Move> MovePlanner::getMoves() {
    return m_moves;
}

void MovePlanner::clear() {
    m_moves.clear();
}