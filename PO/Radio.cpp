#include <SFML/Graphics.hpp>

#include "Radio.h"
#include "Option.h"

Radio::Radio()
    : m_selected(m_names.size()) {
}

Radio::~Radio() {
}

void Radio::addOption(const std::string& name, const std::string& label) {
    sf::Vector2f position;
    if (m_names.size() == 0) {
        position = m_position;
    }
    else {
        Radio::Option last_option = *m_options.at(m_names.at(m_names.size() - 1));
        position = last_option.getPosition();
        position.x += last_option.getSize().x;
    }
    m_names.push_back(name);
    m_options.emplace(name, std::make_unique<Option>(*this, label));
    m_options.at(name)->setPosition(position);
    m_selected = m_names.size();
}

void Radio::setPosition(const sf::Vector2f& position) {
    m_position = position;
    sf::Vector2f option_position;
    for (std::string name : m_names) {
        option_position = m_options.at(name)->getPosition();
        option_position += position;
        m_options.at(name)->setPosition(option_position);
    }
}

const std::size_t Radio::getSize() const {
    return m_options.size();
}

const std::vector<std::string> Radio::getNames() const {
    return m_names;
}

Radio::Option Radio::option(const std::string& name) {
    return *m_options.at(name);
}

Radio::Option Radio::operator[](const std::string& name) {
    return *m_options.at(name);
}

void Radio::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (std::string name : m_names) {
        m_options.at(name)->draw(target, states);
    }
}