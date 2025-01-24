#include <SFML/Graphics.hpp>
#include <array>

//#include <iostream>

#include "Board.h"
#include "Team.h"
#include "Settings.h"
#include "Tile.h"
#include "CornerTile.h"
#include "BorderTile.h"
#include "MainTile.h"
#include "Piece.h"
#include "Move.h"

#include <iostream>

Board::Board(const Settings& settings) {
    m_size = settings.getBoardSize() + 2;
    m_piece_count = settings.getPieceRowCount() * settings.getBoardSize();
    sf::Vector2u window_dimensions = settings.getWindowDimensions();

    float window_heigth = (float)window_dimensions.y;
    float window_width = (float)window_dimensions.x;

    m_tile_size = ((window_heigth < window_width) ? window_heigth : window_width) / m_size;

    float x_offset = (window_heigth < window_width) ? (window_width - m_size * m_tile_size) / 2 : 0;
    float y_offset = (window_heigth < window_width) ? 0 : (window_width - m_size * m_tile_size) / 2;
    m_offset = sf::Vector2f(x_offset, y_offset);

    m_corners = createCorners();
    m_borders = createBorders();
    m_tiles = createMainTiles();
    std::vector<std::unique_ptr<Piece>> pieces = createPieces();
    placePieces(std::move(pieces));
}

Board::~Board() {
}

float Board::getTileSize() const {
    return m_tile_size;
}

sf::Vector2f Board::getOffset() const {
    return m_offset;
}

bool Board::onClick(const sf::RenderWindow& window, const sf::Event& event) {
    sf::Vector2f cords(sf::Mouse::getPosition(window));
    if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
        for (std::size_t i = 0; i < m_tiles.size(); i++) {
            if (m_tiles.at(i)->contains(cords)) {
                return true;
            }
        }
    }
    return false;
    
}

const MainTile* Board::at(const sf::Vector2u& cords) const {
    //std::cout << "ID=" << (cords.x - 1) * (m_size - 2) + (cords.y - 1) << std::endl;
    return m_tiles.at((cords.x - 1) * (m_size - 2) + (cords.y - 1)).get();
}

void Board::makeMove(std::vector<Move>& move) {
    sf::Vector2u from;
    sf::Vector2u to;
    sf::Vector2i delta;
    sf::Vector2i increment;
    //std::cout << "Board" << std::endl;
    for (std::size_t i = 0; i < move.size(); i++) {
        from = move.at(i).from();
        to = move.at(i).to();
        delta = sf::Vector2i(to - from);
        if (std::abs(delta.x) > 1 && std::abs(delta.y) > 1 && std::abs(delta.x) == std::abs(delta.y)) {
            increment = sf::Vector2i(delta.x / std::abs(delta.x), delta.y / std::abs(delta.y));
            while (from != to) {
                from = sf::Vector2u(sf::Vector2i(from) + increment);
                if (m_tiles.at((from.x - 1) * (m_size - 2) + (from.y - 1))->hasPiece()) {
                    std::unique_ptr<Piece> temp = m_tiles.at((from.x - 1) * (m_size - 2) + (from.y - 1))->removePiece();
                    temp.reset();
                }
            }
        }
    }
    from = move.at(0).from();
    to = move.at(move.size() - 1).to();
    std::unique_ptr<Piece> temp = m_tiles.at((from.x - 1) * (m_size - 2) + (from.y - 1))->removePiece();
    Team color = temp->getTeam();
    //std::cout << to.x << ", " << to.y << std::endl;
    if (temp->getType() == Piece::Man && (color == Team::Black && to.y == m_size - 2 || color == Team::White && to.y == 1)) {
        temp->promote();
    }
    m_tiles.at((to.x - 1) * (m_size - 2) + (to.y - 1))->placePiece(std::move(temp));
    
    move.clear();
}

void Board::penaltyRemove(std::vector<sf::Vector2u>& to_remove) {
    for (sf::Vector2u cords : to_remove) {
        if (m_tiles.at((cords.x - 1) * (m_size - 2) + (cords.y - 1))->hasPiece()) {
            m_tiles.at((cords.x - 1) * (m_size - 2) + (cords.y - 1))->removePiece().reset();
        }
    }
}

