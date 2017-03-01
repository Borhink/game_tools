#include "Effect.h"

Effect::Effect(std::string zone)
{
    Debug::log("Effect::Effect(\"" + zone + "\")");
    this->createEffectZone(zone);
}

/*
** ========== createEffectZone ==========
** Creer les zones d'effets pour les sorts et autres actions
** Format : [Type][Taille]
** L -> Ligne droite
** C -> Losange
** V -> Cone
** X -> Croix
** Q -> Carre
** S -> Ligne parralelle
** O -> Losange contour
** A -> Carre contour
** T -> Zone en T inversee
** Exemple : C3 (Losange taille 3)
** ======================================
*/

void Effect::createEffectZone(std::string zone)
{
    int i(0);

    switch (zone[0])
    {
        case 'L':
            mSize = atoi(&zone[1]);
            mZone = (int*)malloc(sizeof(int) * (mSize * mSize));
            for (int i(0); i < mSize * mSize; i++)
                mZone[i] = (i < mSize ? 1 : 0);
            mOrigin = sf::Vector2i(0, 0);
        break;
        case 'C':
            mSize = 1 + (atoi(&zone[1]) * 2);
            i = mSize / 2;
            mZone = (int*)malloc(sizeof(int) * (mSize * mSize));
            for (int y(0); y < mSize; y++)
            {
                if (y > mSize / 2)
                    i--;
                for (int x(0); x < mSize; x++)
                    if ((y <= mSize / 2 && x >= mSize / 2 - y && x <= mSize / 2 + y)
                        || (y > mSize / 2 && x >= mSize / 2 - i && x <= mSize / 2 + i))
                        mZone[y * mSize + x] = 1;
                    else
                        mZone[y * mSize + x] = 0;
            }
            mOrigin = sf::Vector2i(mSize / 2, mSize / 2);
        break;
        case 'V':
            mSize = 1 + (atoi(&zone[1]) * 2);
            mZone = (int*)malloc(sizeof(int) * (mSize * mSize));
            for (int y(0); y < mSize; y++)
                for (int x(0); x < mSize; x++)
                    if (y <= mSize / 2 && x >= mSize / 2 - (y + 1) / 2 && x <= mSize / 2 + (y + 1) / 2)
                        mZone[x * mSize + y] = 1;
                    else
                        mZone[x * mSize + y] = 0;
            mOrigin = sf::Vector2i(0, mSize / 2);
        break;
        case 'X':
            mSize = 1 + (atoi(&zone[1]) * 2);
            mZone = (int*)malloc(sizeof(int) * (mSize * mSize));
            for (int y(0); y < mSize; y++)
                for (int x(0); x < mSize; x++)
                    if (y == mSize / 2 || x == mSize / 2)
                        mZone[y * mSize + x] = 1;
                    else
                        mZone[y * mSize + x] = 0;
            mOrigin = sf::Vector2i(mSize / 2, mSize / 2);
        break;
        case 'Q':
            mSize = 1 + (atoi(&zone[1]) * 2);
            mZone = (int*)malloc(sizeof(int) * (mSize * mSize));
            for (int y(0); y < mSize; y++)
                for (int x(0); x < mSize; x++)
                    mZone[y * mSize + x] = 1;
            mOrigin = sf::Vector2i(mSize / 2, mSize / 2);
        break;
        case 'S':
            mSize = 1 + (atoi(&zone[1]) * 2);
            mZone = (int*)malloc(sizeof(int) * (mSize * mSize));
            for (int i(0); i < mSize * mSize; i++)
                mZone[i] = (!(i % mSize) ? 1 : 0);
            mOrigin = sf::Vector2i(0, mSize / 2);
        break;
        case 'O':
            mSize = 1 + (atoi(&zone[1]) * 2);
            i = mSize / 2;
            mZone = (int*)malloc(sizeof(int) * (mSize * mSize));
            for (int y(0); y < mSize; y++)
            {
                if (y > mSize / 2)
                    i--;
                for (int x(0); x < mSize; x++)
                    if ((y <= mSize / 2 && (x == mSize / 2 - y || x == mSize / 2 + y))
                        || (y > mSize / 2 && (x == mSize / 2 - i || x == mSize / 2 + i)))
                        mZone[y * mSize + x] = 1;
                    else
                        mZone[y * mSize + x] = 0;
            }
            mOrigin = sf::Vector2i(mSize / 2, mSize / 2);
        break;
        case 'A':
            mSize = 1 + (atoi(&zone[1]) * 2);
            mZone = (int*)malloc(sizeof(int) * (mSize * mSize));
            for (int y(0); y < mSize; y++)
                for (int x(0); x < mSize; x++)
                    if (!x || !y || y == mSize - 1 || x == mSize - 1)
                        mZone[y * mSize + x] = 1;
                    else
                        mZone[y * mSize + x] = 0;
            mOrigin = sf::Vector2i(mSize / 2, mSize / 2);
        break;
        case 'T':
            mSize = 1 + (atoi(&zone[1]) * 2);
            mZone = (int*)malloc(sizeof(int) * (mSize * mSize));
            for (int y(0); y < mSize; y++)
                for (int x(0); x < mSize; x++)
                    if (!x || (y == mSize / 2 && x <= mSize / 2))
                        mZone[y * mSize + x] = 1;
                    else
                        mZone[y * mSize + x] = 0;
            mOrigin = sf::Vector2i(0, mSize / 2);
        break;
        default:
            mSize = 1;
            mZone = (int*)malloc(sizeof(int) * (1));
            mZone[0] = 1;
            mOrigin = sf::Vector2i(0, 0);
        break;
    }
}

