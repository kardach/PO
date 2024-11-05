#include <SFML/Graphics.hpp>
#include <iostream>;
#include "window.cpp"

using namespace sf;
using namespace std;

RenderWindow window(VideoMode(800, 600), "Draughts", Style::Close | Style::Titlebar);

int window_heigth = window.getSize().y;
int window_width = window.getSize().x;

RectangleShape background = RectangleShape(Vector2f(window_width, window_heigth));

int board_size = 10 + 2;
float tile_size = ((window_heigth < window_width) ? window_heigth : window_width) / board_size;
int tile_count = board_size * board_size;

float x_offset = (window_heigth < window_width) ? (window_width - board_size * tile_size) / 2 : 0;
float y_offset = (window_heigth < window_width) ? 0 : (window_width - board_size * tile_size) / 2;

Font font;
Text text;
RectangleShape tile;
Color color;

class Tile {
protected:
    float size;
    float x;
    float y;
    int rgb;
public:
    Tile() {
    }
    virtual ~Tile() {
    }
    virtual void draw() {
        color.r = rgb >> 16 & 0xFF;
        color.g = rgb >> 8 & 0xFF;
        color.b = rgb & 0xFF;

        tile.setSize(Vector2f(tile_size, tile_size));
        tile.setPosition(x * tile_size + x_offset, y * tile_size + y_offset);
        tile.setFillColor(color);
        window.draw(tile);
    }
};
class CornerTile :public Tile {
public:
    CornerTile(float size, float x, float y) {
        this->size = size;
        this->x = x;
        this->y = y;
        this->rgb = 0xDEB887;
    }
    ~CornerTile() {
    }
};
class BorderTile : public Tile {
private:
    char sign;
public:
    BorderTile(float size, float x, float y, char sign) {
        this->size = size;
        this->x = x;
        this->y = y;
        this->rgb = 0xDEB887;
        this->sign = sign;
    }
    ~BorderTile() {
    }
    void draw() override{
        color.r = rgb >> 16 & 0xFF;
        color.g = rgb >> 8 & 0xFF;
        color.b = rgb & 0xFF;

        tile.setSize(Vector2f(tile_size, tile_size));
        tile.setPosition(x * tile_size + x_offset, y * tile_size + y_offset);
        tile.setFillColor(color);
        window.draw(tile);

        text.setString(sign);
        text.setPosition(x * tile_size + x_offset + (tile_size - text.getLocalBounds().width) / 2, y * tile_size + y_offset + (tile_size - text.getLocalBounds().height) / 2);
        window.draw(text);
    }
};
class MainTile: public Tile {
private:
    int piece_placed = 0;
public:
    MainTile(float size, float x, float y, bool team) {
        this->size = size;
        this->x = x;
        this->y = y;
        this->rgb = team ? 0xFFE4C4 : 0x8B4513;
    }
    ~MainTile() {
    }
    void draw() override {
        color.r = rgb >> 16 & 0xFF;
        color.g = rgb >> 8 & 0xFF;
        color.b = rgb & 0xFF;

        tile.setSize(Vector2f(tile_size, tile_size));
        tile.setPosition(x * tile_size + x_offset, y * tile_size + y_offset);
        tile.setFillColor(color);
        window.draw(tile);

        if (piece_placed) {
            CircleShape piece = CircleShape(tile_size / 2);
            piece.setFillColor(Color::White);
            piece.setPosition(x * tile_size + x_offset, y * tile_size + y_offset);
            window.draw(piece);
        }
    }
    void place_piece() {
        this->piece_placed = 1;
    }
};
int main() {
    color.r = color.g = color.b = 128;
    background.setPosition(0, 0);
    background.setFillColor(color);
    
    font.loadFromFile("ariblk.ttf");
    
    color.g = color.b = 0;
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(color);

    Tile*** TILES = new Tile ** [board_size];
    for (int i = 0; i < board_size; i++) {
        TILES[i] = new Tile*[board_size];
    }

    for (int i = 0; i < board_size; i++) {
        for (int j = 0; j < board_size; j++) {
            //inner tiles
            if (i != 0 && i != board_size - 1 && j != 0 && j != board_size - 1) {
                TILES[i][j] = new MainTile(tile_size, i, j, (i + j) % 2);
            }
            //left and right board border
            else if (i != 0 && i != board_size - 1 && (j == 0 || j == board_size - 1)) {
                TILES[i][j] = new BorderTile(tile_size, i, j, 'a' + i - 1);
            }
            //top and bottom board border
            else if ((i == 0 || i == board_size - 1) && j != 0 && j != board_size - 1) {
                TILES[i][j] = new BorderTile(tile_size, i, j, '0' + j - 1);
            }
            //corners
            else {
                TILES[i][j] = new CornerTile(tile_size, i, j);
            }
        }
    }
    
    //game
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }
        window.clear();
        window.draw(background);
        for (int i = 0; i < board_size; i++) {
            for (int j = 0; j < board_size; j++) {
                TILES[i][j]->draw();
            }
        }
        
        window.display();
    }

    return 0;
}