#ifndef MOTEUR_H
#define MOTEUR_H

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
    void marche_avant(int speed);
    void marche_arriere(int speed);
    void aller_gauche(int speed);
    void aller_droite(int speed);
    void rotation(int speed);

private:
    // Private data members (class attributes)
    int pinAvantG;
    int pinArriereG;
    int pinAvantD;
    int pinArriereD;
    int pinEEP;

    const int MAX_RANGE_PWM = 255; // Plage maximale pour la PWM

};

#endif
