#include "Spell.h"

Spell::Spell(std::string effects, int po) :
	mPo(po)
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

void Spell::showRange(Map &map, sf::Vector2i player)
{
	int		i(mPo);

	for (int y(0); y <= mPo * 2; y++)
	{
		if (y > mPo)
			i--;
		for (int x(0); x <= mPo * 2; x++)
			if ((y <= mPo && x >= mPo - y && x <= mPo + y)
			|| (y > mPo && x >= mPo - i && x <= mPo + i))
				map.setCell(sf::Vector2i(player.x + x - mPo, player.y + y - mPo), 1, CellType::Range);
	}
}

void Spell::show(Map &map, sf::Vector2i player)
{
    Effect::Direction dir;
	sf::Vector2i pos(map.getMouseCell());
    int distX(pos.x - player.x);
    int distY(pos.y - player.y);

	map.clear(CellType::Zone);
	if (std::abs(distX) + std::abs(distY) <= mPo && !map.getCell(pos, CellType::Block))
	{
	    if (std::abs(distX) >= std::abs(distY))
	        dir = distX < 0 ? Effect::Left : Effect::Right;
	    else
	        dir = distY < 0 ? Effect::Up : Effect::Down;
	    for(auto effect = mEffects.begin(); effect != mEffects.end(); ++effect)
	        (*effect)->showEffectZone(map, pos.x, pos.y, dir);
	}
}

void Spell::use(Map &map, sf::Vector2i player)
{
    Effect::Direction dir;
	sf::Vector2i pos(map.getMouseCell());
    int distX(pos.x - player.x);
    int distY(pos.y - player.y);

    if (std::abs(distX) >= std::abs(distY))
        dir = distX < 0 ? Effect::Left : Effect::Right;
    else
        dir = distY < 0 ? Effect::Up : Effect::Down;
    for(auto effect = mEffects.begin(); effect != mEffects.end(); ++effect)
        (*effect)->showEffectZone(map, pos.x, pos.y, dir);
}

Spell::~Spell()
{
    mEffects.clear();
}
