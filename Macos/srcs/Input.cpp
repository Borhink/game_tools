/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Input.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/10 22:58:00 by qhonore           #+#    #+#             */
/*   Updated: 2017/04/10 16:29:23 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Input.h"
#include <iostream>

Input::Input() :
	mMouse(0, 0),
	mMouseMoved(false),
	mMousePressed(0, 0),
	mMouseReleased(0, 0)
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

bool	Input::getMouseButton(sf::Mouse::Button button)
{
	if (button >= 0 && button < sf::Mouse::Button::ButtonCount)
		return (mEntries[button + Entry::MLeft]);
	return (false);
}

void	Input::setMouseButton(sf::Mouse::Button button, bool val)
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
	mMousePressed.x = x;
	mMousePressed.y = y;
}

void	Input::mouseReleased(sf::Mouse::Button button, int x, int y)
{
	if (button >= 0 && button < sf::Mouse::Button::ButtonCount)
		mEntries[button + Entry::MLeft] = false;
	mMouseReleased.x = x;
	mMouseReleased.y = y;
}

void	Input::mouseMoved(int x, int y)
{
	mMouseMoved = true;
	mMouse.x = x;
	mMouse.y = y;
}

sf::Vector2i	Input::getMouse(void)
{
	return (mMouse);
}

sf::Vector2i	Input::getMousePressed(void)
{
	return (mMousePressed);
}

sf::Vector2i	Input::getMouseReleased(void)
{
	return (mMouseReleased);
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
