#include <SFML/Graphics.hpp>

#include "Move.h"

Move::Move(const sf::Vector2u& from, const sf::Vector2u& to) {
	m_from = from;
	m_to = to;
}

Move::~Move() {
}

sf::Vector2u Move::from() {
	return m_from;
}

sf::Vector2u Move::to() {
	return m_to;
}

//Move::Move(const Board& board, const Settings& settings) {
//    m_offset = board.getOffset();
//    m_tile_size = board.getTileSize();
//    m_board_size = settings.getBoardSize();
//}
//
//Move::~Move() {
//}
//
//Move::Move(Move&& other) noexcept {
//    m_offset = other.m_offset;
//    m_tile_size = other.m_tile_size;
//    m_board_size = other.m_board_size;
//    m_submoves = std::move(other.m_submoves);
//}
//
//Move& Move::operator=(Move&& other) noexcept {
//    if (this != &other) {
//        m_submoves = std::move(other.m_submoves);
//        m_tile_size = other.m_tile_size;
//        m_offset = other.m_offset;
//        m_board_size = other.m_board_size;
//    }
//    return *this;
//}
//
//void Move::add(const sf::Vector2u& from, const sf::Vector2u& to) {
//    m_submoves.push_back(std::make_unique<SubMove>(*this, from, to));
//}
//
//void Move::remove() {
//    m_submoves.pop_back();
//}
//
//void Move::clear() {
//    m_submoves.clear();
//}
//
//std::size_t Move::size() {
//    return m_submoves.size();
//}
//
//void Move::draw(sf::RenderTarget& target, sf::RenderStates states) const {
//    for (std::size_t i = 0; i < m_submoves.size(); i++) {
//        m_submoves.at(i)->draw(target, states);
//    }
//}