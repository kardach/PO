#include <SFML/Graphics.hpp>

#include "MoveDepiction.h"
#include "Settings.h"
#include "Board.h"
#include "Move.h"
#include "Arrow.h"

#include <iostream>

MoveDepiction::MoveDepiction(const Settings& settings, const Board& board) {
    m_offset = board.getOffset();
    m_tile_size = board.getTileSize();
    m_board_size = settings.getBoardSize();
}

MoveDepiction::~MoveDepiction() {
}

void MoveDepiction::update(std::vector<Move>& move) {
    m_arrows.clear();
    sf::Vector2f arrow_from;
    sf::Vector2f arrow_to;

    //std::cout << "OK";

    for (std::size_t i = 0; i < move.size(); i++) {
        arrow_from = sf::Vector2f(move.at(i).from());
        arrow_from *= m_tile_size;
        arrow_from += sf::Vector2f(m_tile_size / 2, m_tile_size / 2);
        arrow_from += m_offset;

        arrow_to = sf::Vector2f(move.at(i).to());
        arrow_to *= m_tile_size;
        arrow_to += sf::Vector2f(m_tile_size / 2, m_tile_size / 2);
        arrow_to += m_offset;
        m_arrows.push_back(Arrow(arrow_from, arrow_to));
    }
}

void MoveDepiction::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (std::size_t i = 0; i < m_arrows.size(); i++) {
        m_arrows.at(i).draw(target, states);
    }
}