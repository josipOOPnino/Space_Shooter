#pragma once
#include "Entity.h"

class Player : public Entity
{
private:
    float speed;
    float shootTimer;
    float shootCooldown;

public:
    Player();

    void update(float dt) override;

    bool canShoot() const;
    void resetShootTimer();

    sf::Vector2f getGunPosition() const;
};
