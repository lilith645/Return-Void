#ifndef DROPS_H
#define DROPS_H

#include "../Menus/Label.h"
#include "../Namespaces/LoadTexture.h"

class Drops {
  public:
    virtual void draw() = 0;
    virtual void setup(float x, float y) = 0;
    virtual void update() = 0;
    virtual int getType() = 0;
    
    void setX(float x) { this->x = x; }
    void setY(float y) { this->y = y; }
    float getX() { return x; }
    float getY() { return y; }
    float getWidth() { return width; }
    float getHeight() { return height; }
    bool isVisible() { return visible; }
  protected:
    int tick;
    float x, y, width, height;
    bool visible, isCollected;
    Label lbTitle;
    
    static GLuint getCoinTexture() {
      static GLuint coinText = txt::LoadTexture("Textures/Game/Powerups/Coin.png");
      return coinText;
    }
    
    static GLuint getHealthTexture() {
      static GLuint healthText = txt::LoadTexture("Textures/Game/Powerups/Health.png");
      return healthText;
    }
    
    static GLuint getShieldTexture() {
      static GLuint shieldText = txt::LoadTexture("Textures/Game/Powerups/Shield.png");
      return shieldText;
    }
};

#endif
