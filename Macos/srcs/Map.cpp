#include "Map.h"
#include "Player.h"

template <typename T>
T **initTab(T **tab, sf::Vector2i size)
{
	tab = (T**)malloc(sizeof(T*) * size.y);
	for (int y(0); y < size.y; y++)
	{
		tab[y] = (T*)malloc(sizeof(T) * size.x);
		for (int x(0); x < size.x; x++)
			tab[y][x] = 0;
	}
	return (tab);
}

Map::Map(sf::Vector2i size) :
	mSize(size),
	mMouseCell(-1, -1),
	mCellPressed(-1, -1)
{
	mCell = initTab(mCell, mSize);
	mPlayer = initTab(mPlayer, mSize);
}

void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::RectangleShape  cell;

	cell.setSize(sf::Vector2f(20, 20));
	cell.setFillColor(sf::Color::White);
	cell.setPosition(0, 0);
	for (int y(0); y < mSize.y; y++)
	{
		for (int x(0); x < mSize.x; x++)
		{
			if (this->getCell(x, y, CellType::Block))//Block sur la map
				cell.setFillColor(sf::Color(155, 155, 155, 255));
			else
				cell.setFillColor(sf::Color::White);//Vide
			if (this->getCell(x, y, CellType::Zone))//Zone de sort
				cell.setFillColor(sf::Color::Red);
			if (this->getCell(x, y, CellType::Path))//Chemin pathfinding
				cell.setFillColor(sf::Color::Green);
			cell.setPosition(x * 22, y * 22);
			target.draw(cell, states);
		}
	}
}

bool Map::mouseInBounds(int x, int y) const
{
	sf::Vector2i	pos(x / 22, y / 22);

	if (pos.y < mSize.y && pos.y >= 0 && pos.x < mSize.x && pos.x >= 0)
		return (1);
	return (0);
}

bool Map::mouseInBounds(sf::Vector2i pos) const
{
	pos = sf::Vector2i(pos.x / 22, pos.y / 22);

	if (pos.y < mSize.y && pos.y >= 0 && pos.x < mSize.x && pos.x >= 0)
		return (1);
	return (0);
}

bool Map::inBounds(sf::Vector2i pos) const
{
	if (pos.y < mSize.y && pos.y >= 0 && pos.x < mSize.x && pos.x >= 0)
		return (1);
	return (0);
}

bool Map::inBounds(int x, int y) const
{
	if (y < mSize.y && y >= 0 && x < mSize.x && x >= 0)
		return (1);
	return (0);
}

void Map::updateMouseCell(sf::Vector2i mouse, class Player &player)
{
	sf::Vector2i	pos(mouse.x / 22, mouse.y / 22);

	if (mMouseCell.x != pos.x || mMouseCell.y != pos.y)
	{
		mMouseCell = pos;
		if (player.getSelectedSpell())
			player.showSpell(*this);
		else
			player.showPath(*this);
	}
}

void Map::clear(CellType type)
{
	for (int y(0); y < mSize.y; y++)
		for (int x(0); x < mSize.x; x++)
			this->setCell(x, y, 0, type);
}

int Map::getCell(sf::Vector2i pos, CellType type) const
{
	if (this->inBounds(pos))
	{
		if (type == CellType::None)
			return (mCell[pos.y][pos.x]);
		else if (type > CellType::None && type < CellType::TypeCount)
			return (mCell[pos.y][pos.x] & type);
	}
	return (-1);
}

int Map::getCell(int x, int y, CellType type) const
{
	if (this->inBounds(x, y))
	{
		if (type == CellType::None)
			return (mCell[y][x]);
		else if (type > CellType::None && type < CellType::TypeCount)
			return (mCell[y][x] & type);
	}
	return (-1);
}

void Map::setCell(sf::Vector2i pos, int val, CellType type)
{
	if (this->inBounds(pos))
	{
		if (type == CellType::None)
			mCell[pos.y][pos.x] = val;
		else if (type > CellType::None && type < CellType::TypeCount)
		{
			if (val)
				mCell[pos.y][pos.x] |= type;
			else if (type & mCell[pos.y][pos.x])
				mCell[pos.y][pos.x] ^= type;
		}
	}
}

void Map::setCell(int x, int y, int val, CellType type)
{
	if (this->inBounds(x, y))
	{
		if (type == CellType::None)
			mCell[y][x] = val;
		else if (type > CellType::None && type < CellType::TypeCount)
		{
			if (val)
				mCell[y][x] |= type;
			else if (type & mCell[y][x])
				mCell[y][x] ^= type;
		}
	}
}

int Map::getPlayer(sf::Vector2i pos) const
{
	if (this->inBounds(pos))
		return (mPlayer[pos.y][pos.x]);
	return (-1);
}

int Map::getPlayer(int x, int y) const
{
	if (this->inBounds(x, y))
		return (mPlayer[y][x]);
	return (-1);
}

void Map::setPlayer(sf::Vector2i pos, int val)
{
	if (this->inBounds(pos))
		mPlayer[pos.y][pos.x] = val;
}

void Map::setPlayer(int x, int y, int val)
{
	if (this->inBounds(x, y))
		mPlayer[y][x] = val;
}

sf::Vector2i Map::getSize() const
{
	return (mSize);
}

void Map::setMouseCell(int x, int y)
{
	sf::Vector2i	pos(x / 22, y / 22);

	if (this->inBounds(pos))
		mMouseCell = pos;
}

sf::Vector2i Map::getMouseCell(void) const
{
	return (mMouseCell);
}

void Map::setCellPressed(int x, int y)
{
	sf::Vector2i	pos(x / 22, y / 22);

	if (this->inBounds(pos))
		mCellPressed = pos;
}

sf::Vector2i Map::getCellPressed(void) const
{
	return (mCellPressed);
}

bool Map::validClic() const
{
	return (mMouseCell == mCellPressed);
}

Map::~Map()
{
	for (int y(0); y < mSize.y; y++)
		free(mCell[y]);
	free(mCell);
	for (int y(0); y < mSize.y; y++)
		free(mPlayer[y]);
	free(mPlayer);
}