void Effect::applyEffect(Map &map, int px, int py, Direction dir)
{
    sf::Vector2i	pos;
	sf::Vector2i	mapSize(map.getSize());

    Debug::log("Effect::applyEffect: dir = " + Debug::to_str(dir));
    Debug::log("Effect::applyEffect: px = " + Debug::to_str(px));
    Debug::log("Effect::applyEffect: py = " + Debug::to_str(py));
    Debug::log("Effect::applyEffect: mapSize = " + Debug::to_str(mapSize));
    Debug::log("Effect::applyEffect: map = " + Debug::to_str(map));
    Debug::log("Effect::applyEffect: mSize = " + Debug::to_str(mSize));
    Debug::log("Effect::applyEffect: mZone = " + Debug::to_str(mZone, mSize));
    for (int y(0); y < mSize; y++)
    {
        for (int x(0); x < mSize; x++)
        {
            if (mZone[y * mSize + x] == 1)
            {
                switch (dir)
                {
                    case Left:
                        pos = sf::Vector2i(px - x + mOrigin.x, y + py - mOrigin.y);
                        if (pos.x >= 0 && pos.y >= 0 && pos.x < mapSize.x && pos.y < mapSize.y)
							map.setCell(pos, mZone[y * mSize + x], CellType::Zone);
                            // map[pos.y][pos.x] = mZone[y * mSize + x];
                    break;
                    case Up:
                        pos = sf::Vector2i(px + y - mOrigin.y, py - x + mOrigin.x);
                        if (pos.x >= 0 && pos.y >= 0 && pos.x < mapSize.x && pos.y < mapSize.y)
							map.setCell(pos, mZone[y * mSize + x], CellType::Zone);
                            // map[pos.y][pos.x] = mZone[y * mSize + x];
                    break;
                    case Down:
                        pos = sf::Vector2i(px + y - mOrigin.y, py + x - mOrigin.x);
                        if (pos.x >= 0 && pos.y >= 0 && pos.x < mapSize.x && pos.y < mapSize.y)
							map.setCell(pos, mZone[y * mSize + x], CellType::Zone);
                            // map[pos.y][pos.x] = mZone[y * mSize + x];
                    break;
                    default:
                        pos = sf::Vector2i(px + x - mOrigin.x, py + y - mOrigin.y);
                        if (pos.x >= 0 && pos.y >= 0 && pos.x < mapSize.x && pos.y < mapSize.y)
							map.setCell(pos, mZone[y * mSize + x], CellType::Zone);
                            // map[pos.y][pos.x] = mZone[y * mSize + x];
                    break;
                }
            }
        }
    }
}

Effect::~Effect()
{
    free(mZone);
}
