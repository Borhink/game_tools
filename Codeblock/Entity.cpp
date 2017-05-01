#include "Entity.h"

Entity::Entity(int x, int y): mPos(x, y)
{
    //ctor
}

sf::Vector2i Entity::getPos()
{
    return (mPos);
}

void Entity::setPos(sf::Vector2i pos)
{
    mPos = pos;
}

void Entity::setPos(int x, int y)
{
    mPos.x = x;
    mPos.y = y;
}

Entity::~Entity()
{
    //dtor
}
