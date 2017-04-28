#include "Player.h"
#include "Input.h"
#include "Map.h"

Player::Player(int x, int y, int pm) :
	Movable(x, y, pm),
	mSpell(new Spell("X2,1,2,5", 5)),
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

void Player::update(Input &input, Map &map, int type)
{
	if (!input.getEntry(Input::MLeft))
	{
		if (type == sf::Event::MouseButtonReleased)
		{
			if (mSelectSpell)
				this->useSpell(map);
			else
				this->goTo(map);
		}
		else if (map.mouseCellChanged())
		{
			if (mSelectSpell)
				this->showSpell(map);
			else
				this->showPath(map);
		}
	}
	if (input.getEntry(Input::Num1))
	{
		this->updateSelectedSpell(1, map);
		input.keyReleased((sf::Keyboard::Key)Input::Num1);
	}
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
		map.clear(CellType::Range);
		mSelectSpell = 0;
	}
}

void Player::updateSelectedSpell(int id, Map &map)
{
	this->setSelectedSpell(id);
	if (mSelectSpell)
	{
		map.clear(CellType::Path);
		mSpell->showRange(map, mPos);
		this->showSpell(map);
	}
	else
	{
		map.clear(CellType::Zone);
		map.clear(CellType::Range);
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
