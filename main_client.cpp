#include "client.h"
//#include "client.cpp"
#include "JsonDataManager.h"
//#include "JsonDataManager.cpp"

#define MAX_RANGE_PWM 255

int main() {
    const char* serverIP = "127.0.0.1"; // Change this to the server's IP address
    int serverPort = 12345; // Change this to the server's port number
    TCPClient client(serverIP, serverPort);
    client.Connect();

    while (true) {

    std::string message, saisie, vitesse;

    std::cout << " Z avance, Q gauche, S recule, D droite, X arret " << std::endl;
    std::cin >> saisie;
    std::cout << "Choisir la vitesse entre 1 et " << MAX_RANGE_PWM << std::endl;
    std::cin >> vitesse;

    //std::string message = "Hello, Server!";
    message= JsonDataManager(saisie, std::stoi(vitesse)).GetJson();

    client.SendData(message);

    }
    return 0;
}
