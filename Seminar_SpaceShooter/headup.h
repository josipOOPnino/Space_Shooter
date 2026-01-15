#pragma once
#include <SFML/Graphics.hpp>

class HUD
{
    sf::Font font;
    sf::Text tekst;
    sf::Text tekstKraja;

public:
    HUD();
    void update(int bodovi, int zivoti);
    void draw(sf::RenderWindow& w);
    void drawGameOver(sf::RenderWindow& w);
};