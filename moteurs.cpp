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

