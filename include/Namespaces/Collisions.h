#ifndef COLLISIONS_H
#define COLLISIONS_H

#define MAXLEVEL 2

#include <vector>

#include "../Ships/FighterShip.h"
#include "../Ships/GalacticShip.h"

#include "../Misc/Effects.h"

#include "../Drops/Drops.h"

#include "../Enemies/Enemy.h"

class Point {
  public:
    Point() { pos = -1; };
    Point(float x, float y) { this->x = x; this->y = y; }
    Point(float x, float y, int pos) { this->x = x; this->y = y; this->pos = pos;}
    
    float getX() {return x;}
    float getY() {return y;}
    float getPos() {return pos;}
  protected:
    float x, y, pos;
};

namespace Collisions{

    void drawQuadTree();
    void drawBox(float x, float y, float width, float height);
    void detect(std::vector<Ship*> ship, std::vector<Enemy*>, std::vector<Drops*>);
    void drawHitBoxes(std::vector<Ship*> ship, std::vector<Enemy*> enemy, std::vector<Drops*> powerups);
    
    int getQuadrant(float x, float y, int xBoundry, int yBoundry, int level, int quadrant);
}



#endif

