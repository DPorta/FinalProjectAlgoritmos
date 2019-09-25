#include <SFML/Graphics.hpp>
#include "autosave.h"
#include "pch.h"
#include "MyStack.h"
#include <time.h>

#include <functional>
#include <windows.h>
#include <algorithm>

///////////
void gottagobackload(MyStack<string> autosaves, list<Entity*> &entities, Texture &t1, Texture &t2, Texture &t3, Texture &t4, Texture &t5, Sprite &background, Animation &sMeta, Animation &sCaja, Animation &sMuro, Animation &sPlayer)
{
	ifstream infile(autosaves.top());
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

int main()
{
	srand(time(0));

	int nivel(1);
	bool flag1(false), flag2(false), flag3(false), flag4(false), flag5(false);
	bool colflag0(false), colflag1(false), colflag2(false);
	int asavecont(0);
	string ori("nada");
	MyStack<string> autosaves;

	RenderWindow app(VideoMode(W, H), "Sokoban");
	app.setFramerateLimit(60);

	Texture t1, t2, t3, t4, t5;
	t1.loadFromFile("images/GrueBloodyGrin.png");
	t2.loadFromFile("images/BackgroundRock.jpg");
	t3.loadFromFile("images/meta.png");
	t4.loadFromFile("images/caja.png");
	t5.loadFromFile("images/muroh.png");


	t1.setSmooth(true);
	t2.setSmooth(true);

	Sprite background(t2);

	Animation sMeta(t3, 0, 0, 55, 55, 1, 0);
	Animation sCaja(t4, 0, 0, 40, 40, 1, 0);
	Animation sMuro(t5, 0, 0, 40, 40, 1, 0);
	Animation sPlayer_right(t1, 0, 0, 56, 71, 1, 0);
	Animation sPlayer_up(t1, 56, 0, 56, 71, 1, 0);
	Animation sPlayer_left(t1, 0, 71, 56, 71, 1, 0);
	Animation sPlayer_down(t1, 56, 71, 56, 71, 1, 0);
	   

	list<Entity*> entities;


	//META

	Entity *a = new Entity();
	a->settings(sMeta, 640, 350, 0, 20);
	a->name = "meta";
	entities.push_back(a);

	Entity *b = new Entity();
	b->settings(sMeta, 700, 350, 0, 20);
	b->name = "meta";
	entities.push_back(b);

	Entity *c = new Entity();
	c->settings(sMeta, 580, 410, 0, 20);
	c->name = "meta";
	entities.push_back(c);

	Entity *d = new Entity();
	d->settings(sMeta, 640, 410, 0, 20);
	d->name = "meta";
	entities.push_back(d);

	Entity *e = new Entity();
	e->settings(sMeta, 700, 410, 0, 20);
	e->name = "meta";
	entities.push_back(e);

	//CAJA

	Caja *f = new Caja();
	f->settings(sCaja, 640, 295, 0, 20);
	entities.push_back(f);

	Caja *g = new Caja();
	g->settings(sCaja, 700, 295, 0, 20);
	entities.push_back(g);

	Caja *h = new Caja();
	h->settings(sCaja, 580, 295, 0, 20);
	entities.push_back(h);

	Caja *i = new Caja();
	i->settings(sCaja, 580, 350, 0, 20);
	entities.push_back(i);

	Caja *j = new Caja();
	j->settings(sCaja, 520, 410, 0, 20);
	entities.push_back(j);

	//MURO


	for (int j = 9; j < 21; j++)
	{
		Muro *a = new Muro();
		a->settings(sMuro, j * 40, 5 * 39, 0, 20);
		entities.push_back(a);

	}

	for (int i = 6; i < 9; i++)
	{
		for (int j = 9; j < 14; j++)
		{
			Muro *a = new Muro();
			a->settings(sMuro, j * 40, i * 39, 0, 20);
			entities.push_back(a);

		}
	}
	for (int i = 6; i < 10; i++)
	{
		Muro *a = new Muro();
		a->settings(sMuro, 20 * 40, i * 39, 0, 20);
		entities.push_back(a);
	}
	for (int i = 10; i < 16; i++)
	{
		for (int j = 19; j < 21; j++)
		{
			Muro *a = new Muro();
			a->settings(sMuro, j * 40, i * 39, 0, 20);
			entities.push_back(a);

		}
	}
	for (int i = 9; i < 12; i++)
	{
		Muro *a = new Muro();
		a->settings(sMuro, 9 * 40, i * 39, 0, 20);
		entities.push_back(a);
	}

	for (int i = 12; i < 16; i++)
	{
		for (int j = 9; j < 15; j++)
		{
			Muro *a = new Muro();
			a->settings(sMuro, j * 40, i * 39, 0, 20);
			entities.push_back(a);

		}
	}

	for (int j = 15; j < 20; j++)
	{
		Muro *a = new Muro();
		a->settings(sMuro, j * 40, 15 * 39, 0, 20);
		entities.push_back(a);

	}

	//Personaje

	player *p = new player();
	p->settings(sPlayer_right, 420, 400, 90.0, 25);
	entities.push_back(p);

	///// bucle principal /////
	while (app.isOpen())
	{

		Event event;
		while (app.pollEvent(event))
		{
			if (event.type == Event::Closed)
				app.close();
		}


		/////Guardar Partida Usuario/////
		if (Keyboard::isKeyPressed(Keyboard::S)) usersave(entities);

		/////Cargar Partida Usuario/////
		if (Keyboard::isKeyPressed(Keyboard::L)) userload(entities, t1, t2, t3, t4, t5, background, sMeta, sCaja, sMuro, sPlayer_right);

		/////Retroceder un paso/colision/////
		if (Keyboard::isKeyPressed(Keyboard::R)) gottagobackload(autosaves, entities, t1, t2, t3, t4, t5, background, sMeta, sCaja, sMuro, sPlayer_right);


		for (auto a : entities)
			for (auto b : entities)
			{
				if (a->name == "caja" && b->name == "muro")
					if (isCollide(a, b))
					{
						a->dx = 0;
						a->dy = 0;
						b->dx = 0;
						b->dy = 0;

					}

				if (a->name == "player" && b->name == "caja")
					if (isCollide(a, b))
					{
						asavecont++;
						if (asavecont == 1) {
							colflag0 = true;
							autosave(entities, colflag0, colflag1, colflag2);
							autosaves.push("autosave2.txt");   //nombres en orden inverso a los correspondientes a la logica de autosave con el proposito de invertir el orden de la pila sin usar mas de una pila
						}
						if (asavecont == 2) {
							colflag1 = true;
							autosave(entities, colflag0, colflag1, colflag2);
							autosaves.push("autosave1.txt");
						}
						if (asavecont == 3) {
							colflag2 = true;
							autosave(entities, colflag0, colflag1, colflag2);
							autosaves.push("autosave0.txt");
						}
						if (asavecont > 3) {
							asavecont = 0;
							autosaves.pop();
							colflag0 = false;
							colflag1 = false;
							colflag2 = false;
						}

						if (a->dy != 0 && a->dx != 0)
						{
							b->dy = 0;
							b->dx = 0;
							a->dy = 0;
							a->dx = 0;
						}

						if (a->dx > 0 && a->x - 40 < b->x)
							b->dx = a->dx; //dx+algo para que la caja salga proyectada un poco y ya no este constantemente contando colision 
						if (a->dx < 0 && a->x + 40 > b->x)
							b->dx = a->dx;
						if (a->dy > 0 && a->y + 40 < b->y)
							b->dy = a->dy;
						if (a->dy < 0 && a->y - 40 > b->y)
							b->dy = a->dy;

						if ((ori == "left" || ori == "right" || ori == "up") && b->dx == 0 && b->dy == 0) {
							if (a->y > b->y + 15)
								a->y += 20;
						}

						if ((ori == "left" || ori == "right" || ori == "down") && b->dx == 0 && b->dy == 0) {
							if (a->y < b->y - 15)
								a->y -= 20;
						}


					}

				if ((a->name == "player" && b->name == "muro") || (a->name == "caja" && b->name == "muro"))
					if (isCollide(a, b)) {

						if (a->y < b->y) {
							a->y = a->y - 15;
						}

						if (a->y > b->y) {
							a->y = a->y + 15;
						}

						if (a->x > b->x) {
							a->x = a->x + 15;
						}

						if (a->x < b->x) {
							a->x = a->x - 15;
						}

					}

				if ((a->name == "caja" && b->name == "meta"))
					if (isCollide(a, b)) {

						if (flag1 == false && flag2 == false && flag3 == false && flag4 == false && flag5 == false) {
							flag1 == true;
						}

						if (flag1 == true && flag2 == false && flag3 == false && flag4 == false && flag5 == false) {
							flag2 == true;
						}

						if (flag1 == true && flag2 == true && flag3 == false && flag4 == false && flag5 == false) {
							flag3 == true;
						}

						if (flag1 == true && flag2 == true && flag3 == true && flag4 == false && flag5 == false) {
							flag4 == true;
						}

						if (flag1 == true && flag2 == true && flag3 == true && flag4 == true && flag5 == false) {
							flag5 == true;
							cout << "Ganaste"; //reemplazar esto por un evento/animacion que indique la victoria
						}


					}

			}

		for (auto e : entities) {
			if (e->name == "player" && Keyboard::isKeyPressed(Keyboard::Up)) {
				e->anim = sPlayer_up; ori = "up";
			}
			if (e->name == "player" && Keyboard::isKeyPressed(Keyboard::Right)) {
				e->anim = sPlayer_right; ori = "right";
			}
			if (e->name == "player" && Keyboard::isKeyPressed(Keyboard::Left)) {
				e->anim = sPlayer_left; ori = "left";
			}
			if (e->name == "player" && Keyboard::isKeyPressed(Keyboard::Down)) {
				e->anim = sPlayer_down; ori = "down";
			}
		}

		for (auto i = entities.begin(); i != entities.end();)
		{
			Entity *e = *i;

			e->update();
			e->anim.update();

			if (e->life == false) { i = entities.erase(i); delete e; }
			else i++;
		}


		//////Draw//////

		app.draw(background);

		for (auto i : entities)
			i->draw(app);

		app.display();

	}

	return 0;

}