#pragma once
#include "Guardar.h"

vector<string> split(string str) {
	istringstream iss(str);
	string cad;
	vector<string> arr;
	while (getline(iss, cad, ',')) {
		arr.push_back(cad);
	}
	return arr;
}

vector<float> convert(vector<string> arr) {

	vector<float> nums(arr.size());
	for (int i = 0; i < arr.size(); i++) {
		nums[i] = atof(arr[i].c_str());
	}
	return nums;
}

void userload(list<Entity*> &entities, Texture &t1, Texture &t2, Texture &t3, Texture &t4, Texture &t5, Sprite &background, Animation &sMeta, Animation &sCaja, Animation &sMuro, Animation &sPlayer)
{


	ifstream infile("usersave.txt");
	string str;
	entities.clear();


	while (getline(infile, str)) {
		auto pstr = split(str);
		auto nums = convert(pstr);

		int entype(4);
		if (nums[0] == 0.0) {
			entype = 0;
		}

		if (nums[0] == 1.0) {
			entype = 1;
		}

		if (nums[0] == 2.0) {
			entype = 2;
		}

		if (nums[0] == 3.0) {
			entype = 3;
		}

		switch (entype) {
		case 0: { player *p = new player();
			p->settings(sPlayer, nums[1], nums[2], nums[3], nums[4]);
			p->dx = nums[5];
			p->dy = nums[6];
			p->life = (bool)nums[7];
			entities.push_back(p); }
				break;

		case 1: { Caja *a = new Caja();

			a->settings(sCaja, nums[1], nums[2], nums[3], nums[4]);
			a->dx = nums[5];
			a->dy = nums[6];
			a->life = (bool)nums[7];
			entities.push_back(a); }
				break;

		case 2: {Muro *b = new Muro();
			b->settings(sMuro, nums[1], nums[2], nums[3], nums[4]);
			b->dx = nums[5];
			b->dy = nums[6];
			b->life = (bool)nums[7];
			entities.push_back(b); }
				break;

		case 3: {Entity *e = new Entity();
			e->settings(sMeta, nums[1], nums[2]);
			e->name = "meta";
			entities.push_back(e); }
				break;

		default:
			break;
		}

		nums.clear();

	}

}