#pragma once
#include "Colision.h"
#include <vector>

void usersave(list<Entity*> entities) {

	ofstream outfile("usersave.txt");

	for (auto i = entities.begin(); i != entities.end(); i++)
	{
		Entity *e = *i;
		int entype(4);

		if (e->name == "player") {
			entype = 0;
		}

		if (e->name == "caja") {
			entype = 1;
		}

		if (e->name == "muro") {
			entype = 2;
		}

		if (e->name == "meta") {
			entype = 3;
		}


		switch (entype) {
		case 0:  outfile << 0 << "," << e->x << "," << e->y << "," << e->angle << "," << e->R << "," << e->dx << "," << e->dy << "," << e->life << endl;
			break;

		case 1:  outfile << 1 << "," << e->x << "," << e->y << "," << e->angle << "," << e->R << "," << e->dx << "," << e->dy << "," << e->life << endl;
			break;

		case 2:  outfile << 2 << "," << e->x << "," << e->y << "," << e->angle << "," << e->R << "," << e->dx << "," << e->dy << "," << e->life << endl;
			break;

		case 3:  outfile << 3 << "," << e->x << "," << e->y << "," << e->angle << "," << e->R << "," << e->dx << "," << e->dy << "," << e->life << endl;
			break;

		default:
			break;
		}

	}
	outfile.close();

}
