#include"prog.h"
void error(const char *e){
	puts(e);
	puts(SDL_GetError());
	exit(EXIT_FAILURE);
}
void swapCols(short a,short b, short c, short d){
	int temp[3];
	for(int i=0;i<3;i++){
		for(int j=0;RANDOMCOLOR && j<5;j++)
			for(int k=0;k<3;k++)
				colors[j][k] = rand()%255;
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
void initSDL(){
	if ( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
		error(" Failed to initialize SDL : %s\n");
}
void createWindow(){
	window = SDL_CreateWindow( TITLE, 0, 0, WIDTH, HEIGHT, 0 );
	if ( window == NULL )
		error("Failed to create window : %s\n");
}
void createRenderer(){
	renderer = SDL_CreateRenderer( window, -1, 0 );
	if ( renderer == NULL )
		error("Failed to create renderer : %s\n");
}
void setupRenderer(){
	SDL_RenderSetLogicalSize( renderer, WIDTH, HEIGHT );
	SDL_SetRenderDrawColor( renderer, 0, 255, 0, 255 );
}

void loop(){
	while (running){
		SDL_Event event;
		SDL_Delay(0);
		running = !(SDL_PollEvent(&event) && event.type == SDL_QUIT );
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
	for(int i=0;i<CUBE_SIZE/2;i++){
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
	if(rect[4].x<CUBE_SIZE/2) right=1;
	if(rect[4].y>HEIGHT-rect[4].h-1) up=0;
	if(rect[4].y<CUBE_SIZE/2) up=1;
	rect[4].x+=(rand()%5)*USERANDOM+1*(right-0.5)*2;
	rect[4].y+=(rand()%5)*USERANDOM+1*(up-0.5)*2;
}

int main(){
	srand(time(NULL));
	pthread_t threads[2];
	pthread_create(&threads[0],NULL,t2loop, NULL);
	pthread_create(&threads[1],NULL,t3loop, NULL);
	initSDL();
  	createWindow();
  	createRenderer();
  	setupRenderer();
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
	rect[4].w=CUBE_SIZE;
	rect[4].h=CUBE_SIZE;
	rect[4].x=WIDTH/2-CUBE_SIZE/2;
	rect[4].y=HEIGHT/2-CUBE_SIZE/2;
	loop();
	pthread_join(threads[0],NULL);
	pthread_join(threads[1],NULL);
	return 0;
}
