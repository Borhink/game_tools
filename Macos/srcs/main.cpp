#include <SFML/Graphics.hpp>
#include <iostream>
#include <functional>
#include <string>
#include "Debug.h"
#include "Effect.h"
#include "Spell.h"
#include "Movable.h"
#include "Map.h"

#define TICK_PER_SECOND 1.0f / 60.0f

int main()
{
    Debug::log("=== LAUNCHING THE GAME ===");
    sf::RenderWindow    window(sf::VideoMode(580, 615), "Map manager");
    sf::Event		    event;
    sf::RectangleShape  cell;
    sf::Clock			updateTime;
	sf::Clock			timer;
	int			    	frames(0);
	int			    	fps(0);
	int			    	ticks(0);
	int			    	ups(0);
	float		    	elapsed(0);
	sf::Vector2f        offset(15, 50);
	Map					map(sf::Vector2i(20, 20));
	Movable				player(10, 10);
    sf::Vector2i		pos(12, 10);//Spell pos
	Spell				spell("X2;V6");

	cell.setSize(sf::Vector2f(15, 15));
	cell.setOutlineColor(sf::Color::White);
	cell.setOutlineThickness(5);
	cell.setPosition(offset);

	player.goTo(sf::Vector2i(3, 18), map);
	spell.use(map, player.getPos(), pos);

	while (window.isOpen())
	{
		elapsed += updateTime.getElapsedTime().asSeconds();
		updateTime.restart();
		if (elapsed >= TICK_PER_SECOND)
		{
			//game update
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}
			elapsed -= TICK_PER_SECOND;
			ticks++;
		}
		else
		{
			//game render
			window.clear(sf::Color::Black);
			for (int y(0); y < 20; y++)
			{
				for (int x(0); x < 20; x++)
				{
					if (map.getCell(x, y, CellType::Block))//Block sur la map
						cell.setOutlineColor(sf::Color(155, 155, 155, 255));
					else
						cell.setOutlineColor(sf::Color::White);//Vide
					if (map.getCell(x, y, CellType::Zone))//Zone de sort
						cell.setOutlineColor(sf::Color::Red);
					if (sf::Vector2i(x, y) == pos)//Position du sort lancé
						cell.setOutlineColor(sf::Color::Yellow);
					if (map.getCell(x, y, CellType::Path))//Chemin pathfinding
						cell.setOutlineColor(sf::Color::Green);
					if (sf::Vector2i(x, y) == player.getPos())//Position joueur
						cell.setOutlineColor(sf::Color::Blue);
					cell.setPosition(offset.x + x * 28, offset.y + y * 28);
					window.draw(cell);
				}
			}
			Debug::drawText(&window, "FPS: " + Debug::to_str(fps), 2, 0, sf::Color::White, 15);
			Debug::drawText(&window, "UPS: " + Debug::to_str(ups), 2, 15, sf::Color::White, 15);
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
}
