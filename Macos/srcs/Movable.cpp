#include "Movable.h"

Movable::Movable(int x, int y)
{
    mPos = sf::Vector2i(x, y);
}

// int Movable::isEmpty(int cell, int weight)
// {
//     if (cell && (cell < 100 || cell >= weight))
//         return (0);
//     return (1);
// }

int Movable::validCell(sf::Vector2i pos, std::vector<std::vector<int>> &gameMap, sf::Vector2i mapSize, int weight)
{
    if (pos.y >= 0 && pos.x >= 0 && pos.y < mapSize.y && pos.x < mapSize.x)
    {
        int cell(gameMap[pos.y][pos.x]);
        if (!cell || (cell >= 100 && cell > weight))
            return (1);
    }
    return (0);
}

int	Movable::nextCell(sf::Vector2i cur, std::vector<std::vector<int>> &gameMap, sf::Vector2i mapSize, int weight, std::queue<sf::Vector2i> &cells)
{
	if (validCell(sf::Vector2i(cur.x, cur.y), gameMap, mapSize, weight))
	{
		if (sf::Vector2i(cur.x, cur.y) == mPos)
			return (1);
		gameMap[cur.y][cur.x] = weight + 1;
		cells.push(sf::Vector2i(cur.x, cur.y));
	}
	return (0);
}

int	Movable::pathfinding(sf::Vector2i pos, std::vector<std::vector<int>> &gameMap, sf::Vector2i mapSize)
{
    std::queue<sf::Vector2i>    cells;
    int                         weight;
    sf::Vector2i                cur;

    cells.push(pos);
    gameMap[pos.y][pos.x] = 100;
    while (!cells.empty())
    {
        cur = cells.front();
        weight = gameMap[cur.y][cur.x];
		if (nextCell(sf::Vector2i(cur.x, cur.y - 1), gameMap, mapSize, weight, cells)
		|| nextCell(sf::Vector2i(cur.x, cur.y + 1), gameMap, mapSize, weight, cells)
		|| nextCell(sf::Vector2i(cur.x + 1, cur.y), gameMap, mapSize, weight, cells)
		|| nextCell(sf::Vector2i(cur.x - 1, cur.y), gameMap, mapSize, weight, cells))
			return (1);
        cells.pop();
    }
    return (0);
}

int Movable::getWeight(sf::Vector2i pos, std::vector<std::vector<int>> &gameMap, sf::Vector2i mapSize)
{
    if (pos.y < 0 || pos.x < 0 || pos.y >= mapSize.y || pos.x >= mapSize.x || !gameMap[pos.y][pos.x] || gameMap[pos.y][pos.x] < 100)
        return (10000);
    return (gameMap[pos.y][pos.x]);
}

sf::Vector2i Movable::getPath(sf::Vector2i pos, std::vector<std::vector<int>> &gameMap, sf::Vector2i mapSize)
{
    int weight(getWeight(sf::Vector2i(pos.x, pos.y + 1), gameMap, mapSize));
    sf::Vector2i path(pos.x, pos.y + 1);

    if (getWeight(sf::Vector2i(pos.x, pos.y - 1), gameMap, mapSize) < weight)
    {
        weight = gameMap[pos.y - 1][pos.x];
        path = sf::Vector2i(pos.x, pos.y - 1);
    }
    if (getWeight(sf::Vector2i(pos.x + 1, pos.y), gameMap, mapSize) < weight)
    {
        weight = gameMap[pos.y][pos.x + 1];
        path = sf::Vector2i(pos.x + 1, pos.y);
    }
    if (getWeight(sf::Vector2i(pos.x - 1, pos.y), gameMap, mapSize) < weight)
    {
        weight = gameMap[pos.y][pos.x - 1];
        path = sf::Vector2i(pos.x - 1, pos.y);
    }
    return (path);
}

// void Movable::clearPaths(Map &map)
// {
// 	sf::Vector2i	size(map.getSize());
//
//     for (int y(0); y < size.y; y++)
//     {
//         for (int x(0); x < size.x; x++)
//         {
//             if (gameMap[y][x] >= 100)
//                 gameMap[y][x] = 0;
//         }
//     }
// }

void Movable::copyBlock(std::vector<std::vector<int>> &pathMap, Map &map)
{
	sf::Vector2i	size(map.getSize());

	for (int y(0); y < size.y; y++)
	{
		pathMap[y].resize(size.x);
		for (int x(0); x < size.x; x++)
			pathMap[y][x] = map.getCell(x, y, (CellType)(CellType::Block + CellType::Player));
	}
}

void Movable::goTo(sf::Vector2i pos, Map &map)
{
	sf::Vector2i				mapSize(map.getSize());
	std::vector<std::vector<int>>	pathMap(mapSize.y);
	// int				pathMap[mapSize.y][mapSize.x];

    Debug::log("Movable::goTo: pos.x = " + Debug::to_str(pos.x));
    Debug::log("Movable::goTo: pos.y = " + Debug::to_str(pos.y));
	copyBlock(pathMap, map);
    if (pathfinding(pos, pathMap, mapSize))
    {
        Debug::log("Movable::goTo: map = " + Debug::to_str(pathMap, mapSize));
        Debug::log("Movable::goTo: PATH FIND !");
        for (sf::Vector2i cur(mPos); cur != pos;)
        {
            cur = getPath(cur, pathMap, mapSize);
            // gameMap[cur.y][cur.x] = 10;
			map.setCell(cur, 1, CellType::Path);
        }
        mPos = pos;
    }
    else
    {
        Debug::log("Movable::goTo: map = " + Debug::to_str(pathMap, mapSize));
        Debug::log("Movable::goTo: PATH NOT FIND !");
    }
    // clearPaths(gameMap, mapSize);
}

Movable::~Movable()
{
    //dtor
}
