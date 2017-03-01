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
        void use(Map &map, sf::Vector2i player, sf::Vector2i pos);
        void add_effect(std::string effect);
    private:
        std::vector<Effect*> mEffects;
};

#endif // SPELL_H
