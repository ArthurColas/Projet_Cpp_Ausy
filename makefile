CC = g++
CFLAGS = -Wall -std=c++14 -Wextra
LIB = -pthread -ljsoncpp -lpigpio -lcurl
OS = linux

SRC = client.cpp server.cpp JsonDataManager.cpp moteurs.cpp
HEADER = $(SRC:.cpp=.h)
OBJ = $(SRC:.cpp=.o)
MAIN_SRC = main_client.cpp main_server.cpp main_post_ihm.cpp
MAIN_OBJ = $(MAIN_SRC:.cpp=.o)
EXEC = $(MAIN_SRC:.cpp=.exe)

all: $(EXEC)

#%.exe: %.o
#	$(CC) -o $@ $^ $(CFLAGS) $(LIB)
main_client.exe: main_client.o client.o JsonDataManager.o moteurs.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIB)

main_server.exe: main_server.o server.o JsonDataManager.o moteurs.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIB)

main_post_ihm.exe: main_post_ihm.o post_ihm.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIB)

#$(MAIN_OBJ): $(MAIN_SRC)
#	$(CC) -o $@ -c $< $(CFLAGS)

#$(OBJ): $(SRC) $(HEADER)
%.o: %.cpp $(HEADER)
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	@echo "Suppression des fichiers .o"
	rm -f $(MAIN_OBJ)

mrproper: clean
	rm -f $(EXEC)

rebuild: mrproper $(EXEC)

build: $(EXEC) clean
