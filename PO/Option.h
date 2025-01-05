#pragma once

#ifndef OPTION_H_
#define OPTION_H_

#include "Checkable.h"

class Radio::Option : public sf::Drawable, public Checkable {
private:
    Radio& m_radio;

    sf::CircleShape m_circle;

    sf::Font m_font;

    sf::Text m_text;

    bool m_enabled;

    bool m_checked;
public:
    Option(Radio&, const std::string);

    ~Option();

    sf::Vector2f getSize();

    void setPosition(const sf::Vector2f&);

    sf::Vector2f getPosition();

    bool contains(const sf::Vector2f&);

    void enable();

    void disable();

    bool isEnabled() const;

    void check() override;

    void uncheck() override;

    bool isChecked() const override;

    void draw(sf::RenderTarget&, sf::RenderStates) const;
};

#endif // OPTION_H_