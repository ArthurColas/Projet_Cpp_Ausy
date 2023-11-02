#include <iostream>
#include <pigpio.h>
#include <unistd.h>
#include <iomanip>
#include "conio.h"

#define COMMAND_DELAY 500000

// Définition des pins
const int IN1 = 27; // moteur droit sens avant
const int IN2 = 18; // moteur droit sens arriere
const int IN3 = 12; // moteur gauche sens arriere
const int IN4 = 17; // moteur gauche sens avant
const int EEP_PIN = 22; // nSLEEP ou EEP

const int MAX_RANGE_PWM = 255; // Plage maximale pour la PWM

void init_gpio_moteur() {
    gpioInitialise();
    gpioSetMode(IN1, PI_OUTPUT);
    gpioSetMode(IN2, PI_OUTPUT);
    gpioSetMode(IN3, PI_OUTPUT);
    gpioSetMode(IN4, PI_OUTPUT);
    gpioSetMode(EEP_PIN, PI_OUTPUT);

    // Activer la carte DRV8833
    gpioWrite(EEP_PIN, 1);
}

void stop_motors() {
    gpioPWM(IN1, 0);
    gpioPWM(IN2, 0);
    gpioPWM(IN3, 0);
    gpioPWM(IN4, 0);
}

void marche_avant(int speed) {
    stop_motors();
    gpioPWM(IN1, speed);
    gpioPWM(IN4, speed);
}

void marche_arriere(int speed) {
    stop_motors();
    gpioPWM(IN2, speed);
    gpioPWM(IN3, speed);
}

void aller_droite(int speed) {
    stop_motors();
    gpioPWM(IN1, speed);
    gpioPWM(IN3, speed);
}

void aller_gauche(int speed) {
    stop_motors();
    gpioPWM(IN2, speed);
    gpioPWM(IN4, speed);
}

void rotation(int speed) {
    stop_motors();
    gpioPWM(IN1, speed);
    gpioPWM(IN3, speed);
    sleep(1);
    gpioPWM(IN2, speed);
    gpioPWM(IN4, speed);
}

int main() {
    init_gpio_moteur();

    std::cout << "INIT OK" << std::endl << "Z Q S D pour piloter, X pour quitter" << std::endl;
    int saisie = -1;
    int vitesse = 200;
    if(vitesse > MAX_RANGE_PWM)
        {
            vitesse = MAX_RANGE_PWM;
        }
    while((saisie = getch()) != EOF && (saisie != 'x'))
    {
        //std::cout << "Aller à gauche à vitesse maximaleCommande : \"1\" = gauche, \"2\" = droite, \"3\" = avant, \"4\" = arriere" << std::endl;
        //std::cin >> saisie;
        /*
        std::cout << "Choisir la vitesse entre 1 et " << MAX_RANGE_PWM << std::endl;
        std::cin >> vitesse;
        if(vitesse > MAX_RANGE_PWM)
        {
            vitesse = MAX_RANGE_PWM;
        }
*/
        switch (saisie)
            {
                case 'z':
                    //std::cout << "Aller à gauche à vitesse " << std::setprecision(1) << (vitesse*100/MAX_RANGE_PWM) <<"%" << std::endl;
                    marche_avant(vitesse);
                    usleep(COMMAND_DELAY);
                    stop_motors();
                    break;
                case 'q':
                    //std::cout << "Aller à droite à vitesse " << std::setprecision(1) << (vitesse*100/MAX_RANGE_PWM) <<"%" << std::endl;
                    aller_gauche(vitesse);
                    usleep(COMMAND_DELAY);
                    stop_motors();
                    break;
                case 's':
                    //std::cout << "Marche avant à vitesse " << std::setprecision(1) << (vitesse*100/MAX_RANGE_PWM) <<"%" << std::endl;
                    marche_arriere(vitesse);
                    usleep(COMMAND_DELAY);
                    stop_motors();
                    break;
                case 'd':
                    //std::cout << "Marche arriere à vitesse " << std::setprecision(1) << (vitesse*100/MAX_RANGE_PWM) <<"%" << std::endl;
                    aller_droite(vitesse);
                    usleep(COMMAND_DELAY);
                    stop_motors();
                    break;
                case'+':
                    std::cout << "(+) Vitesse : " << (vitesse+20) << std::endl;
                    vitesse += 20;
                    break;
                case'-':
                    std::cout << "(-) Vitesse : " << (vitesse-20) << std::endl;
                    vitesse -= 20;
                    break;
            }
            if(vitesse > MAX_RANGE_PWM)
            {
            vitesse = MAX_RANGE_PWM;
            }
            else if(vitesse < 0)
            {
            vitesse = 0;
            }

    }
    std::cout << "Fin de programme" << std::endl;

    // Désactiver la carte DRV8833 après les tests
    gpioWrite(EEP_PIN, 0);

    gpioTerminate();
    return 0;
}

