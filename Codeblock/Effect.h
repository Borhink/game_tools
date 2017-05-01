#ifndef EFFECT_H
#define EFFECT_H

#include <vector>
#include <string>
#include <stdlib.h>
#include <SFML/Graphics.hpp>
#include "Debug.h"

class Effect
{
    public:
        enum Direction
        {
            Right = 0,
            Down,
            Left,
            Up
        };

        Effect(std::string zone);
        void createEffectZone(std::string);
        void applyEffect(int mapSize, int **map, int px, int py, Direction dir);
        virtual ~Effect();
    protected:
    private:
        int*            mZone;
        int             mSize;
        sf::Vector2i    mOrigin;
};

#endif // EFFECT_H
