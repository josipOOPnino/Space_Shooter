#pragma once
#include <SFML/Graphics.hpp>

class Explosion
{
private:
    sf::CircleShape shape;
    float lifetime;
    bool active;

public:
    Explosion(sf::Vector2f position);

    void update(float dt);
    void draw(sf::RenderWindow& window);

    bool isActive() const;
};
