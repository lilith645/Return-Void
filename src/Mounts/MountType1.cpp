#include "../../include/Mounts/MountType1.h"

MountType1::MountType1(float offsetX, float offsetY) { 
    this->currentTexture = 0;
    this->bulletTicks = 0;
    this->damageTicks = 0;
    this->damageTimer = 0;
    this->visible = true;
    this->tookDamage = false;
    this->automated = true; 
    
    this->angle = 0; 
    this->dirX = 0;
    this->dirY = 0;  
    this->offsetX = offsetX;
    this->offsetY = offsetY;
    this->x = -10;
    this->y = -10;
    this->width = 8;
    this->height = 64;

    this->bulletType = BLUEPLASMA;
    
    setTimers();
    
    //Load texture
    getBasicMountTexture();
}

void MountType1::reset(float x, float y) {
  this->visible = true;
  this->tookDamage = false;
  this->x = x+offsetX;
  this->y = y+offsetY;
  
  setTimers();
}

void MountType1::setTexture() {
  if(currentTexture == 0) {
    glBindTexture(GL_TEXTURE_2D, getBasicMountTexture());
  } 
}
