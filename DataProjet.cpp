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
    // g�n�rer classe a partir du json
    //utiliser methode priv�e ParseJson
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
    case BAS : direction = "bas";
        break;
    case HAUT : direction = "haut";
        break;
    case GAUCHE : direction = "gauche";
        break;
    case DROITE : direction = "droite";
        break;
    }

    cout << "Direction : " << direction << ", Abscisse : " << _abscisse << ", Ordonnee : "<< _ordonnee << endl;
}

