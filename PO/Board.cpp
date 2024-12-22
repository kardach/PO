#include <SFML/Graphics.hpp>

#include "Settings.h"
#include "Board.h"
#include "Piece.h"
#include "Tiles.h"

Board::Board(const sf::Vector2u& window_dimensions, const Settings& settings) {
    m_size = settings.getBoardSize();
    m_piece_count = settings.getPieceCount();

    float window_heigth = (float)window_dimensions.y;
    float window_width = (float)window_dimensions.x;

    m_tile_size = ((window_heigth < window_width) ? window_heigth : window_width) / m_size;

    float x_offset = (window_heigth < window_width) ? (window_width - m_size * m_tile_size) / 2 : 0;
    float y_offset = (window_heigth < window_width) ? 0 : (window_width - m_size * m_tile_size) / 2;
    m_offset = sf::Vector2f(x_offset, y_offset);
    m_tiles = createBoard(m_size, m_offset, m_tile_size);
}

Board::~Board() {
}

float Board::getTileSize() const {
    return m_tile_size;
}

sf::Vector2f Board::getOffset() const {
    return m_offset;
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
                Tiles.push_back(std::make_shared<BorderTile>(tile_size, position, '0' + col - 1));
            }
            //corners
            else {
                Tiles.push_back(std::make_shared<CornerTile>(tile_size, position));
            }
        }
    }
    return Tiles;
}