#include "../../include/Menus/Button.h"

Button::Button() {

}

Button::~Button() {
  Texture = 0;
}

void Button::draw() {
  if(visible) {
    if(isFilled) {
      glColor3f(fillR, fillG, fillB);
      drawQuad(x, -width, y, height, UP);
      /*glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(x-width/2, y+height/2, 0.0);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(x+width/2, y+height/2, 0.0);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(x+width/2, y-height/2, 0.0);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(x-width/2, y-height/2, 0.0);
      glEnd(); */
      glColor3f(1.0f, 1.0f, 1.0f);
    }
    if(hasTexture) {
      if(disabled) {
        glColor4f(1.0, 1.0, 1.0, 0.5);
      } else if(clicked || hasBeenClicked) {
        glColor3f(0.0f, 0.0f, 0.0f);
      } else if(isSelected) {
        glColor3f(0.5f, 0.5f, 0.5f);
      } else {
        glColor3f(1.0, 1.0, 1.0);
      }
      glEnable(GL_TEXTURE_2D);
      glBindTexture(GL_TEXTURE_2D, Texture);
      drawQuad(x, -width, y, height, UP);
     /* glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(x-width/2, y+height/2, 0.0);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(x+width/2, y+height/2, 0.0);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(x+width/2, y-height/2, 0.0);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(x-width/2, y-height/2, 0.0);
      glEnd(); */ 
      glColor3f(1.0f, 1.0f, 1.0f);
      glDisable(GL_TEXTURE_2D);    
    } else { 
      lbTitle.draw();
    }
    if(hasBorder)
      drawBox();
  }
  glColor4f(1.0, 1.0, 1.0, 1.0);
}

void Button::clean() {

}

void Button::setup(float x, float y, float width, float height, char* filename) {
  isSelected = false;
  hasTexture = true;
  clicked = false;
  hasBeenClicked = false;
  hasBorder = false;
  isFilled = false;
  disabled = false;
  visible = true;
  
  Texture = txt::LoadTexture(filename);
  
  this->x = x;
  this->y = y;
  this->scaleX = 0;
  this->scaleY = 0;
  this->width = width;
  this->height = height;
}

void Button::setup(float x, float y, float width, float height, float scaleX, float scaleY) {
  isSelected = false;
  hasTexture = false;
  clicked = false;
  hasBeenClicked = false;
  hasBorder = false;
  isFilled = false;
  disabled = false;
  visible = true;
  
  this->x = x;
  this->y = y;
  this->scaleX = scaleX;
  this->scaleY = scaleY;
  this->width = width;
  this->height = height;
  lbTitle.setup(x, y, scaleX, scaleY);
}

void Button::update(float mouseX, float mouseY, unsigned int* mouseBtnState, unsigned int* prevMouseBtnState) {
  hasBeenClicked = false;
  isSelected = false;
  if(!disabled) {
    if(mouseBtnState[0] == 0)
      clicked = false;
      
    if(mouseY > y-height/2 && mouseY < y+height/2 && mouseX > x-width/2 && mouseX < x+width/2) {
      if(mouseBtnState[0] == 1) {
        clicked = true;
      } 
      if(mouseBtnState[0] == 0 && prevMouseBtnState[0] == 1) {
        hasBeenClicked = true;
      }
      isSelected = true;
    } else {
      isSelected = false;
      clicked = false;
      hasBeenClicked = false;
    }
  }
}

void Button::setTexture(char* filename) {
  Texture = txt::LoadTexture(filename);
  hasTexture = true;
}

void Button::setText(const char* str, int length) {
  lbTitle.setText(str, length);
}

void Button::setColour(float R, float G, float B) {
  lbTitle.setColour(R, G, B);
}

bool Button::Clicked() {
  return hasBeenClicked;
}

void Button::drawBox() {
  float border = 5;
  glColor3f(0.0, 0.0, 0.0);
  glBegin(GL_QUADS);

    // Left
    glVertex3f(x-width/2, y+height/2, 0.0);
    glVertex3f(x-width/2+border, y+height/2, 0.0);
    glVertex3f(x-width/2+border, y-height/2, 0.0);
    glVertex3f(x-width/2, y-height/2, 0.0);

    // Right
    glVertex3f(x+width/2, y+height/2, 0.0);
    glVertex3f(x+width/2-border, y+height/2, 0.0);
    glVertex3f(x+width/2-border, y-height/2, 0.0);
    glVertex3f(x+width/2, y-height/2, 0.0);

    // top
    glVertex3f(x+width/2, y+height/2, 0.0);
    glVertex3f(x+width/2, y+height/2-border, 0.0);
    glVertex3f(x-width/2, y+height/2-border, 0.0);
    glVertex3f(x-width/2, y+height/2, 0.0);

    // bottom
    glVertex3f(x+width/2, y-height/2, 0.0);
    glVertex3f(x+width/2, y-height/2+border, 0.0);
    glVertex3f(x-width/2, y-height/2+border, 0.0);
    glVertex3f(x-width/2, y-height/2, 0.0);

  glEnd();
  glColor3f(1.0, 1.0, 1.0);
}

