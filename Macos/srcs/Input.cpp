/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Input.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/10 22:58:00 by qhonore           #+#    #+#             */
/*   Updated: 2017/04/07 17:37:29 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Input.h"
#include <iostream>

Input::Input() :
	mMouseX(0),
	mMouseY(0),
	mMouseMoved(false)
{
	for (int i(0); i < Entry::EntryCount; i++)
		mEntries[i] = false;
}

void	Input::keyPressed(sf::Keyboard::Key key)
{
	if (key >= 0 && key < sf::Keyboard::Key::KeyCount)
		mEntries[key] = true;
}

void	Input::keyReleased(sf::Keyboard::Key key)
{
	if (key >= 0 && key < sf::Keyboard::Key::KeyCount)
		mEntries[key] = false;
}

bool	Input::getKey(sf::Keyboard::Key key)
{
	if (key >= 0 && key < sf::Keyboard::Key::KeyCount)
		return (mEntries[key]);
	return (false);
}

void	Input::setKey(sf::Keyboard::Key key, bool val)
{
	if (key >= 0 && key < sf::Keyboard::Key::KeyCount)
		mEntries[key] = val;
}

bool	Input::getMouse(sf::Mouse::Button button)
{
	if (button >= 0 && button < sf::Mouse::Button::ButtonCount)
		return (mEntries[button + Entry::MLeft]);
	return (false);
}

void	Input::setMouse(sf::Mouse::Button button, bool val)
{
	if (button >= 0 && button < sf::Mouse::Button::ButtonCount)
		mEntries[button + Entry::MLeft] = val;
}

bool	Input::getEntry(Entry entry)
{
	if (entry >= 0 && entry < Entry::EntryCount)
		return (mEntries[entry]);
	return (false);
}

void	Input::setEntry(Entry entry, bool val)
{
	if (entry >= 0 && entry < Entry::EntryCount)
		mEntries[entry] = val;
}

void	Input::clearEntries(void)
{
	for (int i(0); i < Entry::EntryCount; i++)
		mEntries[i] = false;
}

void	Input::mousePressed(sf::Mouse::Button button, int x, int y)
{
	if (button >= 0 && button < sf::Mouse::Button::ButtonCount)
		mEntries[button + Entry::MLeft] = true;
	mMouseX = x;
	mMouseY = y;
}

void	Input::mouseReleased(sf::Mouse::Button button, int x, int y)
{
	if (button >= 0 && button < sf::Mouse::Button::ButtonCount)
		mEntries[button + Entry::MLeft] = false;
	mMouseX = x;
	mMouseY = y;
}

void	Input::mouseMoved(int x, int y)
{
	mMouseMoved = true;
	mMouseX = x;
	mMouseY = y;
}

int		Input::getMouseX(void)
{
	return (mMouseX);
}

int		Input::getMouseY(void)
{
	return (mMouseY);
}

bool	Input::mouseHasMoved(void)
{
	if (mMouseMoved)
	{
		mMouseMoved = false;
		return (true);
	}
	return (false);
}
