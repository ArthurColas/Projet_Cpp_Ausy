#include <iostream>
#include "DataProjet.h"
#include "json.h"

DataProjet::DataProjet(enum Direction direction, float abs, float ord)
{
    _direction = direction;
    _abscisse = abs;
    _ordonnee = ord;
}

DataProjet::DataProjet(string rawJson)
{
    // générer classe a partir du json
    //utiliser methode privée ParseJson
    Json::Value root;
    Json::Reader reader;
    reader.parse(rawJson, root);

    _abscisse = root["abscisse"].asFloat();
    _ordonnee = root["ordonnee"].asFloat();
    string direction = root["direction"].asString();

    if(direction == "haut")
    {
        _direction = HAUT;
    }

    if(direction == "bas")
    {
        _direction = BAS;
    }

    if(direction == "droite")
    {
        _direction = DROITE;
    }

    if(direction == "gauche")
    {
        _direction = GAUCHE;
    }
}

DataProjet::~DataProjet()
{

}

string DataProjet::GetDirection()
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

    return direction;
}

string DataProjet::GetJson()
{
    Json::Value m_data;
    m_data["direction"] = GetDirection();
    m_data["abscisse"] = _abscisse;
    m_data["ordonnee"] = _ordonnee;

    Json::StreamWriterBuilder writer;
    string jsonString = Json::writeString(writer, m_data);

    cout << "json genere"  << endl;
    cout << jsonString << endl;

    return jsonString;
}

void DataProjet::Afficher()
{


    cout << "Direction : " << GetDirection() << ", Abscisse : " << _abscisse << ", Ordonnee : "<< _ordonnee << endl;
}

