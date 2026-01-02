#include "Explosion.h"

Explosion::Explosion(sf::Vector2f position)
{
    shape.setRadius(3.f);
    shape.setFillColor(sf::Color::Yellow);
    shape.setPosition(position);

    lifetime = 0.3f;
    active = true;
}

void Explosion::update(float dt)
{
    lifetime -= dt;

    shape.setRadius(shape.getRadius() + 50.f * dt);
    shape.setFillColor(sf::Color(255, 255, 0, 150));

    if (lifetime <= 0.f)
        active = false;
}

void Explosion::draw(sf::RenderWindow& window)
{
    if (active)
        window.draw(shape);
}

bool Explosion::isActive() const
{
    return active;
}
