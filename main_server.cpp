#include "server.cpp"
#include "moteurs.cpp"

#include <thread>
#include <chrono>

#define MAX_RANGE_PWM 255

int main() {
    int port = 12345;  // Change this to your desired port number
    TCPServer server(port);
    
    std::thread server_thread( [&server]() {server.StartListening();} );
    server_thread.join();

//  Moteurs moteurs=Moteurs();   // raise ambiguïous overload of constructor
    Moteurs moteurs=Moteurs(27,18,12,17,22);
    int vitesse;

    while (true) {
	vitesse = server.getVitesse();
	switch(server.getDirection()[0])
		{
		case 'Z' :
		    std::cout << "Marche avant à vitesse " << std::setprecision(1) << (vitesse*100/MAX_RANGE_PWM) <<"%" << std::endl;
		    moteurs.marche_avant(vitesse);
                    sleep(1);
                    moteurs.stop_motors();
                    break;
                case 'D' :
		    std::cout << "Aller à droite à vitesse maximale" << std::endl;
                    moteurs.aller_droite(vitesse);
                    sleep(1);
                    moteurs.stop_motors();
                    break;
                case 'S' :
                    std::cout << "Marche arriere à vitesse " << std::setprecision(1) << (vitesse*100/MAX_RANGE_PWM) <<"%" << std::endl;
		    moteurs.marche_arriere(vitesse);
                    sleep(1);
                    moteurs.stop_motors();
                    break;
                case 'Q' :
                    std::cout << "Aller à gauche à vitesse maximale" << std::endl;
                    moteurs.aller_gauche(vitesse);
                    sleep(1);
                    moteurs.stop_motors();
                    break;
                case ' ' :
                    std::cout << "STOP !" << std::endl;
                    moteurs.stop_motors();
                    break;
		}
	std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;
}
