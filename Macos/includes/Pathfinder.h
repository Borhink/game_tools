#ifndef PATHFINDER_H
#define PATHFINDER_H

#include "Debug.h"
#include "Movable.h"
#include "Map.h"
#include <queue>
#include <vector>
#include <SFML/Graphics.hpp>

class Pathfinder
{
    public:
        static int getPath(Map &map, Movable &movable);
		static void checkSight(Map &map, sf::Vector2i pos, sf::Vector2i player);

    private:
		static void copyBlock(std::vector<std::vector<int>> &pathMap, Map &map);
		static int getCellDist(Map &map, sf::Vector2i movablePos);
		static int validCell(sf::Vector2i pos, std::vector<std::vector<int>> &gameMap, sf::Vector2i mapSize, int weight);
		static int	nextCell(sf::Vector2i cur, std::vector<std::vector<int>> &gameMap, sf::Vector2i mapSize, int weight, std::queue<sf::Vector2i> &cells, sf::Vector2i playerPos);
		static int getWeight(sf::Vector2i pos, std::vector<std::vector<int>> &gameMap, sf::Vector2i mapSize);
		static sf::Vector2i getPath(sf::Vector2i pos, std::vector<std::vector<int>> &gameMap, sf::Vector2i mapSize);
		static int pathfinding(sf::Vector2i pos, std::vector<std::vector<int>> &gameMap, sf::Vector2i mapSize, sf::Vector2i movablePos);
		static void checkSight1(Map &map, sf::Vector2i p1, sf::Vector2i p2);
		static void checkSight2(Map &map, sf::Vector2i p1, sf::Vector2i p2);
		static void checkSight3(Map &map, sf::Vector2i p1, sf::Vector2i p2);
		static void checkSight4(Map &map, sf::Vector2i p1, sf::Vector2i p2);
		static void checkSight5(Map &map, sf::Vector2i p1, sf::Vector2i p2);
		static void checkSight6(Map &map, sf::Vector2i p1, sf::Vector2i p2);
		static void checkSight7(Map &map, sf::Vector2i p1, sf::Vector2i p2);
		static void checkSight8(Map &map, sf::Vector2i p1, sf::Vector2i p2);
		static bool inCell(sf::Vector2i pos, sf::Vector2i cell);
};

#endif // PATHFINDER_H
