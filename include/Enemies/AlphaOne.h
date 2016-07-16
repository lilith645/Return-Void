#ifndef ALPHAONE_H
#define ALPHAONE_H

#include "./Enemy.h"

class AlphaOne: public Enemy {
  public:
    AlphaOne();
    ~AlphaOne();
    void defaults();
    void update(float Px, float Py);
    void reset();
    void setTexture();
};

#endif