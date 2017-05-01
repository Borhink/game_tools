#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>

class Entity
{
    public:
        Entity(int x = 0, int y = 0);
        virtual ~Entity();
        sf::Vector2i getPos();
        void setPos(sf::Vector2i pos);
        void setPos(int x, int y);

    protected:
        sf::Vector2i mPos;

    private:
};

#endif // ENTITY_H
