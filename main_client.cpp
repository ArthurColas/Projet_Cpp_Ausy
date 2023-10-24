
#include "client.h"
#include "client.cpp"

int main() {
    const char* serverIP = "127.0.0.1"; // Change this to the server's IP address
    int serverPort = 12345; // Change this to the server's port number
    TCPClient client(serverIP, serverPort);
    client.Connect();

    std::string message = "Hello, Server!";
    client.SendData(message);

    return 0;
}
