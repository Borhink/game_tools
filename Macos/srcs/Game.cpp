#include "Game.h"

Game::Game(sf::RenderWindow	*window) :
	mInput(new Input()),
	mWindow(window),
	mMap(new Map(sf::Vector2i(30, 25))),
	mPlayer(new class Player(10, 10, 7))
{
    //ctor
}

void	Game::render(void)
{
	mWindow->draw(*mMap);
	mWindow->draw(*mPlayer);
}

void	Game::update(sf::Event *event)
{
	while (mWindow->pollEvent(*event))
	{
		if (event->type == sf::Event::Closed)
			mWindow->close();
		if (event->type == sf::Event::KeyPressed)
			mInput->keyPressed(event->key.code);
		if (event->type == sf::Event::KeyReleased)
			mInput->keyReleased(event->key.code);
		if (event->type == sf::Event::MouseMoved)
			mInput->mouseMoved(event->mouseMove.x, event->mouseMove.y);
		mouseClicHandler(event);
	}
	inputHandler();
}

void	Game::mouseClicHandler(sf::Event *event)
{
	if (event->type == sf::Event::MouseButtonPressed)
	{
		mInput->mousePressed(event->mouseButton.button, event->mouseButton.x, event->mouseButton.y);
		mMap->update(*mInput, event->type);
	}
	if (event->type == sf::Event::MouseButtonReleased)
	{
		mInput->mouseReleased(event->mouseButton.button, event->mouseButton.x, event->mouseButton.y);
		mPlayer->update(*mInput, *mMap, event->type);
	}
}

void	Game::inputHandler(void)
{
	mMap->update(*mInput, -1);
	mPlayer->update(*mInput, *mMap, sf::Event::MouseMoved);
}

class Player *Game::getPlayer()
{
	return (mPlayer);
}

Map *Game::getMap()
{
	return (mMap);
}

Game::~Game()
{
    //dtor
}
