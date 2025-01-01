#include <SFML/Graphics.hpp>

#include "Settings.h"
#include "Tile.h"
#include "CornerTile.h"
#include "BorderTile.h"
#include "MainTile.h"
#include "Board.h"

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
    m_tiles = createBoard(m_size, m_offset, m_tile_size);
    std::vector<std::shared_ptr<Piece>> pieces = createPieces(m_piece_count, m_tile_size / 2.f);
    placePieces(m_size, m_tiles, pieces);
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

sf::Vector2i Board::getTileCords(const sf::Vector2f& cords) {
    for (std::size_t i = 0; i < m_tiles.size(); i++) {
        if (m_tiles[i]->contains(cords)) {
            return sf::Vector2i(i / m_size, i % m_size);
        }
    }
    return sf::Vector2i(-1, -1);
}

void Board::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (int i = 0; i < m_tiles.size(); i++) {
        m_tiles.at(i)->draw(target, states);
    }
}

std::vector<std::shared_ptr<Tile>> Board::createBoard(const unsigned int size, const sf::Vector2f& offset, const float tile_size) {
    std::vector<std::shared_ptr<Tile>> Tiles;

    for (unsigned int row = 0; row < size; row++) {
        for (unsigned int col = 0; col < size; col++) {
            sf::Vector2f position(offset.x + row * tile_size, offset.y + col * tile_size);
            //inner tiles
            if (row != 0 && row != size - 1 && col != 0 && col != size - 1) {
                Tiles.push_back(std::make_shared<MainTile>(tile_size, position, (row + col) % 2));
            }
            //left and right board border
            else if (row != 0 && row != size - 1 && (col == 0 || col == size - 1)) {
                Tiles.push_back(std::make_shared<BorderTile>(tile_size, position, 'a' + row - 1));
            }
            //top and bottom board border
            else if ((row == 0 || row == size - 1) && col != 0 && col != size - 1) {
                Tiles.push_back(std::make_shared<BorderTile>(tile_size, position, '1' + col - 1));
            }
            //corners
            else {
                Tiles.push_back(std::make_shared<CornerTile>(tile_size, position));
            }
        }
    }
    return Tiles;
}

std::vector<std::shared_ptr<Piece>> Board::createPieces(const unsigned int piece_count, const float radius) {
    std::vector<std::shared_ptr<Piece>> pieces;

    for (unsigned int i = 0; i < piece_count; i++) {
        pieces.push_back(std::make_shared<Piece>(radius, Piece::Type::Man, i < piece_count / 2 ? Piece::Team::White : Piece::Team::Black));
    }

    return pieces;
}

void Board::placePieces(const unsigned int size, std::vector<std::shared_ptr<Tile>> tiles, std::vector<std::shared_ptr<Piece>> pieces) {
    std::size_t row = 1;
    std::size_t col = 1;
    std::size_t piece_count = pieces.size();
    bool flag = true;
    while (pieces.size() > 0) {
        if (flag && pieces.size() <= piece_count / 2) {
            row += ((size - 2) * (size - 2) - piece_count * 2) / (size - 2);
            flag = false;
        }
        std::dynamic_pointer_cast<MainTile>(tiles.at(col * size + row))->placePiece(pieces.at(pieces.size() - 1));
        pieces.pop_back();
        col += 2;
        if (col >= size - 1) {
            row += 1;
            col = (row - 1) % 2 + 1;
        }
    }

}