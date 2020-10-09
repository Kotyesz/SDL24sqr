#pragma once
#include"prog.h"
#include<stdio.h>
#include<pthread.h>
#include"SDL2/SDL.h"
#define TITLE "Alma"
#define WIDTH 800
#define HEIGHT 800
#define SWAP(a,b) a^=b;b^=a;a^=b
_Bool running = 1;

SDL_Window *window; 
SDL_Renderer *renderer;
SDL_Rect rect[4];
int colors[4][3] = {
	{255,0,0},
	{0,0,255},
	{0,0,0},
	{255,255,255}
};


_Bool initEverythin();
_Bool initSDL();
_Bool createWindow();
_Bool createRenderer();
void swapCols();
void setupRenderer();
void render();
void loop();
void *t2loop(void *value);