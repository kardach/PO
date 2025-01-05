#pragma once

#ifndef MOVEDEPICTION_H_
#define MOVEDEPICTION_H_

class Settings;
class Board;
class Move;
class Arrow;

class MoveDepiction : public sf::Drawable {
private:
    sf::Vector2f m_offset;

    float m_tile_size;

    unsigned int m_board_size;

    std::vector<Arrow> m_arrows;
public:
    MoveDepiction(const Settings&, const Board&);

    ~MoveDepiction();

    void update(std::vector<Move>&);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif // MOVEDEPICTION_H_