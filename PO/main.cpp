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


class Tile {
protected:
    RectangleShape tile;
    float size;
    float x;
    float y;
public:
    Tile() {
    }
    virtual ~Tile() {
    }
    virtual void draw() {
        window.draw(tile);
    }
};
class CornerTile :public Tile {
public:
    CornerTile(float size, float x, float y) {
        this->size = size;
        this->x = x;
        this->y = y;
        this->tile = RectangleShape(Vector2f(size, size));

        tile.setPosition(x * tile_size + x_offset, y * tile_size + y_offset);
        tile.setFillColor(Color(222, 184, 135));
    }
    ~CornerTile() {
    }
};
class BorderTile : public Tile {
private:
    Text text;
public:
    BorderTile(float size, float x, float y, char sign) {
        this->size = size;
        this->x = x;
        this->y = y;
        this->text = Text();
        this->tile = RectangleShape(Vector2f(size, size));

        tile.setPosition(x * tile_size + x_offset, y * tile_size + y_offset);
        tile.setFillColor(Color(222, 184, 135));

        text.setFont(font);
        text.setCharacterSize(24);
        text.setFillColor(Color(128, 0, 0));
        text.setString("fj");
        text.setPosition(x * tile_size + x_offset - 2, y * tile_size + y_offset - 4);

        cout << text.getLocalBounds().top << " " << text.getLocalBounds().left << endl;
        cout << text.getLocalBounds().height << " " << text.getLocalBounds().width << endl;
        cout << text.getGlobalBounds().top << " " << text.getGlobalBounds().left << endl;
        cout << text.getGlobalBounds().height << " " << text.getGlobalBounds().width << endl;
        cout << endl;
    }
    ~BorderTile() {
    }
    void draw() override{
        window.draw(tile);
        window.draw(text);
    }
};
class MainTile: public Tile {
private:
    int piece_placed = 0;
public:
    MainTile(float size, float x, float y, bool color) {
        this->size = size;
        this->x = x;
        this->y = y;
        this->tile = RectangleShape(Vector2f(size, size));

        tile.setPosition(x * tile_size + x_offset, y * tile_size + y_offset);
        tile.setFillColor(color ? Color(255, 228, 196) : Color(139, 69, 19));
    }
    ~MainTile() {
    }
    void draw() override {
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

    background.setPosition(0, 0);
    background.setFillColor(Color(128, 128, 128));
    
    font.loadFromFile("ariblk.ttf");
    
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
                TILES[i][j] = new BorderTile(tile_size, i, j, 'y');
            }
            //top and bottom board border
            else if ((i == 0 || i == board_size - 1) && j != 0 && j != board_size - 1) {
                TILES[i][j] = new BorderTile(tile_size, i, j, '0');
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