#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Player.h"
#include "Bullet.h"

class Game
{
private:
    sf::RenderWindow window;
    sf::Clock clock;

    Player player;
    std::vector<Bullet> bullets;

public:
    Game();
    void run();

private:
    void update(float dt);
    void render();
};
