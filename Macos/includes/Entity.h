#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>

class Entity : public sf::Drawable
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
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif // ENTITY_H
