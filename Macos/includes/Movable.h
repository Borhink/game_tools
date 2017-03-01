#ifndef MOVABLE_H
#define MOVABLE_H

#include "Entity.h"
#include "Debug.h"
#include "Map.h"
#include <queue>
#include <vector>

class Movable : public Entity
{
    public:
        Movable(int x = 0, int y = 0);
        virtual ~Movable();
        void goTo(sf::Vector2i pos, Map &map);

    protected:
        // int isEmpty(int cell, int weight);
        int validCell(sf::Vector2i pos, std::vector<std::vector<int>> &gameMap, sf::Vector2i mapSize, int weight);
		int	nextCell(sf::Vector2i cur, std::vector<std::vector<int>> &gameMap, sf::Vector2i mapSize, int weight, std::queue<sf::Vector2i> &cells);
        int pathfinding(sf::Vector2i pos, std::vector<std::vector<int>> &gameMap, sf::Vector2i mapSize);
        int getWeight(sf::Vector2i pos, std::vector<std::vector<int>> &gameMap, sf::Vector2i mapSize);
        sf::Vector2i getPath(sf::Vector2i pos, std::vector<std::vector<int>> &gameMap, sf::Vector2i mapSize);
		void copyBlock(std::vector<std::vector<int>> &pathMap, Map &map);
        // void clearPaths(int **gameMap, int mapSize);

    private:
};

#endif // MOVABLE_H