sf::Vector2u Board::getTileCords(const sf::Vector2f& cords) {
    for (std::size_t i = 0; i < m_tiles.size(); i++) {
        if (m_tiles[i]->contains(cords)) {
            return sf::Vector2u((int)i / (int)std::sqrt(m_tiles.size()) + 1, (int)i % (int)std::sqrt(m_tiles.size()) + 1);
        }
    }
    return sf::Vector2u(0, 0);
}

void Board::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (int i = 0; i < m_tiles.size(); i++) {
        m_tiles.at(i)->draw(target, states);
    }
    for (int i = 0; i < m_corners.size(); i++) {
        m_corners.at(i)->draw(target, states);
    }
    for (int i = 0; i < m_borders.size(); i++) {
        m_borders.at(i)->draw(target, states);
    }
}

std::vector<std::unique_ptr<CornerTile>> Board::createCorners() {
    std::vector<std::unique_ptr<CornerTile>> corners;
    sf::Vector2f position;
    for (unsigned int i = 0; i < 4; i++) {
        position = sf::Vector2f(m_offset.x + (i / 2) * (m_size - 1) * m_tile_size, m_offset.y + (i % 2) * (m_size - 1) * m_tile_size);
        corners.push_back(std::make_unique<CornerTile>(m_tile_size, position));
    }
    return corners;
}

std::vector<std::unique_ptr<BorderTile>> Board::createBorders() {
    std::vector<std::unique_ptr<BorderTile>> borders;
    sf::Vector2f position_ver;
    sf::Vector2f position_hor;
    std::array<char, 12> signs;
    for (int i = 0; i < 9; i++) {
        signs.at(i) = '1' + i;
    }
    signs[9] = 'X';
    signs[10] = 'Y';
    signs[11] = 'Z';
    for (unsigned int i = 0; i < 2; i++) { // Clockwise: Row, Col, Row, Col
        for (unsigned int j = 1; j < m_size - 1; j++) {
            position_ver = sf::Vector2f(m_offset.x + (i % 2) * (m_size - 1) * m_tile_size,  m_offset.y + j * m_tile_size);
            position_hor = sf::Vector2f(m_offset.x + j * m_tile_size, m_offset.y + (i % 2) * (m_size - 1) * m_tile_size);
            borders.push_back(std::make_unique<BorderTile>(m_tile_size, position_ver, signs[j - 1]));
            borders.push_back(std::make_unique<BorderTile>(m_tile_size, position_hor, 'A' + j - 1));
        }
    }
    return borders;
}

std::vector<std::unique_ptr<MainTile>> Board::createMainTiles() {
    std::vector<std::unique_ptr<MainTile>> main_tiles;
    sf::Vector2f position;
    for (unsigned int row = 1; row < m_size - 1; row++) {
        for (unsigned int col = 1; col < m_size - 1; col++) {
            position = sf::Vector2f(m_offset.x + row * m_tile_size, m_offset.y + col * m_tile_size);
            main_tiles.push_back(std::make_unique<MainTile>(m_tile_size, position, (row + col) % 2));
        }
    }
    return main_tiles;
}

std::vector<std::unique_ptr<Piece>> Board::createPieces() {
    std::vector<std::unique_ptr<Piece>> pieces;
    for (unsigned int i = 0; i < m_piece_count; i++) {
        pieces.push_back(std::make_unique<Piece>(m_tile_size / 2.f, Piece::Type::Man, i < m_piece_count / 2 ? Team::White : Team::Black));
    }
    return pieces;
}

void Board::placePieces(std::vector<std::unique_ptr<Piece>> pieces) {
    std::size_t row = 0;
    std::size_t col = 0;
    std::size_t piece_count = pieces.size();
    bool flag = true;
    while (pieces.size() > 0) {
        if (flag && pieces.size() <= piece_count / 2) {
            row += ((m_size - 2) * (m_size - 2) - piece_count * 2) / (m_size - 2);
            flag = false;
        }
        m_tiles.at(col * (m_size - 2) + row)->placePiece(std::move(pieces.at(pieces.size() - 1)));
        //std::cout << "PLACEING PIECES " << (pieces.at(pieces.size() - 1) != nullptr) << std::endl;
        pieces.pop_back();
        col += 2;
        if (col >= m_size - 2) {
            row += 1;
            col = row % 2;
        }
    }
}