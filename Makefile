# Compilateur
CC = gcc

# Options de compilation
CFLAGS = -Wall -Isrc -I.  # <--- on ajoute -I. pour chercher les .h à la racine

# Tous les fichiers .c dans src/
SRCS = $(wildcard src/*.c)

# Cible principale
tetris:
	$(CC) -o tetris $(SRCS) $(CFLAGS)

# Nettoyage
clean:
	rm -f tetris
    