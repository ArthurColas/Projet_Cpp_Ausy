//#include "server.cpp"
//#include "moteurs.cpp"
#include "server.h"
#include "moteurs.h"
#include "JsonDataManager.h"
#include "post_ihm.h"
#include "capteur_sonic.h"

#include <thread>
#include <chrono>

#define MAX_RANGE_PWM 255

std::mutex server_mtx;

int main() {

// INITIALISATION DES VARIABLES ET OBJETS
   int port = 8085;  
   TCPServer server(port);

   Moteurs moteurs=Moteurs(27,18,12,17,22);

   double gauche, droite, avant, temperature, pression;
   int batterie;
   post_ihm client=post_ihm();
   capteur_sonic capteurs = capteur_sonic();

   std::mutex server_mtx;

// THREADS

   std::thread server_thread( [&server, &server_mtx]() {
        server.StartListening(server_mtx);
   } );

    std::thread client_thread( [&client,&temperature, &pression, &batterie, &gauche, &droite, &avant]()
        {
           while(true) {
                client.send(temperature, pression, batterie, gauche, droite, avant);
                std::this_thread::sleep_for(std::chrono::seconds(2));
         }
   } );

   std::thread capteurs_sonic_thread( [&capteurs, &gauche, &droite, &avant]()
        {
           while(true) {
                gauche=capteurs.MeasureDist(16);
                droite=capteurs.MeasureDist(21);
                avant=capteurs.MeasureDist(20);
                std::this_thread::sleep_for(std::chrono::seconds(2));
         }
   } );

/*   std::thread temperature_thread( [&capteur_temp, &temperature]()
        {
           while(true) {
                temperature= capteurs_temp.getTemperature();
                std::this_thread::sleep_for(std::chrono::seconds(2));
           }
   } );
*/

   std::thread moteurs_thread( [&moteurs, &server, &server_mtx]()
   {
        moteurs.controle_moteurs(server, server_mtx);
   } );


        if(server_thread.joinable())
        {
            server_thread.join();
        }
        if(client_thread.joinable())
        {
            client_thread.join();
        }
        if(capteurs_sonic_thread.joinable())
        {
            capteurs_sonic_thread.join();
        }
        if(moteurs_thread.joinable())
        {
            moteurs_thread.join();
        }

    return 0;
}
