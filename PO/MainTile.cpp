#include <SFML/Graphics.hpp>

#include "Tile.h"
#include "MainTile.h"

MainTile::MainTile(const float size, const sf::Vector2f& position, const bool team)
    : Tile(size, position, team ? sf::Color(255, 228, 196) : sf::Color(139, 69, 19)) {
    m_piece = nullptr;
}

MainTile::~MainTile() {
}

void MainTile::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    Tile::draw(target, states);
    if (m_piece != nullptr) {
        m_piece->draw(target, states);
    }
}

void MainTile::placePiece(std::shared_ptr<Piece> piece) {
    m_piece = std::move(piece);
    m_piece->setPosition(m_rectangle.getPosition());
}

const bool MainTile::hasPiece() const {
    return m_piece != nullptr;
}

std::shared_ptr<Piece> MainTile::removePiece() {
    return std::move(m_piece);
}