#include "Spell.h"

Spell::Spell(std::string effects)
{
    size_t pos = 0;

    while ((pos = effects.find(';')) != std::string::npos)
    {
        add_effect(effects.substr(0, pos));
        effects.erase(0, pos + 1);
    }
    add_effect(effects);
}

void Spell::add_effect(std::string effectArgs)
{
    mEffects.push_back(new Effect(effectArgs));
}

void Spell::use(Map &map, sf::Vector2i player, sf::Vector2i pos)
{
    Effect::Direction dir;
    int distX = pos.x - player.x;
    int distY = pos.y - player.y;

    if (std::abs(distX) >= std::abs(distY))
        dir = distX < 0 ? Effect::Left : Effect::Right;
    else
        dir = distY < 0 ? Effect::Up : Effect::Down;
    for(auto effect = mEffects.begin(); effect != mEffects.end(); ++effect)
        (*effect)->applyEffect(map, pos.x, pos.y, dir);
}

Spell::~Spell()
{
    mEffects.clear();
}
