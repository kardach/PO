#pragma once

#ifndef MOVE_H_
#define MOVE_H_

#include <SFML/Graphics.hpp>
#include "globals.h"

class Move {
public:
    Vector2i from;
    Vector2i to;
    Move(Vector2i, Vector2i);
    ~Move();
};

#endif