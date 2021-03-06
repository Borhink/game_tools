#include <SFML/Graphics.hpp>
#include <iostream>
#include <functional>
#include <string>
#include "Debug.h"
#include "Effect.h"
#include "Spell.h"
#include "Movable.h"

#define TICK_PER_SECOND 1.0f / 60.0f
#define MAP_SIZE 20

void drawText(sf::RenderWindow *window, std::string txt, int x, int y, sf::Color color, int size)
{
	sf::Font font;
	sf::Text text;

	if (!font.loadFromFile("sansation.ttf"))
	{
		std::cout << "Error font not loaded!" << std::endl;
	}
	text.setFont(font);
	text.setString(txt);
	text.setCharacterSize(size);
	text.setColor(color);
	text.setPosition(x, y);
	window->draw(text);
}

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
	int**               game_map;
	Movable             player(10, 10);
    sf::Vector2i        pos(12, 10);
	Spell               spell("X2;V6");

    cell.setSize(sf::Vector2f(15, 15));
    cell.setOutlineColor(sf::Color::White);
    cell.setOutlineThickness(5);
    cell.setPosition(offset);

    game_map = (int**)malloc(sizeof(int*) * MAP_SIZE);
    for (int y(0); y < MAP_SIZE; y++)
    {
        game_map[y] = (int*)malloc(sizeof(int) * MAP_SIZE);
        for (int x(0); x < MAP_SIZE; x++)
            game_map[y][x] = 0;
    }
    player.goTo(sf::Vector2i(3, 18), game_map, MAP_SIZE);
    spell.use(20, game_map, player.getPos(), pos);

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
                    if (game_map[y][x] == 0)
                        cell.setOutlineColor(sf::Color::White);
                    else if (game_map[y][x] == 1)
                        cell.setOutlineColor(sf::Color::Red);
                    if (sf::Vector2i(x, y) == pos)
                        cell.setOutlineColor(sf::Color::Yellow);
                    if (game_map[y][x] == 10)
                        cell.setOutlineColor(sf::Color::Green);
                    cell.setPosition(offset.x + x * 28, offset.y + y * 28);
                    if (sf::Vector2i(x, y) == player.getPos())
                        cell.setOutlineColor(sf::Color::Blue);
                    window.draw(cell);
                }
            }
			drawText(&window, "FPS: " + Debug::to_str(fps), 2, 0, sf::Color::White, 15);
			drawText(&window, "UPS: " + Debug::to_str(ups), 2, 15, sf::Color::White, 15);
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
