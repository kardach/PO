#pragma once

#ifndef BUTTON_H_
#define BUTTON_H_

#include <SFML/Graphics.hpp>
#include "globals.h"

class Button {
private:
    float heigth;
    float width;
    float x;
    float y;
    int rgb;
public:
    i_fptr_i on_click;
    Button();
    Button(float, float, float, float, int, i_fptr_i);
    ~Button();
    bool contains(Vector2f);
    void draw();
};

#endif