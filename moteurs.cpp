#include <iostream>
#include <pigpio.h>
#include <unistd.h>
#include <iomanip>

#include "moteurs.h"

Moteurs::Moteurs(int avD , int arD, int arG, int avG, int eep) {
    pinAvantD=avD;
    pinArriereD=arD;
    pinArriereG=arG;
    pinAvantG=avG;
    pinEEP=eep;
    init_gpio_moteurs();
}

Moteurs::Moteurs(){
    init_gpio_moteurs();
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
}

void Moteurs::stop_motors() {
    gpioPWM(pinAvantD, 0);
    gpioPWM(pinArriereD, 0);
    gpioPWM(pinArriereG, 0);
    gpioPWM(pinAvantG, 0);
}

void Moteurs::marche_avant(int speed) {
    stop_motors();
    gpioPWM(pinAvantD, speed);
    gpioPWM(pinAvantG, speed);
}

void Moteurs::marche_arriere(int speed) {
    stop_motors();
    gpioPWM(pinAvantD, speed);
    gpioPWM(pinArriereG, speed);
}

void Moteurs::aller_droite(int speed) {
    stop_motors();
    gpioPWM(pinAvantD, speed);
    gpioPWM(pinAvantG, speed);
}

void Moteurs::aller_gauche(int speed) {
    stop_motors();
    gpioPWM(pinAvantD, speed);
    gpioPWM(pinArriereG, speed);
}

void Moteurs::rotation(int speed) {
    stop_motors();
    gpioPWM(pinAvantD, speed);
    gpioPWM(pinArriereG, speed);
    sleep(1);
    gpioPWM(pinArriereD, speed);
    gpioPWM(pinAvantG, speed);
}

