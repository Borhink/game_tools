#ifndef MOVABLE_H
#define MOVABLE_H

#include "Entity.h"
#include "Debug.h"
#include <queue>

class Movable : public Entity
{
    public:
        Movable(int x = 0, int y = 0);
        virtual ~Movable();
        void goTo(sf::Vector2i pos, int **gameMap, int mapSize);

    protected:
        int isEmpty(int cell, int weight);
        int validCell(sf::Vector2i pos, int **gameMap, int mapSize, int weight);
		int	nextCell(sf::Vector2i cur, int **gameMap, int mapSize, int weight, std::queue<sf::Vector2i> &cells);
        int pathfinding(sf::Vector2i pos, int **gameMap, int mapSize);
        int getWeight(sf::Vector2i pos, int **gameMap, int mapSize);
        sf::Vector2i getPath(sf::Vector2i pos, int **gameMap, int mapSize);
        void clearPaths(int **gameMap, int mapSize);

    private:
};

#endif // MOVABLE_H
