#pragma once

#include "globals.h"
#include <SFML/Graphics.hpp>
#include "button.h"

using namespace std;

#ifndef RADIO_H_
#define RADIO_H_

class Radio {
private:
    bool checked;
    vector<Button>* v;
    float heigth;
    float width;
    float x;
    float y;
    int rgb;
public:
    Radio();
    Radio(float, float, float, float, int, size_t, i_fptr_i);
    ~Radio();
    void draw();
    bool contains(Vector2f);
    int select(Vector2f);
    bool is_checked();
};

#endif RADIO_H_