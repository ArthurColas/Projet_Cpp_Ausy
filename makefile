CC = g++
CFLAGS = -Wall -std=c++14 -Werror -Wextra
LIB = -pthread -ljsoncpp
OS = linux

SRC = $(wildcard *.cpp)
MAIN_SRC = main_client.cpp main_server.cpp
OBJ = $(MAIN_SRC:.cpp=.o)
EXEC = $(MAIN_SRC:.cpp=.exe)

all: $(EXEC)

%.exe: %.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIB)

%.o: %.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	@echo "Suppression des fichiers .o"
	rm -f $(OBJ)

mrproper: clean
	rm -f $(EXEC)

rebuild: mrproper $(EXEC)

build: $(EXEC) clean
























