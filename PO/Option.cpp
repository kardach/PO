#include <SFML/Graphics.hpp>

#include "Checkable.h"
#include "Radio.h"
#include "Option.h"

Radio::Option::Option(Radio& radio, const std::string label) : m_radio(radio) {
    m_enabled = true;

    m_checked = false;

    m_circle = sf::CircleShape();
    m_circle.setRadius(9);
    m_circle.setFillColor(sf::Color::White);
    m_circle.setOutlineColor(sf::Color::Black);
    m_circle.setOutlineThickness(2.f);

    m_font = sf::Font();
    m_font.loadFromFile("ariblk.ttf");

    m_text = sf::Text();
    m_text.setFont(m_font);
    m_text.setCharacterSize(24);
    m_text.setFillColor(sf::Color::Yellow);
    m_text.setString(label);
}

Radio::Option::~Option() {
}

sf::Vector2f Radio::Option::getSize() {
    sf::Vector2f size = m_text.getGlobalBounds().getSize();
    size.x += 2 * (m_circle.getRadius() + m_circle.getOutlineThickness());
    return size;
}

void Radio::Option::setPosition(const sf::Vector2f& position) {
    sf::Vector2f text_position = position;
    text_position.x += 2 * (m_circle.getRadius() + m_circle.getOutlineThickness());
    sf::Vector2f circle_position = position;
    circle_position.y += m_text.getGlobalBounds().getSize().y - m_circle.getRadius() * 2 - m_circle.getOutlineThickness();
    circle_position.x += m_circle.getOutlineThickness();
    m_circle.setPosition(circle_position);
    m_text.setPosition(text_position);
    m_text.setOrigin(m_text.getLocalBounds().getPosition());
}

sf::Vector2f Radio::Option::getPosition() {
    return sf::Vector2f(m_circle.getPosition().x - m_circle.getOutlineThickness(), m_text.getPosition().y);
}

bool Radio::Option::contains(const sf::Vector2f& cords) {
    return m_circle.getGlobalBounds().contains(cords) || m_text.getGlobalBounds().contains(cords);
}

void Radio::Option::enable() {
    m_enabled = true;
    if (isChecked()) {
        m_circle.setFillColor(sf::Color(0, 192, 255));
        m_text.setFillColor(sf::Color::Yellow);
    }
    else {
        m_circle.setFillColor(sf::Color::White);
        m_text.setFillColor(sf::Color::Yellow);
    }
}

void Radio::Option::disable() {
    m_enabled = false;
    m_circle.setFillColor(sf::Color(192, 192, 192));
    m_text.setFillColor(sf::Color(128, 128, 128));
}

bool Radio::Option::isEnabled() const {
    return m_enabled;
}

void Radio::Option::check() {
    m_checked = true;
    m_circle.setFillColor(sf::Color(0, 192, 255));
}

void Radio::Option::uncheck() {
    m_checked = false;
    m_circle.setFillColor(sf::Color::White);
}

bool Radio::Option::isChecked() const {
    return m_checked;
}

void Radio::Option::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_circle, states);
    sf::RectangleShape text_box(m_text.getGlobalBounds().getSize());
    text_box.setPosition(m_text.getGlobalBounds().getPosition());
    text_box.setFillColor(sf::Color::Magenta);
    target.draw(text_box, states);
    target.draw(m_text, states);
}