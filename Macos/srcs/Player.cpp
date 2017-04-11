#include "Player.h"

Player::Player(int x, int y, int pm) :
	Movable(x, y, pm),
	mSpell(new Spell("X1,1,20,25;V3,1,10,12"))
{
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::RectangleShape  cell;
	sf::Vector2f        offset(15, 50);

	cell.setSize(sf::Vector2f(15, 15));
	cell.setOutlineColor(sf::Color::Blue);
	cell.setOutlineThickness(5);
	cell.setPosition(offset.x + mPos.x * 28, offset.y + mPos.y * 28);
	target.draw(cell, states);
}

void Player::useSpell(Map &map, sf::Vector2i pos)
{
	mSpell->use(map, mPos, pos);
}

Player::~Player()
{
    //dtor
}
