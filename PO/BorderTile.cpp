#include <SFML/Graphics.hpp>

#include "Tile.h"
#include "BorderTile.h"

BorderTile::BorderTile(const float size, const sf::Vector2f& position, const char sign)
    : Tile(size, position, sf::Color(222, 184, 135)) {
    m_font = sf::Font();
    m_font.loadFromFile("ariblk.ttf");

    std::string text = { '|', sign, '|' };

    m_text = sf::Text();
    m_text.setFont(m_font);
    m_text.setCharacterSize(24);
    m_text.setFillColor(sf::Color(128, 0, 0));
    m_text.setString(text);

    sf::FloatRect text_rect = m_text.getLocalBounds();
    m_text.setOrigin(text_rect.left + text_rect.width / 2.f, text_rect.top + text_rect.height / 2.f);
    m_text.setPosition(sf::Vector2f(m_rectangle.getPosition().x + m_rectangle.getSize().x / 2.f,
        m_rectangle.getPosition().y + m_rectangle.getSize().y / 2.f));
}

BorderTile::~BorderTile() {
}

void BorderTile::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    Tile::draw(target, states);
    states.transform *= getTransform();
    target.draw(m_text, states);
}