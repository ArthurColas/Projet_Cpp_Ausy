#ifndef MOTEUR_H
#define MOTEUR_H

#include <mutex>

class Moteurs {
public:
    // Constructors
    Moteurs();
    Moteurs(int pinAvantD=27, int pinArriereD=18, int pinArriereG = 12, int pinAvantG = 17, int pinEEP = 22);  // Parameterized constructor
    //Moteur(const Moteur& other);      // Copy constructor

    // Destructor
    ~Moteurs();

    // Member functions
    void init_gpio_moteurs();
    void stop_motors();
    void shut_down_motors();
    void marche_avant();
    void marche_arriere();
    void aller_gauche();
    void aller_droite();
    void rotation_avant(int vitG, int vitD);

    int GetVitesse() { return vitesse;}
    void SetVitesse(int vit);
    void controle_moteurs(TCPServer &server, std::mutex &server_mtx);

private:
    // Private data members (class attributes)
    int pinAvantG;
    int pinArriereG;
    int pinAvantD;
    int pinArriereD;
    int pinEEP;
    int vitesse;
    const int MAX_RANGE_PWM = 255; // Plage maximale pour la PWM

};

#endif

