#include"prog.h"

void swapCols(short a,short b, short c, short d){
	int temp[3];
	for(int i=0;i<3;i++){
		SWAP(colors[a][i],colors[b][i]);
		SWAP(colors[b][i],colors[d][i]);
		SWAP(colors[c][i],colors[d][i]);
	}
}


void render(){
  	SDL_RenderClear(renderer);
	for(int i=0;i<4;i++){
		SDL_SetRenderDrawColor(renderer, colors[i][0], colors[i][1], colors[i][2], 255);
		SDL_RenderFillRect(renderer, &(rect[i]));
	}
	cube();
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
	window = SDL_CreateWindow( TITLE, 0, 0, WIDTH, HEIGHT, 0 );
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
    	if(ROT_RIGHT) swapCols(0,2,1,3);
		else swapCols(0,1,2,3);
		SDL_Delay(BACK_SPEED*100);
	}
	
	return NULL;
}
void *t3loop(void *value){
	while(running){
		SDL_Delay(CUBE_SPEED);
		cubeMove();
	}
}
void cube(){
	for(int i=0;i<50;i++){
		SDL_Rect cube;
		cube.w=rect[4].w;
		cube.h=rect[4].h;
		cube.x=rect[4].x-i;
		cube.y=rect[4].y-i;
		SDL_SetRenderDrawColor(renderer, colors[4][0]-i, colors[4][1]-i, colors[4][2]-i, 255);
		SDL_RenderFillRect(renderer, &cube);
	}
}

void cubeMove(){
	if(rect[4].x>WIDTH-rect[4].w-1) right=0;
	if(rect[4].x<50) right=1;
	if(rect[4].y>HEIGHT-rect[4].h-1) up=0;
	if(rect[4].y<50) up=1;
	if(USERANDOM){	
		rect[4].x+=((rand()%5)+1)*(right-0.5)*2;
		rect[4].y+=((rand()%5)+1)*(right-0.5)*2;
	}else{
		rect[4].x+=(right-0.5)*2;
		rect[4].y+=(up-0.5)*2;
	}
}

int main(){
	srand(time(NULL));
	pthread_t threads[2];
	pthread_create(&threads[0],NULL,t2loop, NULL);
	pthread_create(&threads[1],NULL,t3loop, NULL);
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
	rect[4].w=100;
	rect[4].h=100;
	rect[4].x=WIDTH/2-50;
	rect[4].y=HEIGHT/2-50;
	loop();
	pthread_join(threads[0],NULL);
	pthread_join(threads[1],NULL);
	return 0;
}
