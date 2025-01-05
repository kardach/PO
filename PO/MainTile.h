#pragma once

#include "Piece.h"

#ifndef MAINTILE_H_
#define MAINTILE_H_

class MainTile : public Tile {
private:
    std::unique_ptr<Piece> m_piece;
public:
    MainTile(const float, const sf::Vector2f&, const bool);

    ~MainTile();

    void draw(sf::RenderTarget&, sf::RenderStates) const override;

    void placePiece(std::unique_ptr<Piece>);

    const bool hasPiece() const;

    std::unique_ptr<Piece> removePiece();
};

#endif // MAINTILE_H_