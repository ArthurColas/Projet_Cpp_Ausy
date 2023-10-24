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

class TCPServer {
public:
    TCPServer(int port);
    ~TCPServer();

    void StartListening();
    void Close();

private:
    int serverSocket;
    int port;
};

#endif

