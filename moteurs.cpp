#include <iostream>
#include <pigpio.h>
#include <unistd.h>
#include <iomanip>

#include "moteurs.h"

Moteurs::Moteurs(){
    pinAvantD=27;
    pinArriereD=18;
    pinArriereG=12;
    pinAvantG=17;
    pinEEP=22;
    init_gpio_moteurs();
}

Moteurs::Moteurs(int avD , int arD, int arG, int avG, int eep) {
    pinAvantD=avD;
    pinArriereD=arD;
    pinArriereG=arG;
    pinAvantG=avG;
    pinEEP=eep;
    init_gpio_moteurs();

}

Moteurs::~Moteurs() {
}

void Moteurs::init_gpio_moteurs() {
    gpioInitialise();
    gpioSetMode(pinAvantD, PI_OUTPUT);
    gpioSetMode(pinArriereD, PI_OUTPUT);
    gpioSetMode(pinArriereG, PI_OUTPUT);
    gpioSetMode(pinAvantG, PI_OUTPUT);
    gpioSetMode(pinEEP, PI_OUTPUT);

    // Activer la carte DRV8833
    gpioWrite(pinEEP, 1);
    SetVitesse(0);
}

void Moteurs::stop_motors() {
    gpioPWM(pinAvantD, 0);
    gpioPWM(pinArriereD, 0);
    gpioPWM(pinArriereG, 0);
    gpioPWM(pinAvantG, 0);
}

void Moteurs::marche_avant() {
    stop_motors();
    gpioPWM(pinAvantD, GetVitesse());
    gpioPWM(pinAvantG, GetVitesse());
}

void Moteurs::marche_arriere() {
    stop_motors();
    gpioPWM(pinArriereD, GetVitesse());
    gpioPWM(pinArriereG, GetVitesse());
}

void Moteurs::aller_droite() {
    stop_motors();
    gpioPWM(pinArriereD, GetVitesse());
    gpioPWM(pinAvantG, GetVitesse());
}

void Moteurs::aller_gauche() {
    stop_motors();
    gpioPWM(pinAvantD, GetVitesse());
    gpioPWM(pinArriereG, GetVitesse());
}

void Moteurs::rotation() {
    stop_motors();
    gpioPWM(pinAvantD, GetVitesse());
    gpioPWM(pinArriereG, GetVitesse());
    sleep(1);
    gpioPWM(pinArriereD, GetVitesse());
    gpioPWM(pinAvantG, GetVitesse());
}

// fonction appelée dans le thread moteur du programme principal
void Moteurs::controle_moteurs(TCPServer &server, std::mutex &server_mtx) {

    char direction;
    while (true) {
        // Scope du mutex
        {
            std::unique_lock<std::mutex> lock_server(server_mtx);
            std::cout << "Debug get vitesse : " << server.getVitesse() << std::endl;
            SetVitesse( server.getVitesse() );
            direction = server.getDirection()[0];
            std::cout << "Debug get direction : " << (server.getDirection())[0] << std::endl;
        }

        switch(direction)
            {
            case 'Z' :
                std::cout << "Marche avant " << std::endl;
                //moteurs.marche_avant();
                sleep(1);
                stop_motors();
                break;
            case 'D' :
                std::cout << "Aller à droite " << std::endl;
                //moteurs.aller_droite();
                sleep(1);
                stop_motors();
                break;
            case 'S' :
                std::cout << "Marche arriere " << std::endl;
                //moteurs.marche_arriere();
                sleep(1);
                stop_motors();
                break;
            case 'Q' :
                std::cout << "Aller à gauche " << std::endl;
                //moteurs.aller_gauche();
                sleep(1);
                stop_motors();
                break;
            case 'X' :
                std::cout << "STOP !" << std::endl;
                stop_motors();
                SetVitesse(0);
                break;
            }
        std::this_thread::sleep_for(std::chrono::seconds(1));
        }
}
