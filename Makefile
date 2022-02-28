BIN = httpparseur

SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -ansi -pedantic

OBJECTSPATH = objects/

CC = gcc

TAR = Projet-HTTP-save
IGNORE1 = .vscode
IGNORE2 = get1
IGNORE3 = httpparseur
IGNORE4 = .gitignore




all: $(BIN)
	./$<

exe: $(BIN)

debug: $(BIN)                 # J'ai rajouter une option pour faire l'executable tout en l'executant avec le debugger ddd
	ddd $<

$(BIN): $(OBJ)
	$(CC) $(OBJECTSPATH)*.o $(CFLAGS) -o $@
	 
%.o: %.c                   # Je rejoute l'option -g pour pouvoir utiliser le debugger   
	$(CC) -g -c $< -o $(OBJECTSPATH)$@

tar: clear
	dir=$$(basename $$PWD) && echo "compressing $(dir)" && cd .. && \
	tar cvfz "$(TAR).tgz" \
	--transform="s,^$$dir,$(TAR)," \
	--exclude="$(IGNORE1)" --exclude="$(IGNORE2)" --exclude="$(IGNORE3)" --exclude="$(IGNORE4)" "$$dir" --verbose --show-transformed-names

mrproper: clear
	rm -f $(BIN)
	
clear:
	rm -f $(OBJECTSPATH)*.o
