BIN = httpparseur

SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -ansi -pedantic

OBJECTSPATH = ../objects/

CC = gcc




all: $(OBJ)

%.o: %.c                   # Je rejoute l'option -g pour pouvoir utiliser le debugger   
	$(CC) -g -c $< -o $(OBJECTSPATH)$@
