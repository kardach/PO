#include <SFML/Graphics.hpp>

#include "arrow.h"

Arrow::Arrow(const sf::Vector2f& from, const sf::Vector2f& to) {
    m_from = from;
    m_to = to;
    float delta_x = to.x - from.x;
    float delta_y = to.y - from.y;
    static const float pi = 3.141592654f;
    float length = std::sqrt(std::pow(delta_x, 2.f) + std::pow(delta_y, 2.f));
    float radians = std::atan(delta_y / delta_x);
    float angle = radians * 180.f / pi;

    float head_x = (length - 20.f) * std::cos(radians) * (delta_x < 0 ? -1.f : 1.f);
    float head_y = (length - 20.f) * std::sin(radians) * (delta_x < 0 ? -1.f : 1.f);

    m_head = sf::CircleShape();
    m_head.setPosition(sf::Vector2f(from.x + head_x, from.y + head_y));
    m_head.setPointCount(3);
    m_head.setRadius(20.f);
    m_head.setOrigin(sf::Vector2f(20.f, 20.f));
    m_head.setFillColor(sf::Color(255, 0, 0, 192));
    m_head.rotate((delta_x < 0 ? -90.f : 90.f) + angle);

    m_shaft = sf::RectangleShape();
    m_shaft.setPosition(from);
    m_shaft.setSize(sf::Vector2f(20.f, length - 10.f - 20.f));
    m_shaft.setOrigin(sf::Vector2f(10.f, 0.f));
    m_shaft.setFillColor(sf::Color(255, 0, 0, 192));
    m_shaft.rotate((delta_x < 0 ? 90.f : -90.f) + angle);
}

Arrow::~Arrow() {
}

void Arrow::setThickness(float thickness) {
    sf::Vector2f size = m_shaft.getSize();
    size.x = thickness;
    m_shaft.setSize(size);
    m_shaft.setOrigin(sf::Vector2f(thickness / 2, 0.f));
}

void Arrow::setHeadSize(float radius) {
    sf::Vector2f size = m_shaft.getSize();
    float delta_x = m_to.x - m_from.x;
    float delta_y = m_to.y - m_from.y;
    float radians = std::atan(delta_y / delta_x);
    float length = std::sqrt(std::pow(delta_x, 2.f) + std::pow(delta_y, 2.f));
    size.y = length - 1.5f * radius;
    float head_x = (length - radius) * std::cos(radians) * (delta_x < 0 ? -1.f : 1.f);
    float head_y = (length - radius) * std::sin(radians) * (delta_x < 0 ? -1.f : 1.f);

    m_head.setPosition(sf::Vector2f(m_from.x + head_x, m_from.y + head_y));
    m_head.setRadius(radius);
    m_head.setOrigin(sf::Vector2f(radius, radius));

    m_shaft.setSize(size);
}

void Arrow::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_head, states);
    target.draw(m_shaft, states);
}