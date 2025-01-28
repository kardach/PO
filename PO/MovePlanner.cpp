#include <SFML/Graphics.hpp>
#include <functional>

#include "MovePlanner.h"
#include "Team.h"
#include "Settings.h"
#include "Rules.h"
#include "Board.h"
#include "MainTile.h"
#include "Piece.h"
#include "Turn.h"
#include "Move.h"

#include <iostream>

MovePlanner::MovePlanner(const Settings& settings, const Turn& turn, const Board& board) {
    m_board_size = settings.getBoardSize();
    Rules m_rules = settings.getGameplayRules();
    m_turn = &turn;
    m_board = &board;
    m_move_type = None;
    m_promote_flag = false;

    if (m_rules.men_move_backwards) {
        m_man_can_jump = [=](const sf::Vector2u& from, const sf::Vector2u& to) {
            sf::Vector2i delta(to - from);
            Team turn = m_turn->getTeam();
            if (std::abs(delta.x) == 1 && std::abs(delta.y) == 1) {
                return true;
            }
            return false;
            };
    }
    else {
        m_man_can_jump = [=](const sf::Vector2u& from, const sf::Vector2u& to) {
            sf::Vector2i delta(to - from);
            Team turn = m_turn->getTeam();
            if ((turn == Team::Black && delta.y == 1 || turn == Team::White && delta.y == -1) &&
                std::abs(delta.x) == 1) {
                return true;
            }
            return false;
            };
    }
    if (m_rules.men_capture_backwards) {
        m_man_can_capture = [=](const sf::Vector2u& from, const sf::Vector2u& to) {
            sf::Vector2i delta(to - from);
            Team turn = m_turn->getTeam();
            if (std::abs(delta.x) == 2 && std::abs(delta.y) == 2) {
                sf::Vector2u jumped_over(sf::Vector2f(from + to) * 0.5f);
                const MainTile* tile = m_board->at(jumped_over);
                return tile->hasPiece() && tile->getPiece()->getTeam() == !turn;
            }
            return false;
        };
    }
    else {
        m_man_can_capture = [=](const sf::Vector2u& from, const sf::Vector2u& to) {
            sf::Vector2i delta(to - from);
            Team turn = m_turn->getTeam();
            if ((turn == Team::Black && delta.y == 2 || turn == Team::White && delta.y == -2) &&
                std::abs(delta.x) == 2 ) {
                sf::Vector2u jumped_over(sf::Vector2f(from + to) * 0.5f);
                const MainTile* tile = m_board->at(jumped_over);
                return tile->hasPiece() && tile->getPiece()->getTeam() == !turn;
            }
            return false;
            };
    }
    if (m_rules.kings_fly) {
        m_king_can_jump = [=](const sf::Vector2u& from, const sf::Vector2u& to) {
            sf::Vector2i delta(to - from);
            Team turn = m_turn->getTeam();
            sf::Vector2i increment;
            sf::Vector2u jumped_over = from;
            bool empty_diagonal = true;
            if (delta.x != 0 && delta.y != 0 && std::abs(delta.x) == std::abs(delta.y)) {
                increment = sf::Vector2i(delta.x / std::abs(delta.x), delta.y / std::abs(delta.y));
                for (int i = 0; i < std::abs(delta.x); i++) {
                    jumped_over = sf::Vector2u(sf::Vector2i(jumped_over) + increment);
                    const MainTile* tile = m_board->at(jumped_over);
                    empty_diagonal &= !tile->hasPiece();
                }
                return empty_diagonal;
            }
            return false;
            };
        m_king_can_capture = [=](const sf::Vector2u& from, const sf::Vector2u& to) {
            sf::Vector2i delta(to - from);
            Team turn = m_turn->getTeam();
            sf::Vector2i increment;
            sf::Vector2u jumped_over = from;
            bool no_friends_diagonal = true;
            int enemy_count = 0;
            if (delta.x != 0 && delta.y != 0 && std::abs(delta.x) == std::abs(delta.y)) {
                increment = sf::Vector2i(delta.x / std::abs(delta.x), delta.y / std::abs(delta.y));
                for (int i = 0; i < std::abs(delta.x); i++) {
                    jumped_over = sf::Vector2u(sf::Vector2i(jumped_over) + increment);
                    const MainTile* tile = m_board->at(jumped_over);
                    if (tile->hasPiece()) {
                        const Piece* piece = tile->getPiece();
                        enemy_count += piece->getTeam() != m_turn->getTeam();
                        no_friends_diagonal &= !(piece->getTeam() == m_turn->getTeam());
                    }
                }
                return no_friends_diagonal && enemy_count == 1;
            }
            return false;
            };
    }
    else {
        m_king_can_jump = [=](const sf::Vector2u& from, const sf::Vector2u& to) {
            sf::Vector2i delta(to - from);
            Team turn = m_turn->getTeam();
            if (std::abs(delta.x) == 1 && std::abs(delta.y) == 1) {
                return true;
            }
            return false;
            };
        m_king_can_capture = [=](const sf::Vector2u& from, const sf::Vector2u& to) {
            sf::Vector2i delta(to - from);
            Team turn = m_turn->getTeam();
            if (std::abs(delta.x) == 2 && std::abs(delta.y) == 2) {
                sf::Vector2u jumped_over(sf::Vector2f(from + to) * 0.5f);
                const MainTile* tile = m_board->at(jumped_over);
                return tile->hasPiece() && tile->getPiece()->getTeam() == !turn;
            }
            return false;
            };
    }
}

MovePlanner::~MovePlanner() {
}

int MovePlanner::tryAdding(const sf::Vector2u& from, const sf::Vector2u& to) {
    if (1 <= from.x && from.x <= m_board_size && 1 <= from.y && from.y <= m_board_size &&
        1 <= to.x && to.x <= m_board_size && 1 <= to.y && to.y <= m_board_size && from != to) {
        //std::cout << "FROM: X=" << from.x << " Y=" << from.y << std::endl;
        //std::cout << "TO: X=" << to.x << " Y=" << to.y << std::endl;
        
        const MainTile* from_tile = m_board->at(from);
        const MainTile* to_tile = m_board->at(to);
        if (m_turn->getTeam() == Team::Black && to.y == m_board_size ||
            m_turn->getTeam() == Team::White && to.y == m_board_size) {
            m_promote_flag = true;
        }
        if (m_move_type == None) {
            //std::cout << "NONE\n";
            if (from_tile->hasPiece() && !to_tile->hasPiece()) {
                const Piece* piece = from_tile->getPiece();
                if (piece->getTeam() == m_turn->getTeam()) {
                    if (piece->getType() == Piece::Man && m_man_can_jump(from, to) ||
                        piece->getType() == Piece::King && m_king_can_jump(from,to)) {
                        m_moves.push_back(Move(from, to, Move::Jump));
                        m_move_type = Jump;
                        return 1;
                    }
                    if (piece->getType() == Piece::Man && m_man_can_capture(from, to) ||
                        piece->getType() == Piece::King && m_king_can_capture(from, to)) {
                        m_moves.push_back(Move(from, to, Move::Capture));
                        m_move_type = Capture;
                        return 1;
                    }
                }
            }
        }
        else if (m_move_type == Jump) {
            Move last = m_moves.at(m_moves.size() - 1);
            const Piece* piece = m_board->at(m_moves.at(0).from())->getPiece();
            if (last.from() == to && last.to() == from) {
                if (piece->getType() == Piece::Man && m_man_can_jump(to, from) ||
                    piece->getType() == Piece::King && m_king_can_jump(to, from)) {
                    m_moves.pop_back();
                    m_move_type = None;
                    return -1;
                }
            }
        }
        else if (m_move_type == Capture) {
            Move last = m_moves.at(m_moves.size() - 1);
            const Piece* piece = m_board->at(m_moves.at(0).from())->getPiece();
            if (last.to() == from) {
                if (last.from() == to) {
                    if (piece->getType() == Piece::Man && m_man_can_capture(to, from) ||
                        piece->getType() == Piece::King && m_king_can_capture(to, from)) {
                        if (m_promote_flag == true) {
                            m_promote_flag = false;
                        }
                        m_moves.pop_back();
                        if (m_moves.size() == 0) {
                            m_move_type = None;
                        }
                        return -1;
                    }
                }
                else {
                    if (!to_tile->hasPiece()) {
                        if (piece->getType() == Piece::Man && (m_turn->getTeam() == Team::Black && from.y == m_board_size ||
                            m_turn->getTeam() == Team::White && from.y == 1)) {
                            m_promote_flag = true;
                        }
                        if (piece->getType() == Piece::Man && m_man_can_capture(from, to) && !m_promote_flag ||
                            piece->getType() == Piece::King && m_king_can_capture(from ,to)) {
                            m_moves.push_back(Move(from, to, Move::Capture));
                            return 1;
                        }
                    }
                }  
            }
        }

    }
    return 0;
}

std::vector<Move> MovePlanner::getMoves() {
    return m_moves;
}

void MovePlanner::clear() {
    m_moves.clear();
    m_move_type = None;
}