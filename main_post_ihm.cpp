#include "post_ihm.h"

int main() {

	int temperature=10;
        int pression=20;
        int batterie=30;
        int gauche=40;
        int droite=50;
        int avant=60;

	post_ihm client=post_ihm();
	client.send(temperature, pression, batterie, gauche, droite, avant);

	return 0;
}

