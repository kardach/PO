#pragma once
#ifndef TILES_H
#define TILES_H

#include <SFML/Graphics.hpp>
#include "globals.h"
#include "piece.h"

class Tile {
protected:
    float size;
    float x;
    float y;
    int rgb;
public:
    Tile(float, float, float, int);
    virtual ~Tile();
    virtual void draw() = 0;
};
class CornerTile : virtual public Tile {
public:
    CornerTile(float, float, float);
    ~CornerTile();
    void draw() override;
};
class BorderTile : virtual public Tile {
private:
    char sign;
public:
    BorderTile(float, float, float, char);
    ~BorderTile();
    void draw() override;
};
class MainTile : virtual public Tile {
private:
    Piece* piece;
public:
    MainTile(float, float, float, bool);
    ~MainTile();
    void draw() override;
    void place_piece(Piece* piece);
    bool has_piece();
    Piece* remove_piece();
};

#endif