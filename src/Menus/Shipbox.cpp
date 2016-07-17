#include "../../include/Menus/Shipbox.h"

Shipbox::~Shipbox() {
  clean();
}

void Shipbox::setup(float x, float y, bool unlocked, bool bought, int shipType) {
  this->x = x;
  this->y = y;
  this->unlocked = unlocked;
  this->bought = bought;
  isMovingLeft = false;
  isMovingRight = false;
  visible = true;

  oldX = x;
  switch(shipType) {
    case GALACTICSHIP:
      ship.push_back(new GalacticShip);
      break;
    case FIGHTERSHIP:
      ship.push_back(new FighterShip);
      break;
    default:
      printf("Error in Shipbox.cpp: Unkown ship varient");
      exit(0);
      break;
  }
  ship[0]->VisualSetup(x, y);
  
  // 1st Ship Box
  lb.push_back(new Label);
  lb[0]->setup(x, y, 456, 400, (char*)"Textures/Menu/ShopMenu/Boxbackground.png");
  lb[0]->drawBorder(true);
  
  buttons.push_back(new Button);
  buttons[0]->setup(x, y - 150, 200, 60, 0.3);
  
  if(unlocked) {
    if(bought) {
      buttons[0]->setTexture((char*)"Textures/Menu/ShopMenu/Upgrade.png");
      buttons[0]->fill(0.8f, 0.0f, 0.0f);
    } else {
      buttons[0]->setTexture((char*)"Textures/Menu/ShopMenu/Buy.png");
      buttons[0]->fill(0.0f, 0.8f, 0.0f);

      lb.push_back(new Label);
      lb[1]->setup(x, y + 150, 0.3);
      lb[1]->setWidth(200);
      lb[1]->setHeight(60);
        
      switch(shipType) {
        case 0:
        case FIGHTERSHIP:
          lb[1]->setText((char*)"$1000", 5);
          break;
        case 2:
          lb[1]->setText((char*)"$1500", 5);
          break;
        case 4:
          lb[1]->setText((char*)"$2000", 5);
          break;
        case 5:
          break;
      }
      lb[1]->fill(0.6f, 0.6f, 0.6f);
      lb[1]->drawBorder(true);        
    }
  } else {
      buttons[0]->setTexture((char*)"Textures/Menu/ShopMenu/Locked.png");
      buttons[0]->fill(0.6f, 0.6f, 0.6f);
  }  
  buttons[0]->drawBorder(true);
}

void Shipbox::draw() {
  
  if(visible) {
    for(unsigned int i = 0; i < lb.size(); ++i)
      lb[i]->draw();
    for(unsigned int i = 0; i < buttons.size(); ++i)
      buttons[i]->draw();
    ship[0]->draw();
  }  
}

void Shipbox::update() {
  if(isMovingLeft) {
    x-=10;    
    setX(); 
    if(x < (oldX-444)) {
      isMovingLeft = false;
      oldX = x;
    }
  }
  
  if(isMovingRight) {
    x+=10;
    setX();
    if(x > (oldX+444)) {
      isMovingRight = false;
      oldX = x;
    }
  }
  if(x < 0 || x > 267+453*2.5) {
    visible = false;
  } else {
    visible = true;
  }  
}

void Shipbox::setX() {
  for(unsigned int i = 0; i < lb.size(); ++i)
    lb[i]->setX(x);
  for(unsigned int i = 0; i < buttons.size(); ++i)
    buttons[i]->setX(x);
  ship[0]->setX(x);
}

void Shipbox::moveLeft() {
  isMovingLeft = true;
}

void Shipbox::moveRight() {
  isMovingRight = true;
}

