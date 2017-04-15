#ifndef PLAYER_H
#define PLAYER_H

#include "Movable.h"
#include "Debug.h"
#include "Spell.h"
#include <queue>
#include <vector>
#include <SFML/Graphics.hpp>

class Input;
class Map;

class Player : public Movable
{
	public:
		Player(int x = 0, int y = 0, int pm = 3);
		virtual ~Player();
		void update(Input &input, Map &map, int type);
		bool showSpell(Map &map);
		void useSpell(Map &map);
		void updateSelectedSpell(int id, Map &map);
		void setSelectedSpell(int id);
		int getSelectedSpell(void) const;

	protected:

	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		Spell *mSpell;
		int mSelectSpell;
};

#endif // PLAYER_H
