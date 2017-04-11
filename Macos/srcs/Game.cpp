#include "Game.h"

Game::Game(sf::RenderWindow	*window) :
	mInput(new Input()),
	mWindow(window),
	mMap(new Map(sf::Vector2i(20, 20))),
	mPlayer(new class Player(10, 10, 12))
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
		if (mInput->getEntry(Input::MLeft) && mMap->mouseInBounds(mInput->getMouse()))
			mMap->setCellPressed(mInput->getMouse().x, mInput->getMouse().y);
	}
	if (event->type == sf::Event::MouseButtonReleased)
	{
		mInput->mouseReleased(event->mouseButton.button, event->mouseButton.x, event->mouseButton.y);
		if (mMap->getMouseCell() == mMap->getCellPressed())
			mPlayer->goTo(mMap->getMouseCell(), *mMap);
		else
			mPlayer->showPath(mMap->getMouseCell(), *mMap);
	}
}

void	Game::inputHandler(void)
{

	if (mInput->mouseHasMoved())
	{
		if (mMap->isMouseCellChanged(mInput->getMouse().x, mInput->getMouse().y, true) && !mInput->getEntry(Input::MLeft))
			mPlayer->showPath(mMap->getMouseCell(), *mMap);
	}
	if (mInput->getEntry(Input::MRight))
			mMap->setCell(mMap->getMouseCell(), 1, CellType::Block);
	if (mInput->getEntry(Input::MMiddle))
		mMap->setCell(mMap->getMouseCell(), 0, CellType::Block);
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
