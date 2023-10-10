#include <iostream>
#include "DataProjet.h"

using namespace std;

int main()
{
    enum Direction direction = HAUT;
    DataProjet data1{direction, 1.0f, -1.0f};

    data1.Afficher();
    data1.GetJson();
}
