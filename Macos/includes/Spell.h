#ifndef SPELL_H
#define SPELL_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Effect.h"
#include "Debug.h"
#include "Map.h"


class Spell
{
    public:
        Spell(std::string effects, int po);
        virtual ~Spell();
		void showRange(Map &map, sf::Vector2i player);
        void show(Map &map, sf::Vector2i player);
        void use(Map &map, sf::Vector2i player);
        void add_effect(std::string effect);
    private:
		void adjustSight(Map &map, sf::Vector2i player);

        std::vector<Effect*> mEffects;
		int mPo;
		// int mPa;
};

#endif // SPELL_H
