#include <SFML/Graphics.hpp>
#include <cmath>

sf::Vector2f round(const sf::Vector2f vector)
{
    return sf::Vector2f{ std::round(vector.x), std::round(vector.y) };
}

int main()
{
    auto window = sf::RenderWindow{ {800, 600, 32}, "SFML Window" };
    window.setFramerateLimit(60);
    auto font = sf::Font{};

    if (!font.loadFromFile("OpenSans.ttf"))
    {
        sf::err() << "Couldn't load font\n";
        return -1;
    }

    auto text = sf::Text{ "Centered Text", font };
    auto center = text.getGlobalBounds().getSize() / 2.f;
    auto localBounds = center + text.getLocalBounds().getPosition();
    auto rounded = round(localBounds);
    text.setOrigin(rounded);
    text.setPosition(sf::Vector2f{ window.getSize() / 2u });
    text.setFillColor(sf::Color{ 0x655A7CFF });

    auto rectangle = sf::RectangleShape{ {300.f, 100.f} };
    rectangle.setOutlineThickness(2.f);
    rectangle.setOutlineColor(sf::Color{ 0xAB92BFFF });
    rectangle.setOrigin(round(rectangle.getGlobalBounds().getSize() / 2.f));
    rectangle.setPosition(text.getPosition());
    rectangle.setFillColor(sf::Color::Transparent);

    while (window.isOpen())
    {
        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        window.clear(sf::Color{ 0xAFC1D6FF });
        window.draw(rectangle);
        window.draw(text);
        window.display();
    }
}