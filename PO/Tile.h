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

    bool contains(const sf::Vector2f&);
};

#endif // TILES_H_