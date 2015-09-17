#ifndef SHIP_H
#define SHIP_H

#ifdef __APPLE__
#include <OpenGL/gl.h>// Header File For The OpenGL32 Library
#include <OpenGL/glu.h>// Header File For The GLu32 Library
#include <GLUT/glut.h>// Header File For The GLut Library
#else
#include <GL/glut.h>
#include <GL/freeglut.h>
#endif

class Ship 
{
    public:
        Ship();
        int getHealth();
        int getX();
        int getY();
        void reset();
        void moveLeft();
        void moveRight();
        void draw();
    protected:   
        int width, height;
        int x, y;  
        int health; 
};


#endif
