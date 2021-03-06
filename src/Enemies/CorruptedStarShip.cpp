#include "../../include/Enemies/CorruptedStarShip.h"

CorruptedStarShip::CorruptedStarShip() {
  this->visible = false;
  this->width = 75;
  this->height = 75;
  this->speed = 3;
  this->width = 75;
  this->height = 75;
  this->health = 15;

  this->angle = 0;
  this->isBoss = false;

  this->maxWeaponMounts = 1;

  this->score = 30;
  
  for(int i = 0; i < maxWeaponMounts; ++i) {
    this->WeaponMount.push_back(new BasicMount);
    this->WeaponMount[i]->setup(REDPLASMA);
    this->WeaponMount[i]->setOffset(0, 20);
  }
}

CorruptedStarShip::~CorruptedStarShip() {
  clean();
}

void CorruptedStarShip::defaults() {

 // lbScore.setup(SPACE_X_RESOLUTION/2, SPACE_Y_RESOLUTION/2, 0.2, true);
 // lbScore.setColour( 0.0,  1.0,  0.1);
//  lbScore.setText("+30", 3);

}

void CorruptedStarShip::update(float Px, float Py, float deltaTime) {
  move(deltaTime);

  if(y <= -height)
    setVisible(false);
  for(int i = 0; i < maxWeaponMounts; ++i) {
    if(!visible)
      WeaponMount[i]->setVisible(false);
    float rad = (movementAngle+90) * M_PI/180.0;
    float dirx = cos(-rad) * width;
    float diry = sin(-rad) * height;
    float distance = pow(pow(diry,2.0f) + pow(dirx,2.0f), 0.5f);
    dirx = dirx/distance;
    diry = diry/distance;
    WeaponMount[i]->update(x, y, deltaTime, dirx, diry, angle+180, true);
  }
}

void CorruptedStarShip::reset() {

}

void CorruptedStarShip::setTexture() {
    if(health > maxHealth/4.0 *3) {
      glBindTexture(GL_TEXTURE_2D, getCorruptedStarShipTexture(0));
    } else if(health > maxHealth/2) {
      glBindTexture(GL_TEXTURE_2D, getCorruptedStarShipTexture(1));
    } else if(health > maxHealth/4) {
      glBindTexture(GL_TEXTURE_2D, getCorruptedStarShipTexture(2));
    } else {
      glBindTexture(GL_TEXTURE_2D, getCorruptedStarShipTexture(3));
    }
}

void CorruptedStarShip::setX(float x) {
  this->x = x;
  startX = x;
  if(x < width*5) {
    amp = (x-width)/2;//startX-width/2;
  } else if(SPACE_X_RESOLUTION - x < width*5) {
    amp = (SPACE_X_RESOLUTION - x - width)/2;
  } else {
    amp = width/2*5;
  }
}

void CorruptedStarShip::setY(float y) {
  this->y = y;
}
