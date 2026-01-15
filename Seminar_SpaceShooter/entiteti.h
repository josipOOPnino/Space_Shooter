#pragma once
#include <SFML/Graphics.hpp>
#include <optional>

enum class ValTip { Val1, Val2, Val3 };

struct Metak
{
    sf::Sprite sprite;
    sf::Vector2f velocity{ 0.f, -800.f };
    bool alive = true;

    Metak(sf::Vector2f pos, const sf::Texture& tex);
    void update(float dt);
    void draw(sf::RenderWindow& w) const;
    sf::FloatRect getBounds() const;
};

struct Neprijatelj
{
    sf::Sprite sprite;
    bool alive = true;

    float dirX = 1.f;
    float vrijeme = 0.f;
    ValTip val = ValTip::Val2;

    int frame = 0;
    float frameTimer = 0.f;

    Neprijatelj(sf::Vector2f pos, ValTip v, const sf::Texture& tex);
    void update(float dt);
    void draw(sf::RenderWindow& w) const;
    sf::FloatRect getBounds() const;
    sf::Vector2f getPosition() const;
};

struct Eksplozija
{
    sf::Sprite sprite;
    int frame = 0;
    float frameTimer = 0.f;
    bool finished = false;

    Eksplozija(sf::Vector2f pos, const sf::Texture& tex);
    void update(float dt);
    void draw(sf::RenderWindow& w) const;
};

struct Igrac
{
    std::optional<sf::Sprite> sprite;

    float timerPucanja = 0.f;
    float brzina = 400.f;

    Igrac() = default;

    void init(const sf::Texture& tex);
    void reset();
    void update(float dt);
    bool mozePucati() const;
    Metak pucaj(const sf::Texture& texMetak);
    void draw(sf::RenderWindow& prozor) const;

    sf::FloatRect getBounds() const;
};
