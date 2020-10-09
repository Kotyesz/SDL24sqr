#include"prog.h"

void swapCols(){
	int temp[3];
	for(int i=0;i<3;i++){
		SWAP(colors[0][i],colors[1][i]);
		SWAP(colors[1][i],colors[3][i]);
		SWAP(colors[2][i],colors[3][i]);
	}
}

void render(){
  	SDL_RenderClear(renderer);
	for(int i=0;i<4;i++){
		SDL_SetRenderDrawColor(renderer, colors[i][0], colors[i][1], colors[i][2], 255);
		SDL_RenderFillRect(renderer, &(rect[i]));
	}
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderPresent(renderer);
}
_Bool initEverythin(){
  if(!initSDL())return 0;
  if(!createWindow())return 0;
  if(!createRenderer())return 0;
  setupRenderer();
  return 1;
}
_Bool initSDL(){
	if ( SDL_Init( SDL_INIT_EVERYTHING ) == -1 ){
		printf(" Failed to initialize SDL : %s\n", SDL_GetError());
		return 0;
	}
	return 1;
}
_Bool createWindow(){
	window = SDL_CreateWindow( "win", 0, 0, WIDTH, HEIGHT, 0 );
	if ( window == NULL ){
		printf("Failed to create window : %s\n", SDL_GetError());
		return 0;
	}
  return 1; 
}
_Bool createRenderer(){
	renderer = SDL_CreateRenderer( window, -1, 0 );
	if ( renderer == NULL ){
		printf("Failed to create renderer : %s\n", SDL_GetError());
		return 0;
	}
	return 1;
}
void setupRenderer(){
	SDL_RenderSetLogicalSize( renderer, WIDTH, HEIGHT );
	SDL_SetRenderDrawColor( renderer, 0, 255, 0, 255 );
}

void loop(){
	while (running){
		SDL_Event event;
		SDL_Delay(0);
		if(SDL_PollEvent(&event) && event.type == SDL_QUIT )
			running=0;
		render();
	}
}

void *t2loop(void *value){
	while (running){
		swapCols(0);
		SDL_Delay(1500);
	}
	
	return NULL;
}

int main(){
	pthread_t thread;
	pthread_create(&thread,NULL,t2loop, NULL);
	if(!initEverythin()) return -1;
	for(int i=0;i<4;i++){
		rect[i].w=WIDTH/2;
		rect[i].h=HEIGHT/2;
	}
	rect[0].x=0;
	rect[0].y=0;
	rect[1].x=WIDTH/2-1;
	rect[1].y=0;
	rect[2].x=0;
	rect[2].y=HEIGHT/2-1;
	rect[3].x=WIDTH/2-1;
	rect[3].y=HEIGHT/2-1;
	loop();
	pthread_join(thread,NULL);
}
