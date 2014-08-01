#pragma once

#include "mobile_object.h"

class Ghost : public MobileObject
{
protected:
	int animationRows;
public:
	Ghost();

	void Init(float x, float y, int boundX, int boundY, float velocity, ALLEGRO_BITMAP *image);

	void Destroy(){};
	void Update(int map[][21]);
	void Render();

	void Collided(int ObjectID){};
}; 