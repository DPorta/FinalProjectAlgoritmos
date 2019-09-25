#pragma once
#include "Cargar.h"

void autosave(list<Entity*> entities, bool colflag0, bool colflag1, bool colflag2) {


	if (colflag0 == true && colflag1 == false && colflag2 == false) {
		ofstream outfile0("autosave0.txt");
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
			case 0:  outfile0 << 0 << "," << e->x << "," << e->y << "," << e->angle << "," << e->R << "," << e->dx << "," << e->dy << "," << e->life << endl;
				break;

			case 1:  outfile0 << 1 << "," << e->x << "," << e->y << "," << e->angle << "," << e->R << "," << e->dx << "," << e->dy << "," << e->life << endl;
				break;

			case 2:  outfile0 << 2 << "," << e->x << "," << e->y << "," << e->angle << "," << e->R << "," << e->dx << "," << e->dy << "," << e->life << endl;
				break;

			case 3:  outfile0 << 3 << "," << e->x << "," << e->y << "," << e->angle << "," << e->R << "," << e->dx << "," << e->dy << "," << e->life << endl;
				break;

			default:
				break;
			}

		}
		outfile0.close();
	}

	if (colflag0 == true && colflag1 == true && colflag2 == false) {
		ofstream outfile1("autosave1.txt");
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
			case 0:  outfile1 << 0 << "," << e->x << "," << e->y << "," << e->angle << "," << e->R << "," << e->dx << "," << e->dy << "," << e->life << endl;
				break;

			case 1:  outfile1 << 1 << "," << e->x << "," << e->y << "," << e->angle << "," << e->R << "," << e->dx << "," << e->dy << "," << e->life << endl;
				break;

			case 2:  outfile1 << 2 << "," << e->x << "," << e->y << "," << e->angle << "," << e->R << "," << e->dx << "," << e->dy << "," << e->life << endl;
				break;

			case 3:  outfile1 << 3 << "," << e->x << "," << e->y << "," << e->angle << "," << e->R << "," << e->dx << "," << e->dy << "," << e->life << endl;
				break;

			default:
				break;
			}

		}
		outfile1.close();
	}


	if (colflag0 == true && colflag1 == true && colflag2 == true) {
		ofstream outfile2("autosave2.txt");
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
			case 0:  outfile2 << 0 << "," << e->x << "," << e->y << "," << e->angle << "," << e->R << "," << e->dx << "," << e->dy << "," << e->life << endl;
				break;

			case 1:  outfile2 << 1 << "," << e->x << "," << e->y << "," << e->angle << "," << e->R << "," << e->dx << "," << e->dy << "," << e->life << endl;
				break;

			case 2:  outfile2 << 2 << "," << e->x << "," << e->y << "," << e->angle << "," << e->R << "," << e->dx << "," << e->dy << "," << e->life << endl;
				break;

			case 3:  outfile2 << 3 << "," << e->x << "," << e->y << "," << e->angle << "," << e->R << "," << e->dx << "," << e->dy << "," << e->life << endl;
				break;

			default:
				break;
			}

		}
		outfile2.close();
	}

}