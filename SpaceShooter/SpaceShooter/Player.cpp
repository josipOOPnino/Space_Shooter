#include "Player.h"
#include <SFML/Window/Keyboard.hpp>

Player::Player()
{
    speed = 400.f;
    shootCooldown = 0.25f;
    shootTimer = 0.f;

    shape.setSize({ 40.f, 20.f });
    shape.setFillColor(sf::Color::Green);
    shape.setPosition({ 380.f, 550.f });
}

void Player::update(float dt)
{
    velocity = { 0.f, 0.f };

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        velocity.x = -speed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        velocity.x = speed;

    shape.move(velocity * dt);
    shootTimer += dt;
}

bool Player::canShoot() const
{
    return shootTimer >= shootCooldown &&
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space);
}

void Player::resetShootTimer()
{
    shootTimer = 0.f;
}

sf::Vector2f Player::getGunPosition() const
{
    auto pos = shape.getPosition();
    return { pos.x + shape.getSize().x / 2.f, pos.y };
}
