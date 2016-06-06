#ifndef GAME_H
#define GAME_H

#include "./DisplayManager.h"
#include "./Ship.h"
#include "./LoadTexture.h"

class Game: public DisplayManager {
  public:
    Game();
    
    void draw();
    void update(float mX, float mY, unsigned int* mouseBtnState, unsigned char* keyState, unsigned char* prevKeyState);
    void restart();
    void clean();
  protected:
    void drawBackground();
    void drawCrosshair();
    Ship ship;
    bool isNew;
    // Cross Hair
    float ChX, ChY, ChRadius;
    GLuint ChTexture;
};

#endif
