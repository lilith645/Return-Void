#ifndef WEAPON
#define WEAPON

#include "../defines.h"
#include "../Namespaces/LoadTexture.h"

class Weapon {
  public:

    virtual void draw() = 0;
    virtual void reset() = 0;
    virtual void clean() = 0;
    virtual void tick() = 0;
    virtual void setup(float x, float y, float dirX, float dirY, float angle) = 0;
    
    virtual void update() { 
      if(visible) {
        y+=speed*directionY;
        x+=speed*directionX;
      }
      tick();
      if(y > SPACE_Y_RESOLUTION || y < 0 || x < 0 || x > SPACE_X_RESOLUTION)
        visible = false;
    }
    
    void setVisible(bool visible) { this->visible = visible; }
    
    bool getVisible() { return visible; }
    
    float getDamage() { return damage; }
    float hit() { visible = false; return damage; }
    
    float getX() { return x; }
    float getY() { return y; }
    float getWidth() { return width; }
    float getHeight() { return height; }
    
  protected:
    float damage;
    float angle;
    bool visible;
    float directionX, directionY;
    float x,y, width, height, speed;
    
    static GLuint getBluePlasmaTexture() {
      static GLuint bluePlasmaTexture = txt::LoadTexture("Textures/Game/Weapons/BluePlasma.png");
      return bluePlasmaTexture;
    }
    static GLuint getGreenPlasmaTexture() {
      static GLuint greenPlasmaTexture = txt::LoadTexture("Textures/Game/Weapons/GreenPlasma.png");
      return greenPlasmaTexture;
    }
    static GLuint getRedPlasmaTexture() {
      static GLuint redPlasmaTexture = txt::LoadTexture("Textures/Game/Weapons/RedPlasma.png");
      return redPlasmaTexture;
    }
    static GLuint getPurplePlasmaTexture() {
      static GLuint purplePlasmaTexture = txt::LoadTexture("Textures/Game/Weapons/PurplePlasma.png");
      return purplePlasmaTexture;
    }
    
    static GLuint getSpiralTexture() {
      static GLuint spiralTexture = txt::LoadTexture("Textures/Game/Weapons/Spiral.png");
      return spiralTexture;
    }
    
    static GLuint getAlphaOnePlasmaTexture() {
      static GLuint alphaOnePlasmaTexture = txt::LoadTexture("Textures/Game/Weapons/AlphaOnePlasma.png");
      return alphaOnePlasmaTexture;
    }
};

#endif
