#pragma once

#ifndef BOARD_H_
#define BOARD_H_

enum class Team : bool;
class Settings;
class Tile;
class Piece;

class Board : public sf::Drawable {
private:
    unsigned int m_size;

    unsigned int m_piece_count;

    float m_tile_size;

    sf::Vector2f m_offset;

    std::vector<std::shared_ptr<Tile>> m_tiles;

public:
    Board(const Settings&);

    ~Board();

    float getTileSize() const;

    sf::Vector2f getOffset() const;

    bool onClick(const sf::RenderWindow&, const sf::Event&);

    sf::Vector2i getTileCords(const sf::Vector2f&);

    bool hasPiece(const sf::Vector2u&, const Team&);

    void draw(sf::RenderTarget&, sf::RenderStates) const;
private:
    std::vector<std::shared_ptr<Tile>> createBoard(const unsigned int, const sf::Vector2f&, const float);

    std::vector<std::unique_ptr<Piece>> createPieces(const unsigned int, const float);

    void placePieces(const unsigned int, std::vector<std::shared_ptr<Tile>>, std::vector<std::unique_ptr<Piece>>&);
};

#endif // BOARD_H_