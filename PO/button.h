#pragma once

#ifndef BUTTON_H_
#define BUTTON_H_

class Button : public sf::Drawable {
private:
    RoundedRectangle m_round_rect;
    sf::Font m_font;
    sf::Text m_text;
public:
    Button();

    ~Button();

    void setSize(const sf::Vector2f&);

    void setPosition(const sf::Vector2f&);

    void setFillColor(const sf::Color&);

    void setTextColor(const sf::Color&);

    void setString(const std::string&);

    bool contains(const sf::Vector2f&);

    void draw(sf::RenderTarget&, sf::RenderStates) const override;
private:
    void centerText();
};

#endif // BUTTON_H_