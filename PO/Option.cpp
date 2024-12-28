#include <SFML/Graphics.hpp>

#include "Radio.h"
#include "Option.h"

Radio::Option::Option(Radio& radio, const std::string label) : m_radio(radio) {
    m_enabled = true;

    m_circle = sf::CircleShape();
    m_circle.setRadius(9);
    m_circle.setFillColor(sf::Color::White);
    m_circle.setOutlineColor(sf::Color::Black);
    m_circle.setOutlineThickness(0.f);

    m_font = sf::Font();
    m_font.loadFromFile("ariblk.ttf");

    m_text = sf::Text();
    m_text.setFont(m_font);
    m_text.setCharacterSize(24);
    m_text.setFillColor(sf::Color::Black);
    m_text.setString(label);
}

Radio::Option::~Option() {
}

sf::Vector2f Radio::Option::getSize() {
    sf::Vector2f size = m_text.getLocalBounds().getSize();
    size.x += 2 * (m_circle.getRadius() + m_circle.getOutlineThickness() + 2 * m_text.getLetterSpacing());
    return size;
}

void Radio::Option::setPosition(sf::Vector2f& position) {
    m_circle.setPosition(position);
    sf::Vector2f text_position = position;
    text_position.x += 2 * (m_circle.getRadius() + m_circle.getOutlineThickness());
    m_text.setPosition(text_position);
}

sf::Vector2f Radio::Option::getPosition() {
    return m_circle.getPosition();
}

bool Radio::Option::contains(const sf::Vector2f& cords) {
    return m_circle.getGlobalBounds().contains(cords) || m_text.getGlobalBounds().contains(cords);
}

void Radio::Option::enable() {
    m_enabled = true;
}

void Radio::Option::disable() {
    m_enabled = false;
}

bool Radio::Option::isEnabled() const {
    return m_enabled;
}

void Radio::Option::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_circle, states);
    target.draw(m_text, states);
}