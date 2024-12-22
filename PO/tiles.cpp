#include <SFML/Graphics.hpp>

#include "Piece.h"
#include "Tiles.h"

Tile::Tile(const float size, const sf::Vector2f& position, const sf::Color& color) {
    m_rectangle = sf::RectangleShape(sf::Vector2f(size, size));
    m_rectangle.setPosition(position);
    m_rectangle.setFillColor(color);
}

Tile::~Tile() {
}

void Tile::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(m_rectangle, states);
}

CornerTile::CornerTile(const float size, const sf::Vector2f& position)
    : Tile(size, position, sf::Color(222, 184, 135)) {
}

CornerTile::~CornerTile() {
}

void CornerTile::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    Tile::draw(target, states);
}

BorderTile::BorderTile(const float size, const sf::Vector2f& position, const char sign)
    : Tile(size, position, sf::Color(222, 184, 135)) {
    sf::Font font; // fix this
    font.loadFromFile("ariblk.ttf"); // fix this, multiple load

    m_sign = sf::Text();
    m_sign.setFont(font);
    m_sign.setCharacterSize(24);
    m_sign.setFillColor(sf::Color(128, 0, 0));
    m_sign.setString(sign);

    sf::FloatRect text_rect = m_sign.getLocalBounds();
    m_sign.setOrigin(text_rect.left + text_rect.width / 2.f,text_rect.top + text_rect.height / 2.f);
    m_sign.setPosition(sf::Vector2f(800 / 2.f, 600 / 2.f)); // fix this, value from outer scope
}
BorderTile::~BorderTile() {
}
void BorderTile::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    Tile::draw(target, states);
    //target.draw(m_sign, states);
}
MainTile::MainTile(const float size, const sf::Vector2f& position, const bool team)
    : Tile(size, position, team ? sf::Color(255, 228, 196) : sf::Color(139, 69, 19)) {
    //m_piece = nullptr;
}
MainTile::~MainTile() {
}
void MainTile::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    Tile::draw(target, states);
    /*if (m_piece != nullptr) {
        m_piece->draw(target, states);
    }*/
}
//void MainTile::placePiece(const Piece& piece) {
//    m_piece = &piece;
//}
//const bool MainTile::hasPiece() {
//    return m_piece != nullptr;
//}
//const Piece* MainTile::removePiece() {
//    const Piece* temp = m_piece;
//    m_piece = nullptr;
//    return temp;
//}