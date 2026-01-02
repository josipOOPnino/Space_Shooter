#pragma once
#include "Entity.h"

enum class BulletType { Player, Enemy };

class Bullet : public Entity
{
private:
    bool active;

public:
    Bullet(sf::Vector2f pos, BulletType type);

    void update(float dt) override;

    bool isActive() const;
    void deactivate();
};
