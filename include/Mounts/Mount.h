#ifndef MOUNT
#define MOUNT

#include <vector>
#include <math.h>

#include "../Weapons/Spiral.h"
#include "../Weapons/DotBullet.h"
#include "../Weapons/RedPlasma.h"
#include "../Weapons/BluePlasma.h"
#include "../Weapons/GreenPlasma.h"
#include "../Weapons/PurplePlasma.h"
#include "../Weapons/AlphaOnePlasma.h"

#include "../Namespaces/LoadTexture.h"

class Mount {
  public:
    ~Mount() { 
      for(unsigned int i = 0; i < bullets.size(); ++i) 
          bullets.erase(bullets.begin() + i);
    }
    
    virtual void reset(float x, float y) { }
    virtual void defaults() {};
    virtual void setTexture() = 0;  
      
    virtual void individualClean() {  }
    virtual void tick(float x, float y, float deltaTime, float directionX, float directionY, float angle, bool isShooting) {  }
    
    void setIsBoss() { isBoss = true; }
    void isLeftMount() { isLeft = true; }
    void setX(float x) { this->x = x+offsetX; }
    void setHealth(float health) { this->health = health; };
    void setVisible(bool visible) { this->visible = visible; }
    void setTimer(float bulletTimer) { this->bulletTimer = bulletTimer; }
    void resetTimer() { this->bulletTicks = 0; }
    
    void setAutomated(bool automate) { this->automated = automate; }
    void setDamage(float damage) { customDamage = true; this->damage = damage; }
    void setOffset(float offsetX, float offsetY) { this->offsetX = offsetX; this->offsetY = offsetY; }
    
    bool getVisible() { return visible; }
    int getTimer() { return bulletTicks; }
    int getNumBullets() { return bullets.size(); }    
    float bulletHit(int index) { return bullets[index]->hit(); }    
    
    float getX() { return x; }
    float getY() { return y; }
    float getWidth() { return width; }
    float getHeight() { return height; }
    float getBulletX(int index) { return bullets[index]->getX(); }
    float getBulletY(int index) { return bullets[index]->getY(); }
    float getBulletDirectionX(int index) { return bullets[index]->getDirectionX(); }
    float getBulletDirectionY(int index) { return bullets[index]->getDirectionY(); }
    float getBulletWidth(int index) { return bullets[index]->getWidth(); }
    float getBulletHeight(int index) { return bullets[index]->getHeight(); }
    
    float getHealth() { return health; } 
    
    virtual void erase(float deltaTime) {
      for(unsigned int i = 0; i < bullets.size(); ++i) {
        bullets[i]->update(deltaTime);
        if(!bullets[i]->getVisible())
          bullets.erase(bullets.begin() + i);
      }
    }
    
    virtual void update(float x, float y, float deltaTime, float directionX, float directionY, float angle, bool isShooting) {
      if(currentTexture == 1)
        currentTexture = 0;
      float rad = angle* (float)M_PI / 180;
      float newX = (offsetX)*cos(rad) - (offsetY)*sin(rad);
      float newY = (offsetX)*sin(rad) + (offsetY)*cos(rad);
      this->x = x+newX;
      this->y = y+newY;
      this->angle = angle;
      dirX = directionX;
      dirY = directionY;
     
      tick(x, y, deltaTime, directionX, directionY, angle, isShooting);

      incrementTimers(isShooting, deltaTime);
 
      erase(deltaTime);
    }
    
    virtual void update(float x, float y, float deltaTime, float directionX, float directionY, float angle, float Px, float Py) {

      float diffx = Px - x;
      float diffy = Py - y;

      float distance = pow(pow(diffy,2.0f) + pow(diffx,2.0f), 0.5f);
      dirX = (diffx) / (distance);
      dirY = (diffy) / distance;

      float rad = angle* (float)M_PI / 180;
      float newX = (offsetX)*cos(rad) - (offsetY)*sin(rad);
      float newY = (offsetX)*sin(rad) + (offsetY)*cos(rad);
      this->x = x+newX;
      this->y = y+newY;
      this->angle = angle;

      incrementTimers(true, deltaTime);
 
      erase(deltaTime);
    } 

    void takeDamage(float damage) { 
      health -= damage; 
      if(!tookDamage) 
        tookDamage = true; 
      if(health <= 0) 
        visible = false;
    }
    
    void incrementTimers(bool isShooting, float deltaTime) {
      damageTicks+= 1*deltaTime; 
      bulletTicks+= 1*deltaTime; 
      
      if(damageTicks > damageTimer) { 
        tookDamage = false; 
        damageTicks = 0; 
      }
      
      if(isShooting) {
        if(bulletTicks > bulletTimer) { 
          if(visible && automated) {
            fire(); 
            bulletTicks = 0; 
          }
        }
      }
      if(x < 0)
        visible = false;
    }
    
    void fire() {
      currentTexture = 1;
      addBullet();
      unsigned int i = bullets.size()-1;
      bullets[i]->setup(x, y, dirX, dirY, angle);
      bullets[i]->setVisible(true);
      if(customDamage)
        bullets[i]->setDamage(damage);
    }
    
    void clean() { 
      bullets.clear();  
      bullets.erase(bullets.begin(), bullets.end()); 
      bulletTicks = 0;
      individualClean();
    }   

    virtual void draw() {
      for(unsigned int i = 0; i < bullets.size(); ++i)
        bullets[i]->draw();

      if(visible) {
        glPushMatrix();
        glTranslatef(x, y, 0); // M1 - 2nd translation
        glRotatef(angle, 0.0f, 0.0f, 1.0f);
        glTranslatef(-x, -y, 0); // M1 - 2nd translation

        glEnable(GL_TEXTURE_2D);
        setTexture();
        //if(!isLeft) {
          glBegin(GL_QUADS);
            glTexCoord2f(0.0f, 1.0f);
            glVertex3f(x-width/2, y+height/2, 0.0);
            glTexCoord2f(1.0f, 1.0f);
            glVertex3f(x+width/2, y+height/2, 0.0);
            glTexCoord2f(1.0f, 0.0f);
            glVertex3f(x+width/2, y-height/2, 0.0);
            glTexCoord2f(0.0f, 0.0f);
            glVertex3f(x-width/2, y-height/2, 0.0);
          glEnd();
       /* } else {
          glBegin(GL_QUADS);
            glTexCoord2f(1.0f, 1.0f);
            glVertex3f(x-width/2, y+height/2, 0.0);
            glTexCoord2f(0.0f, 1.0f);
            glVertex3f(x+width/2, y+height/2, 0.0);
            glTexCoord2f(0.0f, 0.0f);
            glVertex3f(x+width/2, y-height/2, 0.0);
            glTexCoord2f(1.0f, 0.0f);
            glVertex3f(x-width/2, y-height/2, 0.0);
          glEnd();
        }*/
        glDisable(GL_TEXTURE_2D);
        glPopMatrix();
        glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
      }
    }
    
    void setTimers() {
      damageTimer = DAMAGETIMER;
      switch (bulletType) {
        case BLUEPLASMA:
          bulletTimer = BLUEPLASMATIMER;
          break;
        case REDPLASMA:
          bulletTimer = REDPLASMATIMER;
          break;
        case PURPLEPLASMA:
          bulletTimer = PURPLEPLASMATIMER;
          break;
        case GREENPLASMA:
          bulletTimer = GREENPLASMATIMER;
          break;
        case SPIRAL:
          bulletTimer = SPIRALTIMER;
          break;
        case ALPHAONEPLASMA:
          bulletTimer = ALPHAONETIMER;
          break;
        case DOTBULLET:
          bulletTimer = DOTBULLETTIMER;
          break;
        default:
          printf("Error: unknown varient in mount setup: %d\n",variant);
          exit(0);
      }
    }
    
    // This setup should be removed
    void setup(int variant) {
      automated = true;
      bulletTicks = 0;
      damageTicks = 0;
      angle = 0;
      isLeft = false;
      visible = true;
      customDamage = false;
      tookDamage = false;
      currentTexture = 0;
      x = SPACE_X_RESOLUTION/2;
      y = SPACE_Y_RESOLUTION/2;
      this->variant = variant;
      this->bulletType = variant;
      defaults();
      
      // To be removed 
      // -----------------------------------------------------------------------
      damageTimer = DAMAGETIMER;
      switch (variant) {
        case BLUEPLASMA:
          bulletTimer = BLUEPLASMATIMER;
          break;
        case REDPLASMA:
          bulletTimer = REDPLASMATIMER;
          break;
        case PURPLEPLASMA:
          bulletTimer = PURPLEPLASMATIMER;
          break;
        case GREENPLASMA:
          bulletTimer = GREENPLASMATIMER;
          break;
        case SPIRAL:
          bulletTimer = SPIRALTIMER;
          break;
        case ALPHAONEPLASMA:
          bulletTimer = ALPHAONETIMER;
          break;
        case DOTBULLET:
          bulletTimer = DOTBULLETTIMER;
          break;
        default:
          printf("Error: unknown varient in mount setup: %d\n",variant);
          exit(0);
      }
      // -----------------------------------------------------------------------
    }

