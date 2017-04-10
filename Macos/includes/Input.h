/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/10 22:54:27 by qhonore           #+#    #+#             */
/*   Updated: 2017/04/10 16:28:18 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_HPP
# define INPUT_HPP

# include <SFML/Graphics.hpp>

class Input
{
	public:
		enum Entry
		{
			Unknown = -1, ///< Unhandled key
			A = 0,        ///< The A key
			B,            ///< The B key
			C,            ///< The C key
			D,            ///< The D key
			E,            ///< The E key
			F,            ///< The F key
			G,            ///< The G key
			H,            ///< The H key
			I,            ///< The I key
			J,            ///< The J key
			K,            ///< The K key
			L,            ///< The L key
			M,            ///< The M key
			N,            ///< The N key
			O,            ///< The O key
			P,            ///< The P key
			Q,            ///< The Q key
			R,            ///< The R key
			S,            ///< The S key
			T,            ///< The T key
			U,            ///< The U key
			V,            ///< The V key
			W,            ///< The W key
			X,            ///< The X key
			Y,            ///< The Y key
			Z,            ///< The Z key
			Num0,         ///< The 0 key
			Num1,         ///< The 1 key
			Num2,         ///< The 2 key
			Num3,         ///< The 3 key
			Num4,         ///< The 4 key
			Num5,         ///< The 5 key
			Num6,         ///< The 6 key
			Num7,         ///< The 7 key
			Num8,         ///< The 8 key
			Num9,         ///< The 9 key
			Escape,       ///< The Escape key
			LControl,     ///< The left Control key
			LShift,       ///< The left Shift key
			LAlt,         ///< The left Alt key
			LSystem,      ///< The left OS specific key: window (Windows and Linux), apple (MacOS X), ...
			RControl,     ///< The right Control key
			RShift,       ///< The right Shift key
			RAlt,         ///< The right Alt key
			RSystem,      ///< The right OS specific key: window (Windows and Linux), apple (MacOS X), ...
			Menu,         ///< The Menu key
			LBracket,     ///< The [ key
			RBracket,     ///< The ] key
			SemiColon,    ///< The ; key
			Comma,        ///< The , key
			Period,       ///< The . key
			Quote,        ///< The ' key
			Slash,        ///< The / key
			BackSlash,    ///< The \ key
			Tilde,        ///< The ~ key
			Equal,        ///< The = key
			Dash,         ///< The - key
			Space,        ///< The Space key
			Return,       ///< The Return key
			BackSpace,    ///< The Backspace key
			Tab,          ///< The Tabulation key
			PageUp,       ///< The Page up key
			PageDown,     ///< The Page down key
			End,          ///< The End key
			Home,         ///< The Home key
			Insert,       ///< The Insert key
			Delete,       ///< The Delete key
			Add,          ///< The + key
			Subtract,     ///< The - key
			Multiply,     ///< The * key
			Divide,       ///< The / key
			Left,         ///< Left arrow
			Right,        ///< Right arrow
			Up,           ///< Up arrow
			Down,         ///< Down arrow
			Numpad0,      ///< The numpad 0 key
			Numpad1,      ///< The numpad 1 key
			Numpad2,      ///< The numpad 2 key
			Numpad3,      ///< The numpad 3 key
			Numpad4,      ///< The numpad 4 key
			Numpad5,      ///< The numpad 5 key
			Numpad6,      ///< The numpad 6 key
			Numpad7,      ///< The numpad 7 key
			Numpad8,      ///< The numpad 8 key
			Numpad9,      ///< The numpad 9 key
			F1,           ///< The F1 key
			F2,           ///< The F2 key
			F3,           ///< The F3 key
			F4,           ///< The F4 key
			F5,           ///< The F5 key
			F6,           ///< The F6 key
			F7,           ///< The F7 key
			F8,           ///< The F8 key
			F9,           ///< The F9 key
			F10,          ///< The F10 key
			F11,          ///< The F11 key
			F12,          ///< The F12 key
			F13,          ///< The F13 key
			F14,          ///< The F14 key
			F15,          ///< The F15 key
			Pause,        ///< The Pause key
			MLeft,        ///< The left mouse button
			MRight,       ///< The right mouse button
			MMiddle,      ///< The middle (wheel) mouse button
			MXButton1,    ///< The first extra mouse button
			MXButton2,    ///< The second extra mouse button
			//MVWheel,      ///< The vertical wheel
			//MHWheel,       ///< The horizontal wheel

			EntryCount      ///< Keep last -- the total number of inputs
		};

		Input();
		void			keyPressed(sf::Keyboard::Key key);
		void			keyReleased(sf::Keyboard::Key key);
		bool			getKey(sf::Keyboard::Key key);
		void			setKey(sf::Keyboard::Key key, bool val);
		bool			getMouseButton(sf::Mouse::Button button);
		void			setMouseButton(sf::Mouse::Button button, bool val);
		bool			getEntry(Entry entry);
		void			setEntry(Entry entry, bool val);
		void			clearEntries(void);
		void			mousePressed(sf::Mouse::Button button, int x, int y);
		void			mouseReleased(sf::Mouse::Button button, int x, int y);
		void			mouseMoved(int x, int y);
		sf::Vector2i	getMouse(void);
		sf::Vector2i	getMousePressed(void);
		sf::Vector2i	getMouseReleased(void);
		bool			mouseHasMoved(void);

	private:
		bool			mEntries[Entry::EntryCount];
		sf::Vector2i	mMouse;
		bool			mMouseMoved;
		sf::Vector2i	mMousePressed;
		sf::Vector2i	mMouseReleased;
};

#endif
