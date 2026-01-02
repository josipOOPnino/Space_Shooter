#pragma once
#include <SFML/Graphics.hpp>

class Entity
{
protected:
    sf::RectangleShape shape;
    sf::Vector2f velocity;

public:
    Entity();
    virtual ~Entity() = default;

    virtual void update(float dt) = 0;
    void draw(sf::RenderWindow& window) const;

    sf::FloatRect getBounds() const;
};
