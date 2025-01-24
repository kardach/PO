#pragma once

#ifndef BOARD_H_
#define BOARD_H_

enum class Team : bool;
class Settings;
class CornerTile;
class BorderTile;
class MainTile;
class Piece;
class Move;

class Board : public sf::Drawable {
private:
    unsigned int m_size;

    unsigned int m_piece_count;

    float m_tile_size;

    sf::Vector2f m_offset;

    std::vector<std::unique_ptr<CornerTile>> m_corners;

    std::vector<std::unique_ptr<BorderTile>> m_borders;

    std::vector<std::unique_ptr<MainTile>> m_tiles;

public:
    Board(const Settings&);

    ~Board();

    float getTileSize() const;

    sf::Vector2f getOffset() const;

    bool onClick(const sf::RenderWindow&, const sf::Event&);

    sf::Vector2u getTileCords(const sf::Vector2f&);

    const MainTile* at(const sf::Vector2u&) const;

    void makeMove(std::vector<Move>&);

    void penaltyRemove(std::vector<sf::Vector2u>&);

    //bool hasPiece(const sf::Vector2u&, const Team&) const;

    void draw(sf::RenderTarget&, sf::RenderStates) const;
private:
    std::vector<std::unique_ptr<CornerTile>> createCorners();

    std::vector<std::unique_ptr<BorderTile>> createBorders();

    std::vector<std::unique_ptr<MainTile>> createMainTiles();

    std::vector<std::unique_ptr<Piece>> createPieces();

    void placePieces(std::vector<std::unique_ptr<Piece>>);
};

#endif // BOARD_H_