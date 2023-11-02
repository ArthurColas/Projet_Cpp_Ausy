#include <iostream>
#include <pigpio.h>
#include <unistd.h>
#include <iomanip>
#include <thread>
#include <mutex>

#include "server.h"
#include "moteurs.h"

#define COMMAND_DELAY 500

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

void Moteurs::SetVitesse(int vit) {
    if (vit > 255)
        vitesse = 255;
    else
        vitesse=vit;
}

void Moteurs::stop_motors() {
    gpioPWM(pinAvantD, 0);
    gpioPWM(pinArriereD, 0);
    gpioPWM(pinArriereG, 0);
    gpioPWM(pinAvantG, 0);
}

void Moteurs::shut_down_motors() {
    stop_motors();
    gpioWrite(pinEEP, 0);
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

void Moteurs::rotation_avant(int vitG, int vitD) {
    gpioPWM(pinAvantD, vitD);
    gpioPWM(pinAvantG, vitG);
}

void Moteurs::controle_moteurs(TCPServer &server, std::mutex &server_mtx) {

    char direction, direction_prec;
    direction_prec = 'X';
    while (true) {
        // Scope du mutex
        {
            std::unique_lock<std::mutex> lock_server(server_mtx);
            //std::cout << "Debug get vitesse : " << server.getVitesse() << std::endl;
            //SetVitesse( server.getVitesse() );
            direction = server.getDirection()[0];
            server.setDirection("!");
            //std::cout << "Debug get direction : " << (server.getDirection())[0] << std::endl;
        }

        switch(direction)
            {
            case 'Z' :
                if(direction_prec == 'Z')
                {
                    std::cout << "Marche avant accelere " << std::endl;
                    SetVitesse(vitesse + 50);
                    marche_avant();
                }
                else
                {
                    std::cout << "Marche avant " << std::endl;
                    SetVitesse(105);
                    marche_avant();
                }
                break;

            case 'S' :
                if(direction_prec == 'S')
                {
                    std::cout << "Marche arriere accelere" << std::endl;
                    SetVitesse(vitesse + 50);
                    marche_arriere();
                }
                else
                {
                    std::cout << "Marche arriere " << std::endl;
                    SetVitesse(105);
                    marche_arriere();
                }
                break;

            case 'Q' :
                if(direction_prec == 'Z')
                {
                    std::cout << "Aller à gauche " << std::endl;
                    rotation_avant(vitesse, vitesse - 50);
                }
                else
                {
                    std::cout << "Aller à gauche " << std::endl;
                    aller_gauche();
                }
                break;

            case 'D' :
                std::cout << "Aller à droite " << std::endl;
                aller_droite();
                break;

            case 'X' :
                std::cout << "STOP !" << std::endl;
                stop_motors();
                SetVitesse(0);
                break;
            }
        if(direction != '!')
        { 
            direction_prec = direction;
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
        }
}
