#ifndef EFFECT_H
#define EFFECT_H

#include <vector>
#include <string>
#include <stdlib.h>
#include <SFML/Graphics.hpp>
#include "Debug.h"
#include "Map.h"

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

		enum Type
		{
			None = 0,
			Damage,
			Heal,

			TypeCount
		};

        Effect(std::string zone);
        void createEffectZone(std::string);
        void applyEffect(Map &map, int px, int py, Direction dir);
        void showEffectZone(Map &map, int px, int py, Direction dir);
        virtual ~Effect();
    protected:
    private:
        int*            mZone;
        int             mSize;
        sf::Vector2i    mOrigin;
		Type			mType;
		int				mMin;
		int				mMax;
};

#endif // EFFECT_H
