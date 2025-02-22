#pragma once

#ifndef MAINTILE_H_
#define MAINTILE_H_

#include "Tile.h"

class Piece;

class MainTile : public Tile {
private:
    std::unique_ptr<Piece> m_piece;
public:
    MainTile(const float, const sf::Vector2f&, const bool);

    ~MainTile();

    void draw(sf::RenderTarget&, sf::RenderStates) const override;

    void placePiece(std::unique_ptr<Piece>);

    const bool hasPiece() const;

    const Piece* getPiece() const;

    std::unique_ptr<Piece> removePiece();
};

#endif // MAINTILE_H_