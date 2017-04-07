#include "Game.h"

Game::Game(sf::RenderWindow	*window) :
	mInput(new Input()),
	mWindow(window),
	mMap(new Map(sf::Vector2i(20, 20))),
	mPlayer(new class Player(10, 10))
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
		if (event->type == sf::Event::MouseButtonPressed)
			mInput->mousePressed(event->mouseButton.button, event->mouseButton.x, event->mouseButton.y);
		if (event->type == sf::Event::MouseButtonReleased)
			mInput->mouseReleased(event->mouseButton.button, event->mouseButton.x, event->mouseButton.y);
		if (event->type == sf::Event::MouseMoved)
			mInput->mouseMoved(event->mouseMove.x, event->mouseMove.y);
	}
	inputHandler();
}

void	Game::inputHandler(void)
{

	if (mInput->mouseHasMoved())
	{
		std::cout << "Mouse moved: x" << mInput->getMouseX() << " y" << mInput->getMouseY() << std::endl;
		// mInput->getMouseX() >= 15 &&)
	}
	// if (mCurMenu.top() == Game::MenuType::None)
	// 	mPlay->update(mInput, mKeyBind);
	// else
	// 	mMenus[mCurMenu.top()]->update(mInput, mKeyBind);
	// if (mInput->getEntry(mKeyBind->getEntry("START")))
	// {
	// 	if (mCurMenu.top() != Game::MenuType::Start && mCurMenu.top() != Game::MenuType::None)
	// 		mCurMenu.pop();
	// 	if (mCurMenu.top() == Game::MenuType::None)
	// 		mCurMenu.push(Game::MenuType::Pause);
	// 	mInput->setEntry(mKeyBind->getEntry("START"), false);
	// }
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
