#Ceci est mon premier makefile

#Variables personnalisees
CC = g++
CFLAGS = -Wall -std=c++14 -Werror -Wextra
LIB = -pthread -ljsoncpp
OS=linux

EXEC = DataProjet


# $(shell test ! -e ${HOME}/programmes && mkdir ${HOME}/programmes)



#Identifier tous les fichiers .c contenu dans le repertoire
SRC = $(wildcard *.cpp)

#Créer une liste de fichiers .o a partir de la liste des fichiers .c contenu dans SRC
OBJ = $(SRC:.cpp=.o)


all: $(EXEC)


$(EXEC): $(OBJ)
	$(CC) -o $(EXEC) $^ $(CFLAGS) $(LIB)


%.o: %.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	@echo "Suppression des fichiers .o"
	rm -f $(OBJ)

mrproper: clean
	rm -f $(EXEC)

rebuild: mrproper $(EXEC)

build: $(EXEC) clean



