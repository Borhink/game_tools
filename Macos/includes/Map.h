#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>

enum CellType
{
	None = 0,
	Block = 1,
	Path = 2,
	View = 4,
	Zone = 8,
	Player = 16,

	TypeCount = 32
};

class Map
{
	public:

		Map(sf::Vector2i size);
		virtual ~Map();
		bool inBounds(sf::Vector2i pos) const;
		bool inBounds(int x, int y) const;
		int getCell(sf::Vector2i pos, CellType type = CellType::None) const;
		int getCell(int x, int y, CellType type = CellType::None) const;
		void setCell(sf::Vector2i pos, int val, CellType type = CellType::None);
		void setCell(int x, int y, int val, CellType type = CellType::None);
		int getPlayer(sf::Vector2i pos) const;
		int getPlayer(int x, int y) const;
		void setPlayer(sf::Vector2i pos, int val);
		void setPlayer(int x, int y, int val);
		sf::Vector2i getSize() const;

	private:
		int				**mCell;
		int				**mPlayer;
		sf::Vector2i	mSize;
};

#endif // MAP_H
