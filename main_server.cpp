#include "server.h"
#include "server.cpp"
#include <thread>
#include <chrono>

int main() {
    int port = 12345;  // Change this to your desired port number
    TCPServer server(port);
    
    std::thread server_thread( [&server]() {server.StartListening();} );
    server_thread.join();

    while (true) {
	cout << server.getDirection() << endl;
	std::this_thread::sleep_for(std::chrono::seconds(2));
    }

    return 0;
}
