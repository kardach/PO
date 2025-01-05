#include <SFML/Graphics.hpp>
#include <string>

#include "Button.h"
#include "RoundedRectangle.h"

Button::Button() {
	m_round_rect = RoundedRectangle();
	m_round_rect.setRoundness(0.5f);

	m_font = sf::Font();
	m_font.loadFromFile("ariblk.ttf");
	
	m_text = sf::Text();
	m_text.setFont(m_font);
	m_text.setCharacterSize(24);
}

Button::~Button() {
}

void Button::setSize(const sf::Vector2f& size) {
	m_round_rect.setSize(size);
	centerText();
}

void Button::setPosition(const sf::Vector2f& position) {
	m_round_rect.setPosition(position);
	centerText();
}

void Button::setFillColor(const sf::Color& color) {
	m_round_rect.setFillColor(color);
}

void Button::setTextColor(const sf::Color& color) {
	m_text.setFillColor(color);
}

void Button::setString(const std::string& text) {
	m_text.setString(text);
	centerText();
}

bool Button::contains(const sf::Vector2f& cords) {
	return m_round_rect.getGlobalBounds().contains(cords);
}

bool Button::onClick(const sf::RenderWindow& window, const sf::Event& event) {
	sf::Vector2f cords(sf::Mouse::getPosition(window));
	return event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left && contains(cords);
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(m_round_rect, states);
	target.draw(m_text, states);
}

void Button::centerText() {
	sf::FloatRect text_rect = m_text.getLocalBounds();
	m_text.setOrigin(text_rect.left + text_rect.width / 2.f, text_rect.top + text_rect.height / 2.f);
	m_text.setPosition(sf::Vector2f(m_round_rect.getPosition().x + m_round_rect.getOptionCount().x / 2.f,
		m_round_rect.getPosition().y + m_round_rect.getOptionCount().y / 2.f));
}