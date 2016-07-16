#ifndef SHOP_H
#define SHOP_H

#include "../GameTypes/Menu.h"

class Shop: public Menu {
  public:
    Shop();
    
    void setup();
    void restart();
    void update(float mX, float mY, unsigned int* mouseBtnState, unsigned int* prevMouseBtnState, unsigned char* keyState, unsigned char* prevKeyState);
    void drawBackground();
    
  protected:
    void drawBox(float x, float y, float width, float height);
};

#endif
