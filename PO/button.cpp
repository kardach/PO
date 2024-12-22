#include <SFML/Graphics.hpp>
#include <string>

#include "RoundedRectangle.h"
#include "Button.h"

Button::Button()
    : RoundedRectangle(), m_text("") {
}
Button::Button(const sf::Vector2f& size, const float roundness, const std::string text)
    : RoundedRectangle(size, roundness), m_text(text) {
}

Button::~Button() {
}

int Button::onClick(int x) {
    return 0;
}