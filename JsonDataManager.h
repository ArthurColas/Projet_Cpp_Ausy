#ifndef JSONDATAMANAGER_H_INCLUDED
#define JSONDATAMANAGER_H_INCLUDED

#include<iostream>

#include <jsoncpp/json/json.h>

using namespace std;

/*enum Direction  // obsolete
{
    HAUT,
    BAS,
    GAUCHE,
    DROITE 
};*/

class JsonDataManager
{

 private :
     string _direction;
     int _vitesse;

 public :
    JsonDataManager(string _direction, int vitesse);
    JsonDataManager(string);
    ~JsonDataManager();

    int GetVitesse();
    //enum Direction GetDirection(){return _direction;}
    string GetDirection();

    void SetVitesse(int val){_vitesse = val;}
    void SetDirection(string val){_direction = val;}

    void ParseJson(string);

    void Afficher();
    string GetJson();
};

#endif // JSONDATAMANAGER_H_INCLUDED
