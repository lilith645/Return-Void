#include "Player.h"

#include <stdlib.h>

Player::Player() {
    width = 5;
    height = 5;
    angle = 0;
    speed = 0.5f;
    boundryX = 100;
    boundryY = 92;
    globalTime = clock();
    printf("Player Constructed\n");
}
   
void Player::setup(GLuint *newTextures, float newAspectRatio) {
    x = 50.0f;
    y = 50.0f;
    angle = 0;
    aspectRatio = newAspectRatio;
   // width*=aspectRatio;
    height=5;//*aspectRatio;
    health = 5;
    drawInvincible = true;
    fireRate = 2000;
    invincible = false;
    alive = true;
    visible = true; 
    PlayerText = newTextures[0];
    PlayerLeftText = newTextures[1];
    PlayerRightText = newTextures[2];
    texture = newTextures[0];

    bulletTexture = newTextures[3];
    invincTimer = 0;
    flashTimer = 0;
    
    bullets.push_back(new Bullet);
    for(unsigned int i = 0; i < bullets.size(); i++) {
        bullets[i]->setup(bulletTexture, 0.5, 3, aspectRatio);
    }
    printf("Player bullets constructed\n");
}

void Player::destroy() {
    for(unsigned int i = 0; i < bullets.size(); i++) {
        bullets.erase(bullets.begin() + i);
    }
    //free(PlayerText);
   // free(PlayerLeftText);
   // free(PlayerRightText);
   // free(texture);
}

void Player::leftImage() {
    texture = PlayerLeftText;
}

void Player::rightImage() {
    texture = PlayerRightText;
}

void Player::stationaryImage() {
    texture = PlayerText;
}

void Player::Tick(float mouseX, float mouseY) {
    
    globalTime = clock();
    if(health < 0) {
        health = 0;
        alive = false;
        visible = false;    
    }
    lastMouseX = mouseX;
    lastMouseY = mouseY;
    float diffx = mouseX - x; 
    float diffy = mouseY - y;
    //float distance = pow( (diffx * diffx) + (diffy * diffy) , 0.5);
    float distance = pow(pow(diffy,2.0f) + pow(diffx,2.0f), 0.5f);
    directionX = (diffx) / (distance+10);
    directionY = (diffy) / (distance+10);
    //angle = tan(directionY/directionX);    
    
     if (diffx > 0.0 && diffy > 0.0) {//Quadrant 1
        angle = atan(diffy/diffx) *180 / M_PI ;
        angle = angle - 90;
    }else if(diffx < 0 && diffy > 0) {//Quadrant 2
        angle = atan(diffy/diffx) *180 / M_PI ;
        angle = angle + 90;
    } else     if(diffx < 0 && diffy < 0) {//Quadrant 3
        angle = atan(diffy/diffx) *180 / M_PI ;
        angle = angle+90;
    } else     if(diffx > 0 && diffy < 0) {//Quadrant 4
        angle = atan(diffy/diffx) * 180 / M_PI ;
        angle = angle - 90;
    }
        
    for(unsigned int i = 0; i < bullets.size(); ++i) {
        if(bullets[i]->getVisible()) {   
            bullets[i]->Tick();
        } else {
            bullets.erase(bullets.begin() + i);
        }
    }
    invincTimer++;
    flashTimer++;
}

void Player::drawShip() {
    glPushMatrix();
    //glLoadIdentity();
    glTranslatef(x, y, 0); // M1 - 2nd translation
    glScalef(1,aspectRatio,1);        
    glRotatef(angle, 0.0f, 0.0f, 1.0f);                  // M2
    glTranslatef( -x, -y, 0);  // M3 - 1st translation  
   
    glEnable(GL_TEXTURE_2D);
    
	glBindTexture(GL_TEXTURE_2D, texture);
    
    glBegin(GL_POLYGON);
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
    
    glPopMatrix();
   // glRotatef(-45.0f, 0.0f, 0.0f, 1.0f);
                       // Reset The View
  //  glPushMatrix();
 //   glTranslatef(x,y, 0);
  //  glRotatef(45, 0.0, 0.0, 1.0f);
    //glTranslatef(x, y, 0);
  // glPopMatrix();
}

void Player::flash() {
    if(invincTimer > 80)
        invincible = false;
    
    if(flashTimer > 10) {
        glColor3f(0.2f, 0.2f, 0.5f);
        drawShip();
    } else {
        glColor3f(1.0, 1.0, 1.0);
        drawShip();
    }
    
    if(flashTimer > 20)
        flashTimer = 0;
}

void Player::draw() {
    if(!visible)
        return;
    for(unsigned int i = 0; i < bullets.size(); ++i) {
        if(bullets[i]->getVisible())
            bullets[i]->draw();
    } 
        
    //glColor3f(0.0, 1.0, 0.0);
    if(x < 0+width/2)
        x = width/2;
    if(y < 0+height/2)
        y = height/2;
    if(x > boundryX - width/2)
        x = boundryX - width/2;
    if(y > boundryY - height/2)
        y = boundryY - height/2;
    
    if(invincible) {
        flash();
    } else {
        drawShip();
    }
}

void Player::fire() {
    bullets.push_back(new Bullet);
    int i = bullets.size()-1;
   // printf("%d\n", i);
    bullets[i]->setup(bulletTexture, 0.5, 3, aspectRatio);
    bullets[i]->fire( x-(bullets[i]->getWidth()/2 * directionX), y + ((height)*directionY), directionX, directionY, 1.75, angle);
}  

int Player::getBulletNum() { return bullets.size(); }

void Player::moveLeft() { x -= speed; }
void Player::moveRight() { x += speed; }
void Player::moveUp() { y += speed; }
void Player::moveDown() { y -= speed; }

void Player::rotateRight() { angle--; }
void Player::rotateLeft() { angle++; }
void Player::setHealth(int newHealth) { health = newHealth; }
void Player::setVisible(bool Visible) { visible = Visible; }   
int Player::getWidth() { return width; }
int Player::getHealth() { return health; }
int Player::getHeight() { return height*aspectRatio; }
float Player::getX() { return x; }
float Player::getY() { return y; }
bool Player::isAlive() { return alive; }
bool Player::getVisible() { return visible; }
bool Player::getInvincible() { return invincible; }

void Player::takeHealth() { health -= 1; if(health < 0) health = 0; }
void Player::setBulletVisible(bool Visible, int i) { bullets[i]->setVisible(Visible); }
bool Player::getBulletVisible(int i) { return bullets[i]->getVisible(); }
float Player::getBulletX(int i) { return bullets[i]->getX(); }
float Player::getBulletY(int i) { return bullets[i]->getY(); }
int Player::getBulletWidth(int i) { return bullets[i]->getWidth(); }
int Player::getBulletHeight(int i) { return bullets[i]->getHeight(); }

void Player::respawn(int X, int Y) { invincible = true; invincTimer = 0; flashTimer = 0; x = X; y = Y; visible = true;}

