#include <SFML/Graphics.hpp>

#include "Radio.h"
#include "Option.h"

Radio::Radio()
    : m_selected(m_names.size()) {
    m_position = sf::Vector2f();
}

Radio::~Radio() {
}

void Radio::addOption(const std::string& name, const std::string& label) { // CAN ADD SAME TWICE
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

const sf::Vector2f Radio::getPosition() const {
    return m_position;
}

const std::size_t Radio::getOptionCount() const {
    return m_options.size();
}

const sf::Vector2f Radio::getSize() const{
    sf::Vector2f size;
    for (const std::string name : m_names) {
        size += m_options.at(name)->getSize();
    }
    return size;
}

const std::vector<std::string> Radio::getNames() const {
    return m_names;
}

const std::string Radio::selected() { // UNSELECTED ERROR
    return m_names[m_selected];
}

void Radio::unselect() {
    if (m_selected != m_names.size()) {
        m_options[m_names[m_selected]]->uncheck();
        m_selected = m_names.size();
    }
}

void Radio::enable(const std::string& name) {
    m_options[name]->enable();
}

void Radio::disable(const std::string& name) {
    m_options[name]->disable();
}

bool Radio::isEnabled(const std::string& name) const {
    return m_options.at(name)->isEnabled();
}

bool Radio::onClick(const sf::RenderWindow& window, const sf::Event& event) {
    sf::Vector2f cords(sf::Mouse::getPosition(window));
    for (const std::string name : m_names) {
        if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left
            && m_options[name]->contains(cords)) {
            if (m_options[name]->isEnabled()) {
                if (!m_options[name]->isChecked()) {
                    m_options[name]->check();

                    if (m_selected != m_names.size()) {
                        m_options[m_names[m_selected]]->uncheck();
                    }
                    m_selected = std::distance(m_names.begin(), std::find(m_names.begin(), m_names.end(), name));
                }
                return true;
            }
            else {
                if (name == m_names[m_selected]) {
                    m_selected = m_names.size();
                }
            }
        }
    }
    return false;
}

void Radio::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (const std::string name : m_names) {
        m_options.at(name)->draw(target, states);
    }
}