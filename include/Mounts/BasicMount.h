#ifndef BASICMOUNT_H
#define BASICMOUNT_H

#include "./Mount.h"

class BasicMount: public Mount {
  public:
    BasicMount();
    ~BasicMount();
    
    void setTexture();
    void reset();
    void defaults();
    void update(float x, float y, float directionX, float directionY, float angle, bool isShooting);
    void update(float x, float y, float directionX, float directionY, float angle, float Px, float Py);

  protected:   
   
};

#endif
