#pragma once

#ifndef MOVE_H_
#define MOVE_H_

class Move {
private:
	sf::Vector2u m_from;
	sf::Vector2u m_to;
public:
	Move(const sf::Vector2u&, const sf::Vector2u&);
	~Move();
	sf::Vector2u from();
	sf::Vector2u to();
};

//class Move : public sf::Drawable {
//    friend class MovePlanner;
//private:
//    class SubMove;
//
//    std::vector<std::unique_ptr<SubMove>> m_submoves;
//
//    sf::Vector2f m_offset;
//
//    float m_tile_size;
//
//    unsigned int m_board_size;
//public:
//    Move(const Board&, const Settings&);
//
//    ~Move();
//
//    Move(Move&& other) noexcept;
//
//    Move& operator=(Move&& other) noexcept;
//private:
//    void add(const sf::Vector2u&, const sf::Vector2u&);
//
//    void remove();
//public:
//    void clear();
//
//    std::size_t size();
//    
//
//    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
//};

#endif // MOVE_H_