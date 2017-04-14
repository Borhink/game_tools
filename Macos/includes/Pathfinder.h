#ifndef PATHFINDER_H
#define PATHFINDER_H

#include "Debug.h"
#include "Movable.h"
#include "Map.h"
#include <queue>
#include <vector>

class Pathfinder
{
    public:
        static int getPath(Map &map, Movable &movable);

    private:
		static void copyBlock(std::vector<std::vector<int>> &pathMap, Map &map);
		static int getCellDist(Map &map, sf::Vector2i movablePos);
		static int validCell(sf::Vector2i pos, std::vector<std::vector<int>> &gameMap, sf::Vector2i mapSize, int weight);
		static int	nextCell(sf::Vector2i cur, std::vector<std::vector<int>> &gameMap, sf::Vector2i mapSize, int weight, std::queue<sf::Vector2i> &cells, sf::Vector2i playerPos);
		static int getWeight(sf::Vector2i pos, std::vector<std::vector<int>> &gameMap, sf::Vector2i mapSize);
		static sf::Vector2i getPath(sf::Vector2i pos, std::vector<std::vector<int>> &gameMap, sf::Vector2i mapSize);
		static int pathfinding(sf::Vector2i pos, std::vector<std::vector<int>> &gameMap, sf::Vector2i mapSize, sf::Vector2i movablePos);
};

#endif // PATHFINDER_H
