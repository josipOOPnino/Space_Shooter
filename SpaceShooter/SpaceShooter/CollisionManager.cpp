#include "CollisionManager.h"
#include <algorithm>

void CollisionManager::handleBulletEnemyCollisions(
    std::vector<Bullet>& bullets,
    std::vector<Enemy>& enemies,
    int& score)
{
    for (auto& b : bullets)
    {
        if (!b.isActive()) continue;

        for (auto& e : enemies)
        {
            if (!e.isAlive()) continue;

            if (b.getBounds().findIntersection(e.getBounds()))
            {
                b.deactivate();
                e.kill();
                score += 10;
            }
        }
    }

    enemies.erase(
        std::remove_if(enemies.begin(), enemies.end(),
            [](const Enemy& e) { return !e.isAlive(); }),
        enemies.end()
    );
}
