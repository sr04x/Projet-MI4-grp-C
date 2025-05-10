CC = gcc

# Options de compilation
CFLAGS = -Wall

# Fichiers communs à plusieurs cibles
SRCS = main.c piece.c score.c grille.c timer.c partieee.c

# Cible principale : tetris
tetris: 
	$(CC) -o tetris $(SRCS) $(CFLAGS)   

    
# Cible pour nettoyer les fichiers générés 
clean: 
	rm -f tetris
    