#pragma once
#include"prog.h"
#include<stdio.h>
#include<pthread.h>
#include"SDL2/SDL.h"
#include"config.h"
#define SWAP(a,b) a^=b;b^=a;a^=b

_Bool running = 1;

SDL_Window *window; 
SDL_Renderer *renderer;

SDL_Rect rect[6];
short colors[5][3] = {
	{COLOR_BG1},
	{COLOR_BG2},
	{COLOR_BG3},
	{COLOR_BG4},
	{COLOR_CUBE}
};
_Bool 
	right=0,
	up=0,
	kb[4],
	initEverythin(),
	initSDL(),
	createWindow(),
	createRenderer();
void 
	cube(),
	cubeMove(),
	swapCols(short a,short b, short c, short d),
	setupRenderer(),
	render(),
	loop(),
	*t2loop(void *value),
	*t3loop(void *value);