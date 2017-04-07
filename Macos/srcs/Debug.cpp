#include "Debug.h"

Debug::Debug()
{
}

void Debug::drawText(sf::RenderWindow *window, std::string txt, int x, int y, sf::Color color, int size)
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
	text.setFillColor(color);
	text.setPosition(x, y);
	window->draw(text);
}

void Debug::log(std::string log)
{
    if (DEBUG)
    {
        time_t _tm = time(NULL);
        struct tm *curtime = localtime(&_tm);
        std::string date = asctime(curtime);
        date.pop_back();
		std::ofstream file;
		file.open("logs.txt", std::ofstream::app);
        file << date << ": " << log << std::endl;
        file.close();
    }
}

std::string Debug::to_str(size_t n)
{
    std::ostringstream s;
    s << n;
    return s.str();
}

std::string Debug::to_str(sf::Vector2i v)
{
    std::ostringstream s;
    s << v.y;
	s << "y, ";
	s << v.x;
	s << "x";
    return s.str();
}

std::string Debug::to_str(std::vector<std::vector<int>> map, sf::Vector2i mapSize)
{
    std::ostringstream s;

    s << std::endl;
    for (int y(0); y < mapSize.y; y++)
    {
        for (int x(0); x < mapSize.x; x++)
        {
            s << map[y][x];
            s << "\t";
        }
        if (y + 1 < mapSize.y)
            s << std::endl;
    }
    return s.str();
}

std::string Debug::to_str(Map &map)
{
    std::ostringstream	s;
	sf::Vector2i		mapSize(map.getSize());

    s << std::endl;
    for (int y(0); y < mapSize.y; y++)
    {
        for (int x(0); x < mapSize.x; x++)
        {
            s << map.getCell(x, y);
            s << "\t";
        }
        if (y + 1 < mapSize.y)
            s << std::endl;
    }
    return s.str();
}

std::string Debug::to_str(int *map, int mapSize)
{
    std::ostringstream s;

    s << std::endl;
    for (int y(0); y < mapSize; y++)
    {
        for (int x(0); x < mapSize; x++)
        {
            s << map[y * mapSize + x];
            s << "\t";
        }
        if (y + 1 < mapSize)
            s << std::endl;
    }
    return s.str();
}

Debug::~Debug()
{
    //dtor
}
