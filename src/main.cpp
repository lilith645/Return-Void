/*
 * main.cpp
 * This file is part of ReturnVoid
 *
 * Copyright (C) 2016 - Akuma
 *
 * ReturnVoid is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * ReturnVoid is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with ReturnVoid. If not, see <http://www.gnu.org/licenses/>.
 */

#include <GLFW/glfw3.h>

#ifdef __APPLE__
#include <OpenGL/gl.h>// Header File For The OpenGL32 Library
#include <OpenGL/glu.h>// Header File For The GLu32 Library
#else 
#include <GL/glc.h>
#include <GL/glu.h>
#include <png.h>
#endif

#include <stdio.h>

#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb/stb_image.h"

#include "../include/Menus/Shop.h"
#include "../include/Menus/MainMenu.h"
#include "../include/Menus/SettingsMenu.h"
#include "../include/Menus/HighscoreScreen.h"

#include "../include/GameTypes/Game.h"
#include "../include/GameTypes/Menu.h"
#include "../include/GameTypes/Story.h"

#include "../include/Namespaces/Settings.h"
#include "../include/Namespaces/Highscore.h"

//Screen dimension constants
const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;

int screenResX;
int screenResY;

int type = MAINMENU;

int refreshMillis = 20;

//Screen grid 100x100
double gridWidth = 100; //veiwing world x
double gridHeight = 100; // veiwing world y

//Aspect ratio of screen resolution
float aspectRatio;

//Scaled aspect Ratios, for the width and height
float aspectW;
float aspectH;

//Current coords of the mouse
int mouseX, mouseY;

//Keeps the current key state, keeps the key state of the previous key state
unsigned int  specialKey[5];
unsigned int  mouseBtnState[3];
unsigned int  prevSpeicalKey[5];
unsigned int  prevMouseBtnState[3];

unsigned char keyState[350];
unsigned char prevKeyState[350];

GLuint mouseTexture;

DisplayManager* Display[6] = { new MainMenu(), new Game(), new SettingsMenu(), new Shop(), new HighscoreScreen(), new Story() };

/*
void mouse() {
  int x, y;
 // SDL_GetMouseState( &x, &y );
  mouseY = (screenResY - y) * aspectH;
  mouseX = x*aspectW;
}*/

static void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos) {
  mouseX = xpos*aspectW;
  mouseY = (screenResY - ypos) * aspectH;
}

//Updates what keys are pressed
void keyboard(int key) {
  //printf("key: %d\n", key);
  keyState[key] = BUTTON_DOWN;
}

//Updates what keys are released
void keyboard_up(int key) {
    keyState[key] = BUTTON_UP;
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {    
  if(action == GLFW_PRESS) {
    keyboard(key);
  }
  if(action == GLFW_RELEASE) {
    keyboard_up(key);
  }
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
  mouseBtnState[button] = action;
  //  if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
  //      popup_menu();
}
  

void drawCursor() {
  if(type != ENDLESSGAME) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, mouseTexture);
    // Nice blue #1e00d5
    //glColor3f(0.117647059f, 0, 0.835294197f);
    glColor4f(1, 0.643137255, 0, 1.0f);
    glBegin(GL_QUADS);
      glTexCoord2f(0.0f, 1.0f);
      glVertex3f(mouseX-20, mouseY+20, 0.0);
      glTexCoord2f(1.0f, 1.0f);
      glVertex3f(mouseX+20, mouseY+20, 0.0);
      glTexCoord2f(1.0f, 0.0f);
      glVertex3f(mouseX+20, mouseY-20, 0.0);
      glTexCoord2f(0.0f, 0.0f);
      glVertex3f(mouseX-20, mouseY-20, 0.0);
    glEnd();

    glColor3f(1.0, 1.0, 1.0f);
    glDisable(GL_TEXTURE_2D);
  }
}

void clean() {
  Settings *settings = Settings::instance();
  settings->destroy();
  glfwTerminate();
}

