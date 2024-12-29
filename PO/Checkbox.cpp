#include <SFML/Graphics.hpp>

#include "Checkable.h"
#include "Checkbox.h"

Checkbox::Checkbox(const std::string& label) {
    m_checked = false;

    m_square = sf::RectangleShape();
    m_square.setSize(sf::Vector2f(18.f, 18.f));
    m_square.setOutlineThickness(2.f);
    m_square.setFillColor(sf::Color::White);
    m_square.setOutlineColor(sf::Color::Black);

    m_font = sf::Font();
    m_font.loadFromFile("ariblk.ttf");

    m_text = sf::Text();
    m_text.setFont(m_font);
    m_text.setCharacterSize(24);
    m_text.setFillColor(sf::Color::Yellow);
    m_text.setString(label);
}

Checkbox::~Checkbox() {
}

sf::Vector2f Checkbox::getOptionCount() {
    sf::Vector2f size(m_text.getGlobalBounds().getSize());
    size.x += m_square.getSize().x + 2 * m_square.getOutlineThickness();
    return size;
}

void Checkbox::setPosition(const sf::Vector2f& position) {
    sf::Vector2f square_position(position);
    sf::Vector2f text_position(position);
    square_position.y += (m_text.getGlobalBounds().getSize().y - m_square.getSize().y - m_square.getOutlineThickness());
    square_position.x += m_square.getOutlineThickness();
    text_position.x += m_square.getSize().x + 2 * m_square.getOutlineThickness();
    m_square.setPosition(square_position);
    m_text.setPosition(text_position);
    m_text.setOrigin(m_text.getLocalBounds().getPosition());
}

sf::Vector2f Checkbox::getPosition() {
    return sf::Vector2f(m_square.getPosition().x - m_square.getOutlineThickness(), m_text.getGlobalBounds().getPosition().y);
}

bool Checkbox::contains(const sf::Vector2f& cords) {
    return m_square.getGlobalBounds().contains(cords) || m_text.getGlobalBounds().contains(cords);
}

void Checkbox::check() {
    m_checked = true;
    m_square.setFillColor(sf::Color(0, 192, 255));
}

void Checkbox::uncheck() {
    m_checked = false;
    m_square.setFillColor(sf::Color::White);
}

bool Checkbox::isChecked() const {
    return m_checked;
}

void Checkbox::onClick(const sf::RenderWindow& window, const sf::Event& event) {
    sf::Vector2f cords(sf::Mouse::getPosition(window));
    if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left && contains(cords)) {
        if (isChecked()) {
            uncheck();
        }
        else {
            check();
        }
    }
}

void Checkbox::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    sf::RectangleShape text_box(m_text.getGlobalBounds().getSize());
    text_box.setPosition(m_text.getGlobalBounds().getPosition());
    text_box.setFillColor(sf::Color::Magenta);
    target.draw(m_square, states);
    target.draw(text_box, states);
    target.draw(m_text, states);
}