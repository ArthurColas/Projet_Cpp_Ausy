#ifndef JSONDATAMANAGER_H_INCLUDED
#define JSONDATAMANAGER_H_INCLUDED

#include<iostream>

#include <jsoncpp/json/json.h>

using namespace std;

enum Direction
{
    HAUT,
    BAS,
    GAUCHE,
    DROITE
};

class JsonDataManager
{

 private :
     enum Direction _direction;
     float _abscisse;
     float _ordonnee;

 public :
    JsonDataManager(enum Direction, float, float);
    JsonDataManager(string);
    ~JsonDataManager();

    float GetAbscisse(){return _abscisse;}
    float GetOrdonne(){return _ordonnee;}
    //enum Direction GetDirection(){return _direction;}
    string GetDirection();

    void SetAbscisse(float val){_abscisse = val;}
    void SetOrdonnee(float val){_ordonnee = val;}
    void SetDirection(enum Direction val){_direction = val;}

    void ParseJson(string);

    void Afficher();
    string GetJson();
};

#endif // JSONDATAMANAGER_H_INCLUDED
