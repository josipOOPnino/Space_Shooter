#include "Bullet.h"

Bullet::Bullet(sf::Vector2f pos, BulletType type)
{
    active = true;

    shape.setSize({ 4.f, 10.f });
    shape.setPosition(pos);
    shape.setFillColor(type == BulletType::Player ? sf::Color::Green : sf::Color::Red);

    velocity = (type == BulletType::Player)
        ? sf::Vector2f(0.f, -500.f)
        : sf::Vector2f(0.f, 300.f);
}

void Bullet::update(float dt)
{
    shape.move(velocity * dt);

    if (shape.getPosition().y < -20.f || shape.getPosition().y > 620.f)
        active = false;
}

bool Bullet::isActive() const
{
    return active;
}

void Bullet::deactivate()
{
    active = false;
}
