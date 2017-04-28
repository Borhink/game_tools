#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>

class Player;
class Input;

enum CellType
{
	None = 0,
	Block = 1,
	Path = 2,
	View = 4,
	Zone = 8,
	Player = 16,
	Range = 32,

	TypeCount = 64
};

class Map : public sf::Drawable
{
	public:

		Map(sf::Vector2i size);
		virtual ~Map();
		void update(Input &input, int type);
		sf::Vector2i mouseToPos(sf::Vector2i mouse) const;
		sf::Vector2i mouseToPos(int x, int y) const;
		bool mouseInBounds(int x, int y) const;
		bool mouseInBounds(sf::Vector2i pos) const;
		bool inBounds(sf::Vector2i pos) const;
		bool inBounds(int x, int y) const;
		bool mouseCellChanged(void);
		void clear(CellType type = CellType::None);
		int getCell(sf::Vector2i pos, int type = CellType::None) const;
		int getCell(int x, int y, int type = CellType::None) const;
		void setCell(sf::Vector2i pos, int val, CellType type = CellType::None);
		void setCell(int x, int y, int val, CellType type = CellType::None);
		int getPlayer(sf::Vector2i pos) const;
		int getPlayer(int x, int y) const;
		void setPlayer(sf::Vector2i pos, int val);
		void setPlayer(int x, int y, int val);
		sf::Vector2i getSize() const;
		void setMouseCell(int x, int y);
		void setMouseCell(sf::Vector2i mouse);
		sf::Vector2i getMouseCell(void) const;
		void setCellPressed(sf::Vector2i mouse);
		sf::Vector2i getCellPressed(void) const;
		bool validClic() const;

		int				**mRange;
	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		int				**mCell;
		int				**mPlayer;
		sf::Vector2i	mSize;
		sf::Vector2i	mMouseCell;
		sf::Vector2i	mCellPressed;
		bool			mMouseCellChanged;
};

#endif // MAP_H
