#ifndef BASICENEMY_H
#define BASICENEMY_H

#include "./Enemy.h"

class BasicEnemy: public Enemy {
  public:
    ~BasicEnemy();
    void setup(float drop);
    void update(float Px, float Py);
    void reset();
    void draw();
};

#endif
