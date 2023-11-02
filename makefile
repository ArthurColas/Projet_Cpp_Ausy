CC = g++
CFLAGS = -Wall -std=c++14 -Wextra
LIB = -pthread -ljsoncpp -lpigpio -lcurl -lm
OS = linux

SRC = server.cpp JsonDataManager.cpp moteurs.cpp moteurs.cpp post_ihm.cpp capteur_sonic.cpp capteur_pt.cpp
HEADER = $(SRC:.cpp=.h)
OBJ = $(SRC:.cpp=.o)
MAIN_SRC = main_server.cpp
MAIN_OBJ = $(MAIN_SRC:.cpp=.o)
EXEC = $(MAIN_SRC:.cpp=.exe)

all: $(EXEC)

main_server.exe: main_server.o server.o JsonDataManager.o moteurs.o post_ihm.o capteur_sonic.o capteur_pt.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIB)

%.o: %.cpp $(HEADER)
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	@echo "Suppression des fichiers .o"
	rm -f $(MAIN_OBJ)

mrproper: clean
	rm -f $(EXEC)

rebuild: mrproper $(EXEC)

build: $(EXEC) clean
