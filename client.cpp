#include "client.h"

TCPClient::TCPClient(const char* serverIP, int serverPort) {
    this->serverIP = serverIP;
    this->serverPort = serverPort;
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
}

TCPClient::~TCPClient() {
    Close();
}

void TCPClient::Connect() {
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(serverPort);

    if (inet_pton(AF_INET, serverIP, &serverAddress.sin_addr) <= 0) {
        perror("Invalid address/Address not supported");
        exit(EXIT_FAILURE);
    }

    if (connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }
}

void TCPClient::SendData(const std::string& data) {
    int sentBytes = send(clientSocket, data.c_str(), data.length(), 0);
    if (sentBytes < 0) {
        perror("Sending data failed");
        exit(EXIT_FAILURE);
    }

    std::cout << "Sent to server: " << data << std::endl;
}

void TCPClient::Close() {
    close(clientSocket);
}
