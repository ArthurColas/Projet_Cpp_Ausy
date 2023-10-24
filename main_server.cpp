#include "server.h"
#include "server.cpp"

int main() {
    int port = 12345;  // Change this to your desired port number
    TCPServer server(port);
    server.StartListening();
    return 0;
}
