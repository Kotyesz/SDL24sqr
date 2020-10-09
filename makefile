run: prog.c prog.h config.h
	gcc prog.c -o run -lSDL2 -lpthread
