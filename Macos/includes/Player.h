#ifndef PLAYER_H
#define PLAYER_H

#include "Movable.h"
#include "Debug.h"
#include "Map.h"
#include "Spell.h"
#include <queue>
#include <vector>

class Player : public Movable
{
	public:
		Player(int x = 0, int y = 0);
		Player(int x = 0, int y = 0, int pm = 3);
		virtual ~Player();
		void useSpell(Map &map, sf::Vector2i pos);

	protected:

	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		Spell *mSpell;
};

#endif // PLAYER_H
