CC= gcc
OPT  = -c -ansi -Wextra -Wall -g
SDL2 = -lSDL2 -lSDL2_gfx -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lSDL2_net

prog : main.o couleurs.o dessiner.o init_level.o
	$(CC) main.o couleurs.o dessiner.o init_level.o $(SDL2) -o prog 

main.o : main.c main.h couleurs.o 
	$(CC) $(OPT) main.c

dessiner.o : dessiner.c dessiner.h 
	$(CC) $(OPT) dessiner.c

init_level.o : init_level.c init_level.h
	$(CC) $(OPT) init_level.c

couleurs.o : couleurs.c couleurs.h
	$(CC) $(OPT) couleurs.c

clear :
	rm main.o couleurs.o dessiner.o
	
propre :
	rm prog
