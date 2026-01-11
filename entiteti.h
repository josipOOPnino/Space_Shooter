#pragma once
#include <SFML/Graphics.hpp>

struct Metak
{
    sf::RectangleShape shape;
    sf::Vector2f velocity;
    bool alive = true;

    Metak(sf::Vector2f pos);
    void update(float dt);
    void draw(sf::RenderWindow& w);
    sf::FloatRect getBounds() const;
};

struct Neprijatelj
{
    sf::RectangleShape shape;
    bool alive = true;
    float dir = 1.f;

    Neprijatelj(sf::Vector2f pos);
    void update(float dt);
    void draw(sf::RenderWindow& w);
    sf::FloatRect getBounds() const;
    sf::Vector2f getPosition() const;
};

struct Eksplozija
{
    sf::CircleShape shape;
    float timer = 0.f;
    bool finished = false;

    Eksplozija(sf::Vector2f pos);
    void update(float dt);
    void draw(sf::RenderWindow& w);
};

struct Igrac
{
    sf::RectangleShape oblik;
    float timerPucanja;
    float brzina;

    Igrac();

    void reset();
    void update(float dt);
    bool mozePucati() const;
    Metak pucaj();
    void draw(sf::RenderWindow& prozor);

    sf::FloatRect getBounds() const;
};