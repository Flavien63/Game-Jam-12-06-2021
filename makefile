CC= gcc
OPT  = -c -ansi -Wextra -Wall -g
SDL2 = -lSDL2 -lSDL2_gfx -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lSDL2_net

prog : main.o 
	$(CC) -o prog main.o

main.o : main.c main.h
	$(CC) $(SDL2) $(OPT) main.c
