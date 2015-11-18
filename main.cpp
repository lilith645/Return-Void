//Version 0.1

#ifdef __APPLE__
#include <OpenGL/gl.h>// Header File For The OpenGL32 Library
#include <OpenGL/glu.h>// Header File For The GLu32 Library
#include <GLUT/glut.h>// Header File For The GLut Library
#else
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#endif
  
#include <stdio.h> 
#include <stdlib.h> 
#include <time.h>      /* time */
#include <iostream>
#include <fstream>

#include "Game.h"
#include "Menu.h"

#define BUTTON_UP   0
#define BUTTON_DOWN 1

enum Screen {
    sMenu,
    sOptions, 
    sGame
};

GLuint menuTextures[4];
GLuint gameTextures[19];

double windowWidth = 100; //veiwing world x
double windowHeight = 100; // veiwing world y

float aspectRatio;
float aspectW;
float aspectH;

int refreshMillis = 20; 
double gridSquareWidth; 

unsigned char keyState[255];
unsigned char prevKeyState[255];

float mouseX, mouseY;

bool alive;

Game game; 
Menu menu;
Screen screen;

void Timer(int value) {
   glutPostRedisplay();    // Post a paint request to activate display()
   glutTimerFunc(refreshMillis, Timer, 0); // subsequent timer call at milliseconds
}

void keyboard(unsigned char key, int x, int y) {
    keyState[putchar (tolower(key))] = BUTTON_DOWN;
}

void keyboard_up(unsigned char key, int x, int y) {
        keyState[putchar (tolower(key))] = BUTTON_UP;        
}

void specialKeys(int key, int x, int y) {
     switch (key) { 
     case GLUT_KEY_LEFT:
            break; 
     }
}

void mouse(int x, int y) {
    mouseX = x * aspectW;
    mouseY = y * aspectH;
    //printf("x: %f y: %f\n", mouseX, mouseY);
}

void drawChar(int PosX, int PosY, float R, float G, float B, char str[25], int length) {
    glColor3f(R, G, B); // Text Colour
    glRasterPos2i(PosX, PosY); //coordinates of text
    glColor4f(0.0f, 0.0f, 1.0f, 1.0f); //colour blue
    
    void * font = GLUT_BITMAP_HELVETICA_18;//set font http://www.opengl.org/documentation/specs/glut/spec3/node76.html#SECTION000111000000000000000
       
     for(int i = 0; i < length; i++) {
             glutBitmapCharacter(font, str[i]);
     }  
     glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	
	glColor4ub(255,255,255,255);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    int screenNum;
    switch(screen) {
       case sGame:
           if(keyState[27] == BUTTON_DOWN) {//ESC
               alive = true;
               screen = sMenu;
           }
           game.draw();
           if(!alive) {
               game.drawGameOver();
               if(keyState[(unsigned char)'y'] == BUTTON_DOWN) {
                   game.setup(aspectRatio);
                   alive = true;
               } else  if(keyState[(unsigned char)'n'] == BUTTON_DOWN) {
                   screen = sMenu;
                   alive = true;
               }
           } else {
               alive = game.Tick(keyState, prevKeyState, mouseX, mouseY);
           }
               
           break;
       case sMenu:           
           glutSetCursor(GLUT_CURSOR_NONE);
           screenNum = menu.keyPress(keyState, prevKeyState);
           if(keyState[27] == BUTTON_DOWN) {//ESC
               if(prevKeyState[27] != BUTTON_DOWN) {
                   glutLeaveGameMode();
                   exit(1);
               }
           }
           
           switch(screenNum) {
               case -1:
                   glutLeaveGameMode();
                   exit(-1);                  
                   break;
               case 1: 
                   screen = sGame;
                   game.setup(aspectRatio);
                   break;
               case 2:
                   screen = sOptions;
                   menu.readSettings();                   
                   menu.changeMenu(sOptions); 
                   break;              
           }
           menu.draw();
           break;
       case sOptions:
           screenNum = menu.keyPress(keyState, prevKeyState);
           menu.draw();
           if(keyState[27] == BUTTON_DOWN && prevKeyState[13] != BUTTON_DOWN) {//ESC
               menu.saveSettings();
               screen = sMenu;
               menu.changeMenu(sMenu); 
           }
           if(screenNum == 3) {
               screen = sMenu;
               menu.changeMenu(sMenu);
           }
           break;
    }
    prevKeyState[27] = keyState[27];//esc
    prevKeyState[13] = keyState[13];//enter
    char versionStr[12] = "Version_0.2";
    drawChar(0, 98, 0.5f, 0.0f, 1.0f, versionStr, 12);
    glEnable (GL_BLEND);
    glBlendFunc (GL_ONE, GL_ONE);
   // glFlush();       
    glutSwapBuffers(); 
}

void setup() { 
    int const screenResX = glutGet(GLUT_SCREEN_WIDTH);
    int const screenResY = glutGet(GLUT_SCREEN_HEIGHT);
    aspectRatio = (float)screenResX / screenResY;
    aspectW = 100.0f/screenResX;
    aspectH = 100.0f/screenResY;
    screen = sMenu;    
    alive = true;

    menu.setup();
}

int main(int argc, char** argv) {
	/* initialize random seed: */
    srand (time(NULL));
    
    glClearColor(0.0f, 0.0f, 0.0f, 255.0f);         // black background

    glClearColor(0.0, 0.0, 0.0, 255.0);         // black background

	glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
    char mode_string[24];
 
    sprintf(mode_string, "%dx%d:32@60", glutGet(GLUT_SCREEN_WIDTH),
    glutGet(GLUT_SCREEN_HEIGHT));
    glutGameModeString(mode_string);
    if(glutGameModeGet(GLUT_GAME_MODE_POSSIBLE)) {
        printf("GameMode %s is possible\n", mode_string);
        
        // destroys the current graphics window
        glutDestroyWindow(0);
        glutEnterGameMode();
    } else {
        printf("GameMode %s NOT possible\n", mode_string);
        glutFullScreen();
    }       
    // hide the cursor
    glutSetCursor(GLUT_CURSOR_NONE);
    
    glBlendFunc(GL_ONE_MINUS_DST_ALPHA,GL_DST_ALPHA);
    glAlphaFunc(GL_GREATER, 0.1);
    glEnable(GL_ALPHA_TEST);
    
    glutIgnoreKeyRepeat(1);
    
    glutDisplayFunc(display);
    glutTimerFunc(0, Timer, 0);   
    glutKeyboardFunc(keyboard); 
    glutKeyboardUpFunc(keyboard_up); 
    glutSpecialFunc(specialKeys);   
    glutMotionFunc(mouse);
    glutPassiveMotionFunc(mouse);
    setup();

    int const screenResX = glutGet(GLUT_SCREEN_WIDTH);
    int const screenResY = glutGet(GLUT_SCREEN_HEIGHT);


//    glOrtho(0.0, windowWidth, 0.0, windowHeight, -1.0, 1.0);   // setup a 100x100x2 viewing world
    glOrtho(0, (100.0/screenResX)*screenResX, 0, (100.0/screenResY)*screenResY, -1.0, 1.0);   // setup a 100x100x2 viewing world
   // glOrtho(-aspectRatio*100, aspectRatio*100, -1*100, 1*100, -1, 1);
    glClearColor(0.0, 0.0, 0.0, 255.0);
    
    printf("Setup Complete\n");
     
    glutMainLoop(); 
    return 0;
}
