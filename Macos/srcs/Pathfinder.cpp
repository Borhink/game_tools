#include "Pathfinder.h"

void Pathfinder::copyBlock(std::vector<std::vector<int>> &pathMap, Map &map)
{
	sf::Vector2i	size(map.getSize());

	for (int y(0); y < size.y; y++)
	{
		pathMap[y].resize(size.x);
		for (int x(0); x < size.x; x++)
			pathMap[y][x] = map.getCell(x, y, (CellType)(CellType::Block + CellType::Player));
	}
}

int Pathfinder::getCellDist(Map &map, sf::Vector2i playerPos)
{
	int		dist;

	dist = abs(map.getMouseCell().x - playerPos.x) + abs(map.getMouseCell().y - playerPos.y);
	return (dist);
}

int Pathfinder::validCell(sf::Vector2i pos, std::vector<std::vector<int>> &gameMap, sf::Vector2i mapSize, int weight)
{
    if (pos.y >= 0 && pos.x >= 0 && pos.y < mapSize.y && pos.x < mapSize.x)
    {
        int cell(gameMap[pos.y][pos.x]);
        if (!cell || (cell >= 100 && cell > weight))
            return (1);
    }
    return (0);
}

int	Pathfinder::nextCell(sf::Vector2i cur, std::vector<std::vector<int>> &gameMap, sf::Vector2i mapSize, int weight, std::queue<sf::Vector2i> &cells, sf::Vector2i movablePos)
{
	if (validCell(sf::Vector2i(cur.x, cur.y), gameMap, mapSize, weight))
	{
		if (sf::Vector2i(cur.x, cur.y) == movablePos)
			return (1);
		gameMap[cur.y][cur.x] = weight + 1;
		cells.push(sf::Vector2i(cur.x, cur.y));
	}
	return (0);
}

int Pathfinder::getWeight(sf::Vector2i pos, std::vector<std::vector<int>> &gameMap, sf::Vector2i mapSize)
{
    if (pos.y < 0 || pos.x < 0 || pos.y >= mapSize.y || pos.x >= mapSize.x || !gameMap[pos.y][pos.x] || gameMap[pos.y][pos.x] < 100)
        return (10000);
    return (gameMap[pos.y][pos.x]);
}

sf::Vector2i Pathfinder::getPath(sf::Vector2i pos, std::vector<std::vector<int>> &gameMap, sf::Vector2i mapSize)
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

int	Pathfinder::pathfinding(sf::Vector2i pos, std::vector<std::vector<int>> &gameMap, sf::Vector2i mapSize, sf::Vector2i movablePos)
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
		if (nextCell(sf::Vector2i(cur.x, cur.y - 1), gameMap, mapSize, weight, cells, movablePos)
		|| nextCell(sf::Vector2i(cur.x, cur.y + 1), gameMap, mapSize, weight, cells, movablePos)
		|| nextCell(sf::Vector2i(cur.x + 1, cur.y), gameMap, mapSize, weight, cells, movablePos)
		|| nextCell(sf::Vector2i(cur.x - 1, cur.y), gameMap, mapSize, weight, cells, movablePos))
			return (1);
        cells.pop();
    }
    return (0);
}

int Pathfinder::getPath(Map &map, Movable &movable)
{
	sf::Vector2i					mapSize(map.getSize());
	sf::Vector2i					pos(map.getMouseCell());
	sf::Vector2i					movablePos(movable.getPos());
	std::vector<std::vector<int>>	pathMap(mapSize.y);
	int								pm(movable.getPm());

	map.clear(CellType::Path);
	if (map.inBounds(pos) && pos != movablePos && Pathfinder::getCellDist(map, movablePos) <= pm && !map.getCell(pos, CellType::Block))
	{
	    Debug::log("Movable::goTo: pos.x = " + Debug::to_str(pos.x));
	    Debug::log("Movable::goTo: pos.y = " + Debug::to_str(pos.y));
		copyBlock(pathMap, map);
	    if (pathfinding(pos, pathMap, mapSize, movablePos))
	    {
	        Debug::log("Movable::goTo: map = " + Debug::to_str(pathMap, mapSize));
	        Debug::log("Movable::goTo: PATH FIND !");
	        for (sf::Vector2i cur(movablePos); cur != pos;)
	        {
				if (pm == 0)
				{
					map.clear(CellType::Path);
					return (0);
				}
	            cur = getPath(cur, pathMap, mapSize);
				map.setCell(cur, 1, CellType::Path);
				pm--;
	        }
			return (1);
	    }
		Debug::log("Movable::goTo: map = " + Debug::to_str(pathMap, mapSize));
		Debug::log("Movable::goTo: PATH NOT FIND !");
	}
	return (0);
}
