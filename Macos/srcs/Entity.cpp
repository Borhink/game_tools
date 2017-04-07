#include "Entity.h"

Entity::Entity(int x, int y): mPos(x, y)
{
    //ctor
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::RectangleShape  cell;
	sf::Vector2f        offset(15, 50);

	cell.setSize(sf::Vector2f(15, 15));
	cell.setOutlineColor(sf::Color::Blue);
	cell.setOutlineThickness(5);
	cell.setPosition(offset.x + mPos.x * 28, offset.y + mPos.y * 28);
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
