#pragma once

#ifndef BOARD_H_
#define BOARD_H_

#include "Settings.h"
#include "Tiles.h"

class Board : public sf::Drawable {
private:
    unsigned int m_size;

    unsigned int m_piece_count;

    float m_tile_size;

    sf::Vector2f m_offset;

    std::vector<std::shared_ptr<Tile>> m_tiles;

public:
    Board(const sf::Vector2u&, const Settings&);

    ~Board();

    float getTileSize() const;

    sf::Vector2f getOffset() const;

    void draw(sf::RenderTarget&, sf::RenderStates) const;
private:
    static std::vector<std::shared_ptr<Tile>> createBoard(const unsigned int, const sf::Vector2f&, const float);
};

#endif // BOARD_H_