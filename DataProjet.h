#ifndef DATAPROJET_H_INCLUDED
#define DATAPROJET_H_INCLUDED

#include<iostream>

using namespace std;

enum Direction
{
    HAUT,
    BAS,
    GAUCHE,
    DROITE
};

class DataProjet
{

 private :
     enum Direction _direction;
     float _abscisse;
     float _ordonnee;
     void ParseJson(string);

 public :
    DataProjet(enum Direction, float, float);
    DataProjet(string);
    ~DataProjet();

    float GetAbscisse(){return _abscisse;}
    float GetOrdonne(){return _ordonnee;}
    //enum Direction GetDirection(){return _direction;}
    string GetDirection();

    void SetAbscisse(float val){_abscisse = val;}
    void SetOrdonnee(float val){_ordonnee = val;}
    void SetDirection(enum Direction val){_direction = val;}

    void Afficher();
    string GetJson();
};

#endif // DATAPROJET_H_INCLUDED
