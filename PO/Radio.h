#pragma once

#ifndef RADIO_H_
#define RADIOH_

class Radio : public sf::Drawable {
private:    
    class Option;

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

    void unselect();

    void enable(const std::string&);

    void disable(const std::string&);

    bool isEnabled(const std::string&) const;

    bool onClick(const sf::RenderWindow&, const sf::Event&);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif // RADIO_H_