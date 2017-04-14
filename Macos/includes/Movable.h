#ifndef MOVABLE_H
#define MOVABLE_H

#include "Entity.h"
#include "Debug.h"
#include "Map.h"

class Movable : public Entity
{
    public:
		Movable(int x = 0, int y = 0);
		Movable(int x = 0, int y = 0, int pm = 0);
		virtual ~Movable();
		void goTo(Map &map);
		int showPath(Map &map);
		int getPm(void) const;
		void setPm(int pm);

    private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		int mPm;
};

#endif // MOVABLE_H
