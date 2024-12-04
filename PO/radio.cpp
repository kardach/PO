#include "radio.h"

using namespace std;

Radio::Radio() {
    this->checked = false;
    this->v = nullptr;
    this->heigth = 0;
    this->width = 0;
    this->x = 0;
    this->y = 0;
    this->rgb = 0x000000;
}
Radio::Radio(float height, float width, float x, float y, int rgb, size_t size, i_fptr_i on_click) {
    this->checked = false;
    this->v = new vector<Button>;
    this->heigth = height;
    this->width = width;
    this->x = x;
    this->y = y;
    this->rgb = rgb;
    for (size_t i = 0; i < size; i++) {
        v->push_back(Button(height, width / size, x + i * (width / size), y, rgb, on_click));
    }
}
Radio::~Radio() {
    delete v;
}
void Radio::draw() {
    for (size_t i = 0; i < v->size(); i++) {
        v->at(i).draw();
    }
}
bool Radio::contains(Vector2f point) {
    button.setPosition(Vector2f(x, y));
    button.setSize(Vector2f(width, heigth));
    return button.getGlobalBounds().contains(point);
}
int Radio::select(Vector2f point) {
    checked = true;
    for (size_t i = 0; i < v->size(); i++) {
        if (v->at(i).contains(point)) {
            return v->at(i).on_click((int)i);
        }
    }
    return 0;
}
bool Radio::is_checked() {
    return checked;
}