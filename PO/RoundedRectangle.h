#pragma once

#ifndef ROUNDEDRECTANGLE_H_
#define ROUNDEDRECTANGLE_H_

class RoundedRectangle : public sf::Shape {
private:
    sf::Vector2f m_size;

    float m_roundness;
public:
    explicit RoundedRectangle();

    explicit RoundedRectangle(const sf::Vector2f&, const float);

    ~RoundedRectangle();
    
    void setRoundness(const float);

    const float getRoundness() const;

    void setSize(const sf::Vector2f&);

    const sf::Vector2f& getSize() const;

    virtual std::size_t getPointCount() const;

    virtual sf::Vector2f getPoint(std::size_t) const;
};

#endif // ROUNDEDRECTANGLE_H_