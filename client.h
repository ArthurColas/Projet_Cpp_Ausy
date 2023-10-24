#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <cerrno>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

class TCPClient {
public:
    TCPClient(const char* serverIP, int serverPort);
    ~TCPClient();

    void Connect();
    void SendData(const std::string& data);
    void Close();

private:
    int clientSocket;
    const char* serverIP;
    int serverPort;
};

#endif
