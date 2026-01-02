#pragma once
#include "Entity.h"

class Enemy : public Entity
{
private:
    bool alive;

public:
    Enemy(sf::Vector2f pos);

    void update(float dt) override;

    bool isAlive() const;
    void kill();
};
