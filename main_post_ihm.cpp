#include "post_ihm.h"
#include "capteur_sonic.h"
#include <thread>
#include <chrono>

int main() {
    capteur_sonic capteurs=capteur_sonic();
    while(true) {
	double gauche=capteurs.MeasureDist(16);
        double droite=capteurs.MeasureDist(21);
        double avant=capteurs.MeasureDist(20);

	double temperature=10;
        double pression=20;
        int batterie=30;

	post_ihm client=post_ihm();
	client.send(temperature, pression, batterie, gauche, droite, avant);

	std::this_thread::sleep_for(std::chrono::seconds(2));
   } return 0;
}

void client_post_ihm() {
        double gauche=capteurs.MeasureDist(16);
        double droite=capteurs.MeasureDist(21);
        double avant=capteurs.MeasureDist(20);

        double temperature=10;
        double pression=20;
        int batterie=30;

        post_ihm client=post_ihm();
        client.send(temperature, pression, batterie, gauche, droite, avant);
}

/*

    while (true) {
        // Get sensor data
        temperature = getTemperature();
        pression = getPression();
        batterie = getBatteriePercent();
        gauche = getDistanceGauche();
        droite = getDistanceDroite();
        avant = getDistanceAvant();

        std::thread temp_thread([&temperature]() {
            temperature = getTemperature();
        });

        if (temp_thread.joinable()) {
            temp_thread.join();
        }

        // Sleep for 2 seconds
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }

*/
