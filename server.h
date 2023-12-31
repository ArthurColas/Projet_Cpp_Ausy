#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <cerrno>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h> // Include the header for inet_pton
#include <mutex>

#include "JsonDataManager.h"

class TCPServer {
public:
    TCPServer(int port);
    ~TCPServer();

    void setDirection(string dir) {direction = dir;}
    string getDirection() {return direction;}
    void setVitesse(int vit) {vitesse = vit;}
    int getVitesse() {return vitesse;}

    void StartListening(std::mutex &server_mtx);
    void Close();

private:
    int serverSocket;
    int port;
    string direction;
    int vitesse;
};

#endif
