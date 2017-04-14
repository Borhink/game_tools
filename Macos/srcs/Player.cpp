#include "Player.h"

Player::Player(int x, int y, int pm) :
	Movable(x, y, pm),
	mSpell(new Spell("T5,1,10,12")),
	mSelectSpell(0)
{
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::RectangleShape  cell;

	cell.setSize(sf::Vector2f(20, 20));
	cell.setFillColor(sf::Color::Blue);
	cell.setPosition(mPos.x * 22, mPos.y * 22);
	target.draw(cell, states);
}

bool Player::showSpell(Map &map)
{
	mSpell->show(map, mPos);
	return (true);
}

void Player::useSpell(Map &map)
{
	if (this->showSpell(map) && map.validClic())
	{
		mSpell->use(map, mPos);
		map.clear(CellType::Zone);
		mSelectSpell = 0;
	}
}

void	Player::mouseAction(Map &map)
{
	if (mSelectSpell)
		this->useSpell(map);
	else
		this->goTo(map);
}

void Player::updateSelectedSpell(int id, Map &map)
{
	this->setSelectedSpell(id);
	if (mSelectSpell)
	{
		map.clear(CellType::Path);
		this->showSpell(map);
	}
	else
	{
		map.clear(CellType::Zone);
		this->showPath(map);
	}
}

void Player::setSelectedSpell(int id)
{
	if (mSelectSpell == id)
		mSelectSpell = 0;
	else
		mSelectSpell = id;
}

int Player::getSelectedSpell(void) const
{
	return (mSelectSpell);
}

Player::~Player()
{
    //dtor
}
