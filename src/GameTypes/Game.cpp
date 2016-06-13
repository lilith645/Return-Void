#include "../../include/GameTypes/Game.h"

Game::Game() {
  //glutSetCursor(GLUT_CURSOR_NONE);
  seed = time(NULL);
  boostRand.newSeed(seed);
}

void Game::draw() {
  drawBackground();

  ship.draw();
  for(unsigned int i = 0; i < enemy.size(); ++i) {
      enemy[i]->draw();
  }
   
  if(DRAWQUADTREE)
    Collisions::drawQuadTree();
  if(DRAWHITBOX)
    Collisions::drawHitBoxes(&ship, enemy);

  drawCrosshair();
  lbWave.draw();
  lbScore.draw();
  if(paused)
    pMenu.draw();
}

void Game::setup() {
  boostRand.newSeed(seed);

  paused = false;

  score = 0;
  wave = 0;

  lbWave.setup(SPACE_X_RESOLUTION/2, SPACE_Y_RESOLUTION/2, 0.5, true);
  lbWave.setColour( 1.0,  0.0,  1.0);

  lbScore.setup(SPACE_X_RESOLUTION, SPACE_Y_RESOLUTION/20 * 19.2, 0.3, false);
  lbScore.setColour( 1.0,  1.0,  1.0);
  std::stringstream ss;
  ss << score;
  std::string strScore = "Score: " + ss.str();
  lbScore.setText(strScore.c_str(), strScore.length() + 1);

  level = 1;
  isNew = true;
  ended = false;
  ChRadius = 20;
  type = MAINMENU;
  ChTexture = txt::LoadTexture("Textures/Game/Crosshair.png");

  pMenu.setup();
}

void Game::clean() {
  ship.clean();
  enemy.erase(enemy.begin(), enemy.end());
}

void Game::newWave() {
  wave++;
  
  std::stringstream ss;
  ss << wave;
  std::string str = "Wave " + ss.str();
  lbWave.setText(str.c_str(), str.length() + 1);
  lbWave.setTimer(40);

  unsigned int numOfEnemies = boostRand.Int(0, wave*10);
  for(unsigned int i = 0; i < numOfEnemies; ++i) {
    switch(boostRand.Int(1, 2)) {
      case 1:
        enemy.push_back(new BasicEnemy);
        break;
      case 2:
        enemy.push_back(new CorruptedStarShip);
        break;
    }
    enemy[i]->setup();
    enemy[i]->setX(boostRand.Int((int)(enemy[i]->getWidth()/2),               SPACE_X_RESOLUTION-enemy[i]->getWidth()));
    enemy[i]->setY(boostRand.Int((enemy[i]->getHeight()+SPACE_Y_RESOLUTION),  (int)(SPACE_Y_RESOLUTION*(2+wave))));
  }
  boostRand.newSeed(boostRand.Int(0, 9999999999));
}

void Game::restart() {
  ship.setup();
}

void Game::update(float mouseX, float mouseY, unsigned int* mouseBtnState, unsigned int* prevMouseBtnState, unsigned char* keyState, unsigned char* prevKeyState) {
  ChX = mouseX;
  ChY = mouseY;

  if(keyState[ESC] == BUTTON_DOWN && prevKeyState[ESC] != BUTTON_DOWN) {
    prevKeyState[ESC] = keyState[ESC];
    paused = !paused;
  }

  if(!paused) {
    if(isNew) {
      ship.setup();
      isNew = false;
    }
    if(enemy.size() == 0)
      newWave();

    ship.update(mouseX, mouseY, mouseBtnState, keyState, prevKeyState);

    for(unsigned int i = 0; i < enemy.size(); ++i) {
      enemy[i]->update();
      if(enemy[i]->getWaskilled()) {
        score += enemy[i]->getScore();
        std::stringstream ss;
        ss << score;
        std::string str = "Score: " + ss.str();
        lbScore.setText(str.c_str(), str.length() + 1);
      }
      if(!enemy[i]->isVisible() && enemy[i]->getTotalNumOfBullets() == 0) {
        enemy.erase(enemy.begin()+i);
      }
    }

    Collisions::detect(&ship, enemy);

    if(!ship.getVisible()) {
      type = MAINMENU;
      ended = true;
    }

    lbWave.update();
  } else {
    pMenu.update(mouseX, mouseY, mouseBtnState, prevMouseBtnState);
    if(!pMenu.isPaused())
      paused = !paused;
     if(pMenu.hasEnded()) {
      type = MAINMENU;
      ended = true;
    }
  }
}

void Game::drawCrosshair() {
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, ChTexture);
  // Nice blue #1e00d5
  glColor3f(0.117647059f, 0, 0.835294197f);
  if(!paused) {
    if(ship.getDistanceFromCursor() > MINIMUM_DISTANCETOSHIP) {
      lastChX = ChX;
      lastChY = ChY;
    } else {
      lastChX = ship.getX() +  MINIMUM_DISTANCETOSHIP*ship.getDirectionX();
      lastChY = ship.getY() + MINIMUM_DISTANCETOSHIP*ship.getDirectionY();
    }
  } else {
    lastChX = ChX;
    lastChY = ChY;
  }

  glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(lastChX-ChRadius, lastChY+ChRadius, 0.0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(lastChX+ChRadius, lastChY+ChRadius, 0.0);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(lastChX+ChRadius, lastChY-ChRadius, 0.0);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(lastChX-ChRadius, lastChY-ChRadius, 0.0);
  glEnd();

  glColor3f(0.0, 0.0, 0.0f);
  glDisable(GL_TEXTURE_2D);

}

void Game::drawBackground() {
  // Draw Score

}
