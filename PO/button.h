#pragma once

#ifndef BUTTON_H_
#define BUTTON_H_

class Button : public RoundedRectangle {
private:
    std::string m_text;
public:
    Button();

    Button(const sf::Vector2f&, const float, const std::string);

    ~Button();

    int onClick(int);

};

#endif // BUTTON_H_