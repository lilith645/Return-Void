#ifndef SHIP_H
#define SHIP_H

#define MAXWEAPONS 3

#include <math.h>

#include "../defines.h"
#include "../Namespaces/LoadTexture.h"
#include "../Mounts/BasicMount.h"
#include "../Mounts/TriangleMount.h"

class Ship {
  public:
    Ship();
    void update(float mX, float mY, unsigned int* mouseBtnState, unsigned char* keyState, unsigned char* prevKeyState);
    void draw();
    void setup();
    void clean();
        
    float getX();
    float getY();
    float getWidth();
    float getHeight();
    bool getVisible();
    int getNumOfMounts();
    float getBulletX(int mIndex, int bIndex);
    float getBulletY(int mIndex, int bIndex);
    float getBulletWidth(int mIndex, int bIndex);
    float getBulletHeight(int mIndex, int bIndex);
    int getNumOfBullets(int index);
    int bulletHit(int mIndex, int bIndex);
    float getDirectionX();
    float getDirectionY();
    float getDistanceFromCursor();
    //float getHealth();
    void takeDamage(int damage);
    
  protected:
    //void respawn();
    
    GLuint textures[3];
    Mount* WeaponMount[MAXWEAPONS];
    
    float x, y;
    int health;
    float speed;
    float angle;
    bool visible;
    float width, height;
    float directionX, directionY, distanceFromCursor;
    //float directionX, directionY;   
};

#endif