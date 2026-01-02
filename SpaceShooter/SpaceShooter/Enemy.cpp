#include "Enemy.h"

Enemy::Enemy(sf::Vector2f pos)
{
    alive = true;

    shape.setSize({ 32.f, 32.f });
    shape.setFillColor(sf::Color::Red);
    shape.setPosition(pos);

    velocity = { 0.f, 40.f };
}

void Enemy::update(float dt)
{
    shape.move(velocity * dt);
}

bool Enemy::isAlive() const
{
    return alive;
}

void Enemy::kill()
{
    alive = false;
}
