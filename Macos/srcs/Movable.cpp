#include "Movable.h"
#include "Pathfinder.h"

Movable::Movable(int x, int y) :
	Entity(x, y),
	mPm(0)
{
}

Movable::Movable(int x, int y, int pm) :
	Entity(x, y),
	mPm(pm)
{
}

void Movable::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::RectangleShape cell;

	cell.setSize(sf::Vector2f(20, 20));
	cell.setFillColor(sf::Color::Blue);
	cell.setPosition(mPos.x * 22, mPos.y * 22);
	target.draw(cell, states);
}

void Movable::goTo(Map &map)
{
	if (this->showPath(map) && map.validClic())
	{
		mPos = map.getMouseCell();
		map.clear(CellType::Path);
	}
}

int Movable::showPath(Map &map)
{
	return (Pathfinder::getPath(map, *this));
}

int Movable::getPm(void) const
{
	return (mPm);
}

void Movable::setPm(int pm)
{
	if (pm >= 0)
		mPm = pm;
}

Movable::~Movable()
{
    //dtor
}
