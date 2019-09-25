#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace sf;
using namespace std;

const int W = 1350;
const int H = 700;

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

		RectangleShape rectangle;
		rectangle.setSize(sf::Vector2f(R, R));
		rectangle.setFillColor(Color(255, 0, 0, 170));
		rectangle.setOrigin(R, R);
		rectangle.setPosition(x, y);
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

		dx = 0;
		dy = 0;
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