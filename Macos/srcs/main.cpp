#include <SFML/Graphics.hpp>
#include <iostream>
#include <functional>
#include <string>
#include "Debug.h"
#include "Effect.h"
#include "Spell.h"
#include "Movable.h"
#include "Map.h"
#include "Game.h"

#include <stdlib.h>

#define TICK_PER_SECOND 1.0f / 60.0f

int main()
{
    Debug::log("=== LAUNCHING THE GAME ===");
    sf::RenderWindow    window(sf::VideoMode(1024 * 4 / 3, 1024), "Map manager");
    sf::Event		    event;
	Game				game(&window);
	sf::Clock			updateTime;
	sf::Clock			timer;
	int					frames(0);
	int					fps(0);
	int					ticks(0);
	int					ups(0);
	float				elapsed(0);


	while (window.isOpen())
    {
		elapsed += updateTime.getElapsedTime().asSeconds();
		updateTime.restart();
		if (elapsed >= TICK_PER_SECOND)
		{
			game.update(&event);
			elapsed -= TICK_PER_SECOND;
			ticks++;
		}
		else
		{
			window.clear(sf::Color::Black);
			game.render();
			// Debug::drawText(&window, "FPS: " + Debug::to_str(fps), 2, 0, sf::Color::White, 15);
			// Debug::drawText(&window, "UPS: " + Debug::to_str(ups), 2, 15, sf::Color::White, 15);
			window.display();
			frames++;
		}
		if (timer.getElapsedTime().asSeconds() >= 1.0f)
		{
			fps = frames;
			frames = 0;
			ups = ticks;
			ticks = 0;
			timer.restart();
		}
    }
    return (0);
}
