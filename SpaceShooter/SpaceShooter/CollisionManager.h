#pragma once
#include <vector>
#include "Bullet.h"
#include "Enemy.h"

class CollisionManager
{
public:
    static void handleBulletEnemyCollisions(
        std::vector<Bullet>& bullets,
        std::vector<Enemy>& enemies,
        int& score
    );
};
