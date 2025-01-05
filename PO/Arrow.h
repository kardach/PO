#pragma once

#ifndef ARROW_H_
#define ARROW_H_

class Arrow : public sf::Drawable {
private:
    sf::CircleShape m_head;

    sf::RectangleShape m_shaft;

    sf::Vector2f m_from;

    sf::Vector2f m_to;
public:
    Arrow(const sf::Vector2f&, const sf::Vector2f&);

    ~Arrow();

    void setThickness(float);

    void setHeadSize(float);

    void draw(sf::RenderTarget&, sf::RenderStates) const override;
};

#endif // ARROW_H_