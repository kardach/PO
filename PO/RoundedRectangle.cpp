#include <SFML/Graphics.hpp>

#include "RoundedRectangle.h"

#include <iostream>

RoundedRectangle::RoundedRectangle()
    : m_size(), m_roundness() {
    update();
}

RoundedRectangle::RoundedRectangle(const sf::Vector2f& size, const float roundness)
    : m_size(size), m_roundness(std::min(roundness, 1.0f)) {
    update();
}

RoundedRectangle::~RoundedRectangle() {
}

void RoundedRectangle::setRoundness(const float roundness) {
    m_roundness = roundness;
    update();
}

const float RoundedRectangle::getRoundness() const {
    return m_roundness;
}

void RoundedRectangle::setSize(const sf::Vector2f& size) {
    m_size = size;
    update();
}

const sf::Vector2f& RoundedRectangle::getSize() const {
    return m_size;
}

std::size_t RoundedRectangle::getPointCount() const {
    return 32;
}

sf::Vector2f RoundedRectangle::getPoint(std::size_t index) const {
    static const float pi = 3.141592654f;

    float angle = (index - index / 8) * 2 * pi / (getPointCount() - 4) - pi;
    float x = std::cos(angle) * m_roundness / 2;
    float y = std::sin(angle) * m_roundness / 2;
    float radius = std::min(m_size.x, m_size.y) * m_roundness / 2;

    sf::Vector2f cords(std::min(m_size.x, m_size.y) * x + radius, std::min(m_size.x, m_size.y) * y + radius);
    // top left corner
    if (index >= 0 && index < 8) {
        return sf::Vector2f(cords.x, cords.y);
    }
    // top right corner
    else if (index >= 8 && index < 16) {
        return sf::Vector2f(m_size.x - 2 * radius + cords.x, cords.y);
    }
    // bottom right corner
    else if (index >= 16 && index < 24) {
        return sf::Vector2f(m_size.x - 2 * radius + cords.x, m_size.y - 2 * radius + cords.y);
    }
    // bottom left corner
    else if (index >= 24 && index < 32) {
        return sf::Vector2f(cords.x, m_size.y - 2 * radius + cords.y);
    }
    else {
        return sf::Vector2f(0.f, 0.f);
    }
}