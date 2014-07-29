#pragma once

#include <allegro5\allegro5.h>
#include <allegro5\allegro_primitives.h>
#include "globals.h"

class GameObject
{
private:
	int ID;
	bool alive;
	bool collidable;

protected:
	float x;
	float y;

	int boundX;
	int boundY;

	int maxFrame;
	int curFrame;
	int frameCount;
	int frameDelay;
	int frameWidth;
	int frameHeight;
	int animationColumns;

	ALLEGRO_BITMAP *image;

public:
	GameObject();

	void Init(float x, float y, int boundX, int boundY);

	void virtual Render();
	void virtual Destroy();
	void virtual Update();

	float GetX() {return x;}
	float GetY() {return y;}

	void SetX(float x) {GameObject::x = x;}
	void SetY(float y) {GameObject::y = y;}

	int GetID() {return ID;}
	void SetID(int ID) {GameObject::ID = ID;}

	bool GetAlive() {return alive;}
	void SetAlive(bool alive) {GameObject::alive = alive;}

	bool GetCollidable() {return collidable;}
	void SetCollidable(bool collidable) {GameObject::collidable = collidable;}

	int GetBoundX() {return boundX;}
	int GetBoundY() {return boundY;}

	bool CheckCollisions(GameObject *otherObject);
	void virtual Collided(int objectID);
	bool Collidable();
};