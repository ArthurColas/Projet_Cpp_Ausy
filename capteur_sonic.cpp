#include "capteur_sonic.h"
#include <iostream>
#include <pigpio.h>

const int TRIG_PIN = 26;

const int ECHO_PIN_1 = 20;
const int ECHO_PIN_2 = 16;
const int ECHO_PIN_3 = 21;

capteur_sonic::capteur_sonic() {
    if(gpioInitialise() < 0)
        {
                std::cout << "Erreur lors de l'initialisation de pigpio." << std::endl;
        }

        gpioSetMode(TRIG_PIN, PI_OUTPUT);
        gpioSetMode(ECHO_PIN_1, PI_INPUT);
        gpioSetMode(ECHO_PIN_2, PI_INPUT);
        gpioSetMode(ECHO_PIN_3, PI_INPUT);
}

double capteur_sonic::MeasureDist(int capteurNum)
{
    const int HIGH = 1;

    gpioTrigger(TRIG_PIN, 10, HIGH); //impulsion de mesure 10 µs

    int echo = gpioRead(capteurNum);
    unsigned startTime = gpioTick();

    while (echo == 0)
    {
            if(gpioTick() - startTime > 10000)
            {
                    return -1.0; //si pas de  reponse capteur, distance non valide
            }
            echo = gpioRead(capteurNum);
    }

    unsigned startTick = gpioTick();

    while (echo == 1)
    {
            echo = gpioRead(capteurNum);
    }

    unsigned endTick = gpioTick();

    double soundSpeed = 343.0; //vitesse du son en m/s dans l'air a 20°C
    double pulseDuration = (endTick - startTick) / 1000000.0; //duree impuksion en s
    double distance = (pulseDuration / 2.0) * soundSpeed;

    return distance;
}
