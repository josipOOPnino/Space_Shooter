#include "Entity.h"

Entity::Entity()
{
    velocity = { 0.f, 0.f };
}

void Entity::draw(sf::RenderWindow& window) const
{
    window.draw(shape);
}

sf::FloatRect Entity::getBounds() const
{
    return shape.getGlobalBounds();
}
