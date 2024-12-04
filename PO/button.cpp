#include "button.h"

bool Button::contains(Vector2f point) {
    button.setSize(Vector2f(width, heigth));
    button.setPosition(x, y);
    return button.getGlobalBounds().contains(point);
}
Button::Button() {
    this->rgb = 0;
    this->heigth = 0;
    this->width = 0;
    this->on_click = nullptr;
    this->x = 0;
    this->y = 0;

}
Button::Button(float heigth, float width, float x, float y, int rgb, i_fptr_i on_click) {
    this->heigth = heigth;
    this->width = width;
    this->x = x;
    this->y = y;
    this->rgb = rgb;
    this->on_click = on_click;
}
Button::~Button() {
}
void Button::draw() {
    color.r = rgb >> 16 & 0xFF;
    color.g = rgb >> 8 & 0xFF;
    color.b = rgb & 0xFF;

    button.setSize(Vector2f(width, heigth));
    button.setPosition(Vector2f(x, y));
    button.setFillColor(color);
    window.draw(button);
}