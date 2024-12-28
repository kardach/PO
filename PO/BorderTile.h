#pragma once

#ifndef BORDERTILE_H_
#define BORDERTILE_H_

class BorderTile : public Tile {
private:
    sf::Font m_font;

    sf::Text m_text;
public:
    BorderTile(const float, const sf::Vector2f&, const char);

    ~BorderTile();

    void draw(sf::RenderTarget&, sf::RenderStates) const override;
};

#endif // BORDERILE_H_