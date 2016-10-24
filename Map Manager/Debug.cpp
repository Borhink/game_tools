#include "Debug.h"

Debug::Debug()
{
    //ctor
}

void Debug::log(std::string log)
{
    if (DEBUG)
    {
        time_t _tm = time(NULL);
        struct tm *curtime = localtime(&_tm);
        std::string date = asctime(curtime);
        date.pop_back();
        std::ofstream myfile;
        myfile.open("logs.txt", std::ios_base::app);
        myfile << date << ": " << log << std::endl;
        myfile.close();
    }
}

std::string Debug::to_str(size_t n)
{
    std::ostringstream s;
    s << n;
    return s.str();
}

std::string Debug::to_str(int **map, size_t mapSize)
{
    std::ostringstream s;

    s << std::endl;
    for (int y(0); y < mapSize; y++)
    {
        for (int x(0); x < mapSize; x++)
        {
            s << map[y][x];
            s << " ";
        }
        if (y + 1 < mapSize)
            s << std::endl;
    }
    return s.str();
}

std::string Debug::to_str(int *map, size_t mapSize)
{
    std::ostringstream s;

    s << std::endl;
    for (int y(0); y < mapSize; y++)
    {
        for (int x(0); x < mapSize; x++)
        {
            s << map[y * mapSize + x];
            s << " ";
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
