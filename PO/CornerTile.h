#pragma once

#ifndef CORNERTILE_H_
#define CORNERTILE_H_

class CornerTile : public Tile {
public:
    CornerTile(const float, const sf::Vector2f&);

    ~CornerTile();

    void draw(sf::RenderTarget&, sf::RenderStates) const override;
};

#endif // CORNERTILE_H_