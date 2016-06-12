#ifndef BASICMOUNT_H
#define BASICMOUNT_H

#include "./Mount.h"


class BasicMount: public Mount {
  public:
    BasicMount();
    void update(float x, float y, float directionX, float directionY, float angle);
    void setup();
    void setup(int variant);
    void reset();

  protected:
    void addBullet();
    int maxMounts;
    int variant;
};

#endif