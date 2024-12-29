#pragma once

//#include "Option.h"

#ifndef RADIO_H_
#define RADIOH_

class Radio : public sf::Drawable {
public:    
    class Option;
private:
    sf::Vector2f m_position;

    std::size_t m_selected;

    std::vector<std::string> m_names;

    std::map<std::string, std::unique_ptr<Option>> m_options;
public:
    Radio();

    ~Radio();

    void addOption(const std::string&, const std::string&);  // CAN ADD SAME TWICE

    const std::size_t getOptionCount() const;

    const std::vector<std::string> getNames() const;

    void setPosition(const sf::Vector2f&);

    const sf::Vector2f getPosition() const;

    const sf::Vector2f getSize() const;

    const std::string selected(); // UNSELECTED ERROR

    void enable(const std::string&);

    void disable(const std::string&);

    bool isEnabled(const std::string&) const;

    bool onClick(const sf::RenderWindow&, const sf::Event&);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

//class Radio::Option : public sf::Drawable {
//private:
//    Radio& m_radio;
//
//    sf::CircleShape m_circle;
//
//    sf::Font m_font;
//
//    sf::Text m_text;
//
//    bool m_enabled;
//public:
//    Option(Radio&, const std::string);
//
//    ~Option();
//
//    sf::Vector2f getSize();
//
//    void setPosition(sf::Vector2f&);
//
//    sf::Vector2f getPosition();
//
//    bool contains(const sf::Vector2f&);
//
//    void enable();
//
//    void disable();
//
//    bool isEnabled() const;
//
//    void draw(sf::RenderTarget&, sf::RenderStates) const;
//};

#endif // RADIO_H_