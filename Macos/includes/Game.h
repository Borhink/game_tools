#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Input.h"
#include "Map.h"
#include "Player.h"

class Game
{
    public:
        Game(sf::RenderWindow *window);
        virtual ~Game();
		void render(void);
		void update(sf::Event *event);
		void inputHandler(void);
		class Player *getPlayer();
		Map *getMap();

	private:
		Input *mInput;
		sf::RenderWindow *mWindow;
		Map *mMap;
		class Player *mPlayer;

};

#endif // GAME_H
