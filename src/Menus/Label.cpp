#include "../../include/Menus/Label.h"

Label::Label() {

}

void Label::draw() {
  if(hasTexture) {  
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, Texture);
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
  
    glDisable(GL_TEXTURE_2D);
  }
  
  if(isTimed) {
    if(ticks > 0)
      drawChar();
  } else {
    drawChar();
  }
}

void Label::clean() {

}

void Label::setup(float x, float y, float scale) {
  hasTexture = false;
  isTimed = false;
  ticks = 0;
  this->x = x;
  this->y = y;
  this->scale = scale;
}

void Label::setup(float x, float y, float scale, bool timer) {
  hasTexture = false;
  isTimed = timer;
  ticks = 0;
  this->x = x;
  this->y = y;
  this->scale = scale;
}

void Label::update() {
    if(isTimed) {
      ticks--;
      if(ticks <= 0)
        ticks = 0;
    } 
}

//Draws Text to the screen
void Label::drawChar() {
  glPushMatrix();
  glColor3f(R, G, B); // Text Colour
  //glRasterPos2i(x, y); //coordinates of text
  glTranslatef(x-length*20, y, 0);

  // void * font = GLUT_BITMAP_TIMES_ROMAN_24;
  //GLUT_BITMAP_HELVETICA_18;//set font http://www.opengl.org/documentation/specs/glut/spec3/node76.html#SECTION000111000000000000000
  glScalef(scale,scale,scale);
  for(int i = 0; i < length; i++) {
    //glutBitmapCharacter(font, str[i]);//Draw character to screen
    glutStrokeCharacter(GLUT_STROKE_ROMAN , str[i]);
  }
   
  glColor4f(1.0f, 1.0f, 1.0f, 1.0f);//return colours to the full amounts

  glPopMatrix();
}

void Label::setTexture(char* filename) {
  Texture = txt::LoadTexture(filename);
  hasTexture = true;
}

void Label::setText(const char* str, int length) {
  for(int i = 0; i < length; ++i)
    this->str[i] = str[i];
  this->length = length;
}

void Label::setTimer(int time) {
  ticks = time;
}

void Label::setColour(float R, float G, float B) {
  this->R = R;
  this->G = G;
  this->B = B;
}