  protected:
    void addBullet() {
      switch(bulletType) {
        case GREENPLASMA:
          bullets.push_back(new GreenPlasma);
          break;
        case BLUEPLASMA:
          bullets.push_back(new BluePlasma);
          break;
        case REDPLASMA:
          bullets.push_back(new RedPlasma);
          break;
        case PURPLEPLASMA:
          bullets.push_back(new PurplePlasma);
          break;
        case SPIRAL:
          bullets.push_back(new Spiral);
          break;
        case DOTBULLET:
          bullets.push_back(new DotBullet);
          break;
        case ALPHAONEPLASMA:
          bullets.push_back(new AlphaOnePlasma);
          if(isBoss) {
            int size = bullets.size() - 1;
            bullets[size]->setIsBoss(true);
          }
          break;
        default:
          printf("Error: unknown varient in mounts add bullet: %d\n",variant);
          exit(0);
      }
    }
    //To be Removed
    //-------------
    int isLeft;
    int damage;
    int variant;
    int maxMounts;
    int bulletType;
    
    bool isBoss;
    bool customDamage;
    float health; 
    float fireRate;  
    //-------------   
    
    int currentTexture;
    float bulletTicks, bulletTimer, damageTicks, damageTimer;       
    
    bool visible;
    bool tookDamage;
    bool automated; 
    
    float angle;


    float dirX, dirY;  
    float offsetX, offsetY;
    float x,y, width, height;

    std::vector<Weapon*> bullets;

    static GLuint getBasicMountTexture() {
      static GLuint basicMountTexture = txt::LoadTexture("Textures/Game/Mounts/BasicMount.png");
      return basicMountTexture;
    }

    static GLuint getBasicMountBrightTexture() {
      static GLuint basicMountBrightTexture = txt::LoadTexture("Textures/Game/Mounts/BasicMountBright.png");
      return basicMountBrightTexture;
    }

    static GLuint getPurpleMountTexture() {
      static GLuint purpleMountTexture = txt::LoadTexture("Textures/Game/Mounts/PurpleMount.png");
      return purpleMountTexture;
    }

    static GLuint getAlphaOneMountTexture() {
      static GLuint alphaOneMountTexture = txt::LoadTexture("Textures/Game/Mounts/AlphaOneMount.png");
      return alphaOneMountTexture;
    }
    
    static GLuint getHeroMountTexture(int i) {
      static GLuint heroMount1Texture = txt::LoadTexture("Textures/Game/Ships/HeroMount1.png");
      static GLuint heroMount2Texture = txt::LoadTexture("Textures/Game/Ships/HeroMount2.png");
      static GLuint heroMount3Texture = txt::LoadTexture("Textures/Game/Ships/HeroMount3.png");
      static GLuint heroMount4Texture = txt::LoadTexture("Textures/Game/Ships/HeroMount4.png");
                        
      switch(i) {
        case 0:
          return heroMount1Texture;
          break;
        case 1:
          return heroMount2Texture;
          break;
        case 2:
          return heroMount3Texture;
          break;
        case 3:
          return heroMount4Texture;
          break;
      }
      return heroMount1Texture;
    }

    static GLuint getHypnoMountTexture(int i) {
      static GLuint hypnoMountLeftTexture = txt::LoadTexture("Textures/Game/Mounts/HypnoMountLeft.png");
      static GLuint hypnoMountRightTexture = txt::LoadTexture("Textures/Game/Mounts/HypnoMountRight.png");

      switch(i) {
        case 0:
          return hypnoMountLeftTexture;
        case 1:
          return hypnoMountRightTexture;
      }
      return hypnoMountLeftTexture;
    }
};

#endif
