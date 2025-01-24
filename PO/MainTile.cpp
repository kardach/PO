#include <SFML/Graphics.hpp>

#include "Tile.h"
#include "MainTile.h"
#include "Piece.h"

#include <iostream>

MainTile::MainTile(const float size, const sf::Vector2f& position, const bool team)
    : Tile(size, position, team ? sf::Color(255, 228, 196) : sf::Color(139, 69, 19)) {
    m_piece = nullptr;
}

MainTile::~MainTile() {
}

void MainTile::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(m_rectangle, states);
    if (m_piece != nullptr) {
        m_piece->draw(target, states);
    }
}

void MainTile::placePiece(std::unique_ptr<Piece> piece) {
    m_piece = std::move(piece);
    //std::cout << "PLACE " << (m_piece != nullptr) << " " << (piece != nullptr) << std::endl;
    m_piece->setPosition(m_rectangle.getPosition());
}

const bool MainTile::hasPiece() const {
    //std::cout << "HAS " << (m_piece != nullptr) << std::endl;
    return m_piece != nullptr;
}

const Piece* MainTile::getPiece() const {
    //std::cout << "GET " << (m_piece != nullptr) << std::endl;
    return (m_piece == nullptr) ? nullptr : m_piece.get();
}

std::unique_ptr<Piece> MainTile::removePiece() {
    //std::cout << "BEFORE REMOVE " << (m_piece != nullptr) << std::endl;
    //std::unique_ptr<Piece> temp = nullptr;
    //temp = std::move(m_piece);
    //std::cout << "REMOVE " << (m_piece != nullptr) << " " << (temp != nullptr) << std::endl;
    return std::move(m_piece);
}