#pragma once
#include <SFML/Graphics.hpp>

class HUD
{
private:
    sf::Font font;
    sf::Text scoreText;

public:
    HUD();

    void update(int score);
    void draw(sf::RenderWindow& window);
};
