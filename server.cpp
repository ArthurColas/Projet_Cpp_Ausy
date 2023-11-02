#include "server.h"
#include <thread>
#include <mutex>

TCPServer::TCPServer(int port) {
    this->port = port;
    this->vitesse=0;
    this->direction="";

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
//    serverAddress.sin_addr.s_addr = INADDR_ANY;
// Specify the server's IP address here
    const char* serverIP = "192.168.1.45";
    if (inet_pton(AF_INET, serverIP, &(serverAddress.sin_addr)) <= 0) {
        perror("Invalid server IP address");
    exit(EXIT_FAILURE);
    }

    serverAddress.sin_port = htons(port);

    if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
        perror("Binding failed");
        exit(EXIT_FAILURE);
    }
}

TCPServer::~TCPServer() {
    Close();
}

void TCPServer::StartListening(std::mutex &server_mtx) {

    if (listen(serverSocket, 5) < 0) {
        perror("Listening failed");
        exit(EXIT_FAILURE);
    }

    std::cout << "Server listening on port " << port << "..." << std::endl;

    struct sockaddr_in clientAddress;
    socklen_t clientAddressLength = sizeof(clientAddress);
    int clientSocket;

    while (true) {

        clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddress, &clientAddressLength);

        if (clientSocket < 0) {
            perror("Accepting client connection failed");
            exit(EXIT_FAILURE);
        }

        char buffer[1024];
        memset(buffer, 0, sizeof(buffer));
        int bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesRead < 0) {
            perror("Reading from client failed");
            exit(EXIT_FAILURE);
        }

        std::cout << "Received from client: " << buffer << std::endl;

        // You can process the received data here and send a response if needed.
        JsonDataManager data_received = JsonDataManager(buffer);
        std::cout << "serverdebug direction : " << data_received.GetDirection() << std::endl;
        std::cout << "server debug vitesse : " << data_received.GetVitesse() << std::endl;
        // Scope du mutex
        {
            std::unique_lock<std::mutex> lock_server(server_mtx);
            setDirection( data_received.GetDirection() );
            setVitesse( data_received.GetVitesse() );
        }
        setDirection( data_received.GetDirection() );
        setVitesse( data_received.GetVitesse() );
        std::this_thread::sleep_for(std::chrono::milliseconds(500));

        close(clientSocket);
        }
}

void TCPServer::Close() {
    close(serverSocket);
}
