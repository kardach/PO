#include "checkbox.h"

Checkbox::Checkbox(float height, float width, float x, float y, int rgb) {
	this->heigth = height;
	this->width = width;
	this->x = x;
	this->y = y;
	this->rgb = rgb;
	this->checked = false;
}
Checkbox::~Checkbox() {
}
bool Checkbox::is_checked() {
	return checked;
}
void Checkbox::draw() {
	color.r = rgb >> 16 & 0xFF;
	color.g = rgb >> 8 & 0xFF;
	color.b = rgb & 0xFF;

	button.setSize(Vector2f(width, heigth));
	button.setPosition(Vector2f(x, y));
	button.setFillColor(color);
	window.draw(button);
}
void Checkbox::on_click() {
	this->checked = !checked;
}
bool Checkbox::contains(Vector2f point) {
	button.setSize(Vector2f(width, heigth));
	button.setPosition(x, y);
	return button.getGlobalBounds().contains(point);
}