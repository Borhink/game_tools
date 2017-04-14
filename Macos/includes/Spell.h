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
        Spell(std::string effects);
        virtual ~Spell();
        void show(Map &map, sf::Vector2i player);
        void use(Map &map, sf::Vector2i player);
        void add_effect(std::string effect);
    private:
        std::vector<Effect*> mEffects;
		// int mPo;
		// int mPa;
};

#endif // SPELL_H
