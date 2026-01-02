#include "Game.h"
#include <algorithm>

Game::Game()
    : window(
        sf::VideoMode(sf::Vector2u(800u, 600u)),
        "Space Shooter"
    )
{
    window.setFramerateLimit(60);
}

void Game::run()
{
    while (window.isOpen())
    {
        float dt = clock.restart().asSeconds();

        while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        update(dt);
        render();
    }
}

void Game::update(float dt)
{
    player.update(dt);

    if (player.canShoot())
    {
        bullets.emplace_back(player.getGunPosition(), BulletType::Player);
        player.resetShootTimer();
    }

    for (auto& b : bullets)
        b.update(dt);

    bullets.erase(
        std::remove_if(bullets.begin(), bullets.end(),
            [](const Bullet& b) { return !b.isActive(); }),
        bullets.end()
    );
}

void Game::render()
{
    window.clear();

    player.draw(window);

    for (auto& b : bullets)
        b.draw(window);

    window.display();
}
