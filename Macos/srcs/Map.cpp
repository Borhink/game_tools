#include "Map.h"
#include "Player.h"
#include "Input.h"

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
	mCellPressed(-1, -1),
	mMouseCellChanged(false)
{
	mCell = initTab(mCell, mSize);
	mPlayer = initTab(mPlayer, mSize);
	mRange = initTab(mRange, mSize);
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
			cell.setPosition(x * 22, y * 22);
			target.draw(cell, states);
			if (this->getCell(x, y, CellType::Range))//Zone de sort
				cell.setFillColor(sf::Color(65,105,225, 100));
			if (this->getCell(x, y, CellType::Zone))//Zone de sort
				cell.setFillColor(sf::Color(255, 0, 0, 180));
			if (this->getCell(x, y, CellType::Path))//Chemin pathfinding
				cell.setFillColor(sf::Color::Green);
			cell.setPosition(x * 22, y * 22);
			target.draw(cell, states);
		}
	}
}

void Map::update(Input &input, int type)
{
	if (type == sf::Event::MouseButtonPressed)
	{
		if (input.getEntry(Input::MLeft))
			mCellPressed = mouseToPos(input.getMouse());
	}
	else if (type == -1)
	{
		if (input.mouseHasMoved())
			this->setMouseCell(input.getMouse());
		if (input.getEntry(Input::MRight))
			this->setCell(this->getMouseCell(), 1, CellType::Block);
		if (input.getEntry(Input::MMiddle))
			this->setCell(this->getMouseCell(), 0, CellType::Block);
	}
}

sf::Vector2i Map::mouseToPos(sf::Vector2i mouse) const
{
	return (sf::Vector2i(mouse.x / 22, mouse.y / 22));
}

sf::Vector2i Map::mouseToPos(int x, int y) const
{
	return (sf::Vector2i(x / 22, y / 22));
}

bool Map::mouseInBounds(int x, int y) const
{
	sf::Vector2i pos(mouseToPos(x, y));

	if (pos.y < mSize.y && pos.y >= 0 && pos.x < mSize.x && pos.x >= 0)
		return (1);
	return (0);
}

bool Map::mouseInBounds(sf::Vector2i mouse) const
{
	sf::Vector2i pos(mouseToPos(mouse));

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

bool Map::mouseCellChanged(void)
{
	if (mMouseCellChanged)
	{
		mMouseCellChanged = false;
		return (true);
	}
	return (false);
}

void Map::clear(CellType type)
{
	for (int y(0); y < mSize.y; y++)
		for (int x(0); x < mSize.x; x++)
			this->setCell(x, y, 0, type);
}

int Map::getCell(sf::Vector2i pos, int type) const
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

int Map::getCell(int x, int y, int type) const
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
	sf::Vector2i	pos(mouseToPos(x, y));

	if (mMouseCell != pos)
	{
		mMouseCell = pos;
		mMouseCellChanged = true;
	}
}

void Map::setMouseCell(sf::Vector2i mouse)
{
	sf::Vector2i	pos(mouseToPos(mouse));

	if (mMouseCell != pos)
	{
		mMouseCell = pos;
		mMouseCellChanged = true;
	}
}

sf::Vector2i Map::getMouseCell(void) const
{
	return (mMouseCell);
}

void Map::setCellPressed(sf::Vector2i mouse)
{
	mCellPressed = mouseToPos(mouse);
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
