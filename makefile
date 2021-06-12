CC= gcc
OPT  = -c -ansi -Wextra -Wall -g
SDL2 = -lSDL2 -lSDL2_gfx -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lSDL2_net

prog : main.o couleurs.o dessiner.o
	$(CC) -o prog main.o

main.o : main.c main.h
	$(CC) $(SDL2) $(OPT) main.c

couleurs.o : couleurs.c couleurs.h
	$(CC) $(OPT) couleurs.c

dessiner.o : dessiner.c dessiner.h
	$(CC) $(OPT) dessiner.c

clear :
	rm main.o couleurs.o dessiner.o
	
propre :
	rm prog
