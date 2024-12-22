#pragma once

#ifndef TILES_H
#define TILES_H

#include "Piece.h"

class Tile : public sf::Transformable, public sf::Drawable {
protected:
    sf::RectangleShape m_rectangle;
public:
    Tile(const float, const sf::Vector2f&, const sf::Color&);

    virtual ~Tile();

    virtual void draw(sf::RenderTarget&, sf::RenderStates) const = 0;
};

class CornerTile : public Tile {
public:
    CornerTile(const float, const sf::Vector2f&);

    ~CornerTile();

    virtual void draw(sf::RenderTarget&, sf::RenderStates) const override;
};

class BorderTile : public Tile {
private:
    sf::Text m_sign;
public:
    BorderTile(const float, const sf::Vector2f&, const char);
    ~BorderTile();
    virtual void draw(sf::RenderTarget&, sf::RenderStates) const override;
};

class MainTile : public Tile {
private:
    //Piece* m_piece;
public:
    MainTile(const float, const sf::Vector2f&, const bool);
    ~MainTile();
    virtual void draw(sf::RenderTarget&, sf::RenderStates) const override;
    //void placePiece(const Piece&);
    //const bool hasPiece();
    //const Piece* removePiece();
};

#endif // TILES_H_