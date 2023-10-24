#include "server.h"
#include "server.cpp"
#include <thread>

int main() {
    int port = 12345;  // Change this to your desired port number
    TCPServer server(port);
    
    std::thread server_thread( [&server]() {server.StartListening();} );
    server_thread.join();

    return 0;
}
