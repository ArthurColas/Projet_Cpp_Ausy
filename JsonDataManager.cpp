#include <iostream>
#include "JsonDataManager.h"

JsonDataManager::JsonDataManager(string direction, int vitesse)
{
    _direction = direction;
    _vitesse = vitesse;
}

JsonDataManager::JsonDataManager(string rawJson)
{
    ParseJson(rawJson);
}

JsonDataManager::~JsonDataManager()
{

}

int JsonDataManager::GetVitesse() { return _vitesse; }

string JsonDataManager::GetDirection()
{
    return _direction;
/*    string direction = "";

    switch(_direction)
    {
    case BAS : direction = "S";
        break;
    case HAUT : direction = "Z";
        break;
    case GAUCHE : direction = "Q";
        break;
    case DROITE : direction = "D";
        break;
    }

    return direction; */
}

string JsonDataManager::GetJson()
{
    Json::Value m_data;
    m_data["direction"] = GetDirection();
    m_data["vitesse"] = GetVitesse();

    Json::StreamWriterBuilder writer;
    string jsonString = Json::writeString(writer, m_data);

    cout << "json genere"  << endl;
    cout << jsonString << endl;

    return jsonString;
}

void JsonDataManager::ParseJson(string rawJson)
{
    Json::Value root;
    Json::Reader reader;
    reader.parse(rawJson, root);

    _vitesse = root["vitesse"].asInt();
    string _direction = root["direction"].asString();
}

void JsonDataManager::Afficher()
{


    cout << "Direction : " << GetDirection() << ", Vitesse : " << GetVitesse() << endl;
}

