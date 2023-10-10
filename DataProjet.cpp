#include <iostream>
#include "DataProjet.h"

DataProjet::DataProjet(enum Direction direction, float abs, float ord)
{
    _direction = direction;
    _abscisse = abs;
    _ordonnee = ord;
}

DataProjet::DataProjet(string)
{
    // générer classe a partir du json
    //utiliser methode privée ParseJson
}

void DataProjet::ParseJson(string)
{

}

DataProjet::~DataProjet()
{

}

string DataProjet::GetJson()
{
    return "";
}

void DataProjet::Afficher()
{
    string direction = "";

    switch(_direction)
    {
    case Direction.BAS : direction = "bas";
        break;
    case Direction.HAUT : direction = "haut";
        break;
    case Direction.GAUCHE : direction = "gauche";
        break;
    case Direction.DROITE : direction = "droite";
        break;
    }

    cout << "Direction : " << direction << ", Abscisse : " << _abscisse << ", Ordonnee : "<< _ordonnee << endl;
}