void display(GLFWwindow* window, float deltaTime) {      
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Wipes screen clear

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);//Blends colours with alpha
  glClearColor(0.0f, 0.0f, 0.0f, 255.0f);
  
  //Texture options
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  glColor4ub(255,255,255,255); //sets full colours and alpha

  Display[type]->update(mouseX, mouseY, deltaTime, mouseBtnState, prevMouseBtnState, keyState, prevKeyState);
  Display[type]->draw();

  drawCursor();
  
  if(Display[type]->hasEnded()) {
    int newtype = Display[type]->getEndType();
    switch(newtype) {
      case EXIT:
        glfwSetWindowShouldClose(window, true);
        clean();
        exit(0);
        break;
      case ENDLESSGAME:
        Display[newtype]->setSeed(567894);
        break;
      case STORY:
       // Display[newtype]->setSeed(time(NULL));
        //Display[newtype]->setSeed(time(NULL));
        break;
    }
    Display[type]->clean();
    type = newtype;
    Display[type]->setup();
  }
 
  glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
  prevKeyState[ESC] = keyState[ESC];
  prevMouseBtnState[0] = mouseBtnState[0]; // Left Mouse Button
  
  glEnable (GL_BLEND);
  glBlendFunc (GL_ONE, GL_ONE);
}

GLFWwindow* init() {
  Settings *settings =  Settings::init();
  Highscore *highscore = Highscore::init();
    
  /* Initialize the library */
  GLFWwindow* window;
  if (!glfwInit()) {
    glfwSetWindowShouldClose(window, true);
    return window;
  }
  // Use OpenGL 2.1    
 
  bool isFullscreen = settings->getFullscreen();
  screenResX = settings->getWindowWidth();
  screenResY = settings->getWindowHeight();


  /* Create a windowed mode window and its OpenGL context */

  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

  if(isFullscreen) {
    //screenResX = 800;
    //screenResY = 600;
      
    //Create Window
    //  gWindow = SDL_CreateWindow("Return-Void", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,  screenResX, screenResY, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN );
      
    // Borderless fullscreen
    //SDL_SetWindowFullscreen(gWindow, SDL_WINDOW_FULLSCREEN_DESKTOP);
      
    // Fullscreen
    //  SDL_SetWindowFullscreen(gWindow, SDL_WINDOW_FULLSCREEN_DESKTOP);
    /* Borderless fullscreen
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
glfwWindowHint(GLFW_RED_BITS, mode->redBits);
glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
GLFWwindow* window = glfwCreateWindow(mode->width, mode->height, "My Title", monitor, NULL);
    */
    const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    screenResX = mode->width;
    screenResY = mode->height;
    
    window = glfwCreateWindow(SPACE_X_RESOLUTION, SPACE_Y_RESOLUTION, "Return-Void", glfwGetPrimaryMonitor(), NULL);

    printf("Entering fullscreen mode\n");
    settings->setFullscreen(true); 
    settings->setResolution(screenResX, screenResY);    
  } else {
    printf("Entering windowed mode\n");
  
    //Create Window
   // gWindow = SDL_CreateWindow("Return-Void", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,  screenResX, screenResY, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN );
    window = glfwCreateWindow(screenResX, screenResY, "Return-Void", NULL, NULL);
      
  }
  
  if (!window) {
    glfwTerminate();
    glfwSetWindowShouldClose(window, true);
    return window;
  }  
  
  aspectRatio = (float)screenResX / (float)screenResY;
  aspectW = (float)SPACE_X_RESOLUTION/(float)screenResX;
  aspectH = (float)SPACE_Y_RESOLUTION/(float)screenResY;
  
  gluOrtho2D(0.f, SPACE_X_RESOLUTION, 0.f, SPACE_Y_RESOLUTION);

  //screen =SDL_GetWindowSurface(gWindow);    
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

  return window;
}

int main(int argc, char* args[]) {
  
  GLFWwindow* window = init();
  
  /* Make the window's context current */
  glfwMakeContextCurrent(window);
  
  glfwSetKeyCallback(window, key_callback);
  glfwSetCursorPosCallback(window, cursor_pos_callback);
  glfwSetMouseButtonCallback(window, mouse_button_callback);
  
  mouseTexture = txt::LoadTexture("Textures/Game/Crosshair.png");
  //Initialize clear color
  glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
  
  Display[type]->setup();
  
  

  double lastTime = glfwGetTime();
  while(!glfwWindowShouldClose(window)) {
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    float ratio = width / (float)height;
    glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
    gluOrtho2D(0.f, SPACE_X_RESOLUTION, 0.f, SPACE_Y_RESOLUTION);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    double currentTime = glfwGetTime();
   // printf("Time: %f", currentTime);
    float deltaTime = float(currentTime - lastTime)  * 50;
    lastTime = glfwGetTime();
    display(window, deltaTime);  
    
    glfwSwapInterval(1);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  clean();
  glfwTerminate();
  return 0;
}
