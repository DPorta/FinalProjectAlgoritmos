#include <SFML/Graphics.hpp>

#include "pch.h"
#include <time.h>
#include <list>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <functional>
#include "MyStack.h"
#include <windows.h>
#include <algorithm>



using namespace sf;
using namespace std;

const int W = 1350;
const int H = 700;



float DEGTORAD = 0.017453f;

class Animation
{
public:
	float Frame, speed;
	Sprite sprite;
	std::vector<IntRect> frames;

	Animation() {}

	Animation(Texture &t, int x, int y, int w, int h, int count, float Speed)
	{
		Frame = 0;
		speed = Speed;

		for (int i = 0; i < count; i++)
			frames.push_back(IntRect(x + i * w, y, w, h));

		sprite.setTexture(t);
		sprite.setOrigin(w / 2, h / 2);
		sprite.setTextureRect(frames[0]);
	}

	

	void update()
	{
		Frame += speed;
		int n = frames.size();
		if (Frame >= n) Frame -= n;
		if (n > 0) sprite.setTextureRect(frames[int(Frame)]);
	}

	bool isEnd()
	{
		return Frame + speed >= frames.size();
	}

};


////////////
class Entity
{
public:
	float x, y, dx, dy, R, angle;
	bool life;
	std::string name;
	Animation anim;


	Entity() { life = 1; }

	void settings(Animation &a, float X, float Y, float Angle = 0, float radius = 1)
	{
		anim = a;
		this->x = X; 
		this->y = Y;
		this->angle = Angle;
		R = radius;
	}

	

	virtual void update() {};

	void draw(RenderWindow &app)
	{
		anim.sprite.setPosition(x, y);
		anim.sprite.setRotation(0);
		app.draw(anim.sprite);

		CircleShape circle(R);
		circle.setFillColor(Color(255, 0, 0, 170));
		
		circle.setOrigin(R, R);
		circle.setPosition(x, y);
	}	
	
	virtual ~Entity() {};
};

class Caja : public Entity
{
public:
	Caja()
	{
		dx = 0;
		dy = 0;
		name = "caja";
	}

	void  update()
	{
		x += dx;
		y += dy;

		dx=0;
		dy=0;
	}
	
};

class player : public Entity
{
public:
	
	player() { name = "player"; }

	void update()
	{
		

		x += dx;
		y += dy;

		dx = 0;
		dx = 0;
		dy = 0;
		dy = 0;


		if (x > W) x = W; 
		if (x < 0) x = 0;
		if (y > H) y = H; 
		if (y < 0) y = 0;

	

		if (Keyboard::isKeyPressed(Keyboard::Right)) dx = 3;
		if (Keyboard::isKeyPressed(Keyboard::Left))  dx = -3;
		if (Keyboard::isKeyPressed(Keyboard::Down))  dy = 3;
		if (Keyboard::isKeyPressed(Keyboard::Up))    dy = -3;
		
	}

};

class Muro : public Entity
{
public:
	Muro()
	{
		name = "muro";
	}

	void  update()
	{

	}

};


///////////
bool isCollide(Entity *a, Entity *b)
{
	return (b->x - a->x)*(b->x - a->x) +
		(b->y - a->y)*(b->y - a->y) <
		(a->R + b->R)*(a->R + b->R);
}

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
				entities.push_back(a);}
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
	string ori("nada");

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
	//CAJA
	
		Caja *f = new Caja();
		f->settings(sCaja, 640, 295, 0, 20);
		entities.push_back(f);

		Caja *g = new Caja();
		g->settings(sCaja,700, 295, 0, 20);
		entities.push_back(g);

		Caja *h = new Caja();
		h->settings(sCaja, 580, 295, 0, 20);
		entities.push_back(h);

		Caja *i = new Caja();
		i->settings(sCaja, 580, 350, 0, 20);
		entities.push_back(i);

		Caja *j = new Caja();
		j->settings(sCaja, 520,410, 0, 20);
		entities.push_back(j);
	
	//MURO
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 36; j++)
		{
		Muro *a = new Muro();
		a->settings(sMuro, j*40, i*39, 0, 20);
		entities.push_back(a);	

		}
	}
	for (int i = 5; i < 9; i++)
	{
		for (int j = 0; j < 14; j++)
		{
			Muro *a = new Muro();
			a->settings(sMuro, j * 40, i * 39, 0, 20);
			entities.push_back(a);

		}
	}
	for (int i = 5; i < 10; i++)
	{
		for (int j = 20; j < 36; j++)
		{
			Muro *a = new Muro();
			a->settings(sMuro, j * 40, i * 39, 0, 20);
			entities.push_back(a);

		}
	}
	for (int i = 9; i < 19; i++)
	{
		for (int j = 19; j < 36; j++)
		{
			Muro *a = new Muro();
			a->settings(sMuro, j * 40, i * 39, 0, 20);
			entities.push_back(a);

		}
	}
	for (int i = 9; i < 12; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			Muro *a = new Muro();
			a->settings(sMuro, j * 40, i * 39, 0, 20);
			entities.push_back(a);

		}
	}
	for (int i = 12; i < 19; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			Muro *a = new Muro();
			a->settings(sMuro, j * 40, i * 39, 0, 20);
			entities.push_back(a);

		}
	}
	for (int i = 15; i < 19; i++)
	{
		for (int j = 15; j < 20; j++)
		{
			Muro *a = new Muro();
			a->settings(sMuro, j * 40, i * 39, 0, 20);
			entities.push_back(a);

		}
	}
	

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

	

	//Personaje
	player *p = new player();
	p->settings(sPlayer_right, 420, 400, 0, 25);
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

                        if (a->dy != 0 && a->dx != 0)
                        {
                        	b->dy = 0;
                        	b->dx = 0;
                        	a->dy = 0;
                        	a->dx = 0;
                        }

                        if (a->dx > 0 && a->x - 40 < b->x)
                        	b->dx = a->dx;
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