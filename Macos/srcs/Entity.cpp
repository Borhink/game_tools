#include "Entity.h"

Entity::Entity(int x, int y): mPos(x, y)
{
    //ctor
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::RectangleShape  cell;

	cell.setSize(sf::Vector2f(20, 20));
	cell.setFillColor(sf::Color::Blue);
	cell.setPosition(mPos.x * 22, mPos.y * 22);
	target.draw(cell, states);
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
