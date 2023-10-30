//#include "server.cpp"
//#include "moteurs.cpp"
#include "server.h"
#include "moteurs.h"
#include "JsonDataManager.h"

#include <thread>
#include <chrono>

#define MAX_RANGE_PWM 255

int main() {
    int port = 12345;  // Change this to your desired port number
    TCPServer server(port);
    std::thread server_thread( [&server]() {server.StartListening();} );
    
//  Moteurs moteurs=Moteurs();   // raise ambiguïous overload of constructor
    Moteurs moteurs=Moteurs(27,18,12,17,22);

    while (true) {
        std::cout << "Debug get vitesse : " << server.getVitesse() << std::endl;
        moteurs.SetVitesse( server.getVitesse() );
        std::cout << "Debug get direction : " << (server.getDirection())[0] << std::endl;
        switch(char(server.getDirection()[0]))
            {
            case 'z' :
                std::cout << "Marche avant à vitesse " << (moteurs.GetVitesse()*100/MAX_RANGE_PWM) <<"%" << std::endl;
                moteurs.marche_avant();
                sleep(1);
                moteurs.stop_motors();
                break;
            case 'd' :
                std::cout << "Aller à droite à vitesse maximale" << std::endl;
                moteurs.aller_droite();
                sleep(1);
                moteurs.stop_motors();
                break;
            case 's' :
                std::cout << "Marche arriere à vitesse " << (moteurs.GetVitesse()*100/MAX_RANGE_PWM) <<"%" << std::endl;
                moteurs.marche_arriere();
                sleep(1);
                moteurs.stop_motors();
                break;
            case 'q' :
                std::cout << "Aller à gauche à vitesse maximale" << std::endl;
                moteurs.aller_gauche();
                sleep(1);
                moteurs.stop_motors();
                break;
            case 'x' :
                std::cout << "STOP !" << std::endl;
                moteurs.stop_motors();
                moteurs.SetVitesse(0);
                break;
            }
        std::this_thread::sleep_for(std::chrono::seconds(2));
        }

        if(server_thread.joinable())
        {
            server_thread.join();
        }

    return 0;
}
