#pragma once

#ifndef CHECKBOX_H_
#define CHECKBOX_H_

#include "Checkable.h"

class Checkbox : public sf::Drawable, public Checkable {
private:
    sf::RectangleShape m_square;

    sf::Font m_font;

    sf::Text m_text;

    bool m_checked;
public:
    Checkbox(const std::string&);

    ~Checkbox();

    sf::Vector2f getOptionCount();

    void setPosition(const sf::Vector2f&);

    sf::Vector2f getPosition();

    bool contains(const sf::Vector2f&);

    void check() override;

    void uncheck() override;

    bool isChecked() const override;

    void onClick(const sf::RenderWindow&, const sf::Event&);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif // CHECKBOX_H_