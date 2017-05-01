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

bool Pathfinder::inCell(sf::Vector2i pos, sf::Vector2i cell)
{
	sf::Rect<int>	rect(cell.x * 11, cell.y * 11, 11, 11);

	if (rect.contains(pos.x, pos.y))
		return (true);
	return (false);
}

void Pathfinder::checkSight1(Map &map, sf::Vector2i player, sf::Vector2i p2)
{
	sf::Vector2i	p1(player);
	int				e(std::abs(p2.x - p1.x));
	sf::Vector2i	d(e * 2, std::abs(p2.y - p1.y) * 2);

	while (p1.x <= p2.x)
	{
		if (player / 11 != p1 / 11 && map.getCell(p1 / 11, CellType::Block + CellType::Player))
		{
			map.setCell(p2 / 11, 0, CellType::Range);
			break;
		}
		if ((e -= d.y) <= 0)
		{
			p1.y++;
			e += d.x;
		}
		p1.x++;
	}
}

void Pathfinder::checkSight2(Map &map, sf::Vector2i player, sf::Vector2i p2)
{
	sf::Vector2i	p1(player);
	int				e(std::abs(p2.y - p1.y));
	sf::Vector2i	d(std::abs(p2.x - p1.x) * 2, e * 2);

	while (p1.y <= p2.y)
	{
		if (player / 11 != p1 / 11 && map.getCell(p1 / 11, CellType::Block + CellType::Player))
		{
			map.setCell(p2 / 11, 0, CellType::Range);
			break;
		}
		if ((e -= d.x) <= 0)
		{
			p1.x++;
			e += d.y;
		}
		p1.y++;
	}
}

void Pathfinder::checkSight3(Map &map, sf::Vector2i player, sf::Vector2i p2)
{
	sf::Vector2i	p1(player);
	int				e(std::abs(p2.y - p1.y));
	sf::Vector2i	d(std::abs(p2.x - p1.x) * 2, e * 2);

	while (p1.y <= p2.y)
	{
		if (player / 11 != p1 / 11 && map.getCell(p1 / 11, CellType::Block + CellType::Player))
		{
			map.setCell(p2 / 11, 0, CellType::Range);
			break;
		}
		if ((e -= d.x) <= 0)
		{
			p1.x--;
			e += d.y;
		}
		p1.y++;
	}
}

void Pathfinder::checkSight4(Map &map, sf::Vector2i player, sf::Vector2i p2)
{
	sf::Vector2i	p1(player);
	int				e(std::abs(p2.x - p1.x));
	sf::Vector2i	d(e * 2, std::abs(p2.y - p1.y) * 2);

	while (p1.x >= p2.x)
	{
		if (player / 11 != p1 / 11 && map.getCell(p1 / 11, CellType::Block + CellType::Player))
		{
			map.setCell(p2 / 11, 0, CellType::Range);
			break;
		}
		if ((e -= d.y) <= 0)
		{
			p1.y++;
			e += d.x;
		}
		p1.x--;
	}
}

void Pathfinder::checkSight5(Map &map, sf::Vector2i player, sf::Vector2i p2)
{
	sf::Vector2i	p1(player);
	int				e(std::abs(p2.x - p1.x));
	sf::Vector2i	d(e * 2, std::abs(p2.y - p1.y) * 2);

	while (p1.x >= p2.x)
	{
		if (player / 11 != p1 / 11 && map.getCell(p1 / 11, CellType::Block + CellType::Player))
		{
			map.setCell(p2 / 11, 0, CellType::Range);
			break;
		}
		if ((e -= d.y) <= 0)
		{
			p1.y--;
			e += d.x;
		}
		p1.x--;
	}
}

void Pathfinder::checkSight6(Map &map, sf::Vector2i player, sf::Vector2i p2)
{
	sf::Vector2i	p1(player);
	int				e(std::abs(p2.y - p1.y));
	sf::Vector2i	d(std::abs(p2.x - p1.x) * 2, e * 2);

	while (p1.y >= p2.y)
	{
		if (player / 11 != p1 / 11 && map.getCell(p1 / 11, CellType::Block + CellType::Player))
		{
			map.setCell(p2 / 11, 0, CellType::Range);
			break;
		}
		if ((e -= d.x) <= 0)
		{
			p1.x--;
			e += d.y;
		}
		p1.y--;
	}
}

void Pathfinder::checkSight7(Map &map, sf::Vector2i player, sf::Vector2i p2)
{
	sf::Vector2i	p1(player);
	int				e(std::abs(p2.y - p1.y));
	sf::Vector2i	d(std::abs(p2.x - p1.x) * 2, e * 2);

	while (p1.y >= p2.y)
	{
		if (player / 11 != p1 / 11 && map.getCell(p1 / 11, CellType::Block + CellType::Player))
		{
			map.setCell(p2 / 11, 0, CellType::Range);
			break;
		}
		if ((e -= d.x) <= 0)
		{
			p1.x++;
			e += d.y;
		}
		p1.y--;
	}
}

void Pathfinder::checkSight8(Map &map, sf::Vector2i player, sf::Vector2i p2)
{
	sf::Vector2i	p1(player);
	int				e(std::abs(p2.x - p1.x));
	sf::Vector2i	d(e * 2, std::abs(p2.y - p1.y) * 2);

	while (p1.x <= p2.x)
	{
		if (player / 11 != p1 / 11 && map.getCell(p1 / 11, CellType::Block + CellType::Player))
		{
			map.setCell(p2 / 11, 0, CellType::Range);
			break;
		}
		if ((e -= d.y) <= 0)
		{
			p1.y--;
			e += d.x;
		}
		p1.x++;
	}
}

void Pathfinder::checkSight(Map &map, sf::Vector2i pos, sf::Vector2i player)
{
	sf::Vector2i	dir(pos.x - player.x, pos.y - player.y);

	player = sf::Vector2i(player.x * 11 + 5, player.y * 11 + 5);
	pos = sf::Vector2i(pos.x * 11 + 5, pos.y * 11 + 5);
	if (dir.x >= 0)// DROITE
	{
		if (dir.y >= 0)// BAS
		{
			if (std::abs(dir.x) > std::abs(dir.y))// X
				Pathfinder::checkSight1(map, player, pos);
			else// Y
				Pathfinder::checkSight2(map, player, pos);

		}
		else// HAUT
		{
			if (std::abs(dir.x) > std::abs(dir.y))// X
				Pathfinder::checkSight8(map, player, pos);
			else// Y
				Pathfinder::checkSight7(map, player, pos);
		}
	}
	else// GAUCHE
	{
		if (dir.y >= 0)// BAS
		{
			if (std::abs(dir.x) > std::abs(dir.y))// X
				Pathfinder::checkSight4(map, player, pos);
			else// Y
				Pathfinder::checkSight3(map, player, pos);

		}
		else// HAUT
		{
			if (std::abs(dir.x) > std::abs(dir.y))// X
				Pathfinder::checkSight5(map, player, pos);
			else// Y
				Pathfinder::checkSight6(map, player, pos);
		}
	}
}
