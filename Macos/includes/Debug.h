#ifndef DEBUG_H
#define DEBUG_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <ctime>
#include <SFML/Graphics.hpp>
#include "Map.h"

#define DEBUG 0

class Debug
{
    public:
        Debug();
        virtual ~Debug();
		static void drawText(sf::RenderWindow *window, std::string txt, int x, int y, sf::Color color, int size);
        static void log(std::string log);
        static std::string to_str(size_t n);
        static std::string to_str(sf::Vector2i v);
        static std::string to_str(std::vector<std::vector<int>> map, sf::Vector2i mapSize);
        static std::string to_str(Map &map);
        static std::string to_str(int *map, int mapSize);
};

#endif // DEBUG_H
