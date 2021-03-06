#include "../../include/Mounts/MountType3.h"

MountType3::MountType3(float offsetX, float offsetY) { 
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
    this->width = 96;
    this->height = 96;

    this->bulletType = GREENPLASMA;
    
    setTimers();
    
    //Load texture
    getPurpleMountTexture();
}

void MountType3::reset(float x, float y) {
  this->visible = true;
  this->tookDamage = false;
  this->x = x+offsetX;
  this->y = y+offsetY;
  
  setTimers();
}

void MountType3::setTexture() {
  if(bulletTicks > 60) {
    currentTexture = 3;
  } else if (bulletTicks > 40) {
    currentTexture = 2;
  } else if (bulletTicks > 20) {
    currentTexture = 1;
  } else {
    currentTexture = 0;
  }

  glBindTexture(GL_TEXTURE_2D, getHeroMountTexture(currentTexture));
    
}
