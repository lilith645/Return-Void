#!/usr/bin/make -f
CC = g++
CFLAGS  = -Wall -g -O3
PROG = Return-void

SRCS = ./src/main.cpp ./src/Menu.cpp ./src/Game.cpp ./src/Level.cpp ./src/Player.cpp ./src/EnemyBase.cpp ./src/EnemyTypes.cpp ./src/Bullet.cpp

LIBS = -lglut -lGLU -lGL -lpng

all: $(PROG)

$(PROG):	$(SRCS)
	$(CC) $(CFLAGS) -o $(PROG) $(SRCS) $(LIBS)

clean:
	rm -f $(PROG) 

