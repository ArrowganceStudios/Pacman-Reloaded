#pragma once

#include "static_object.h"

class PowerUp : public StaticObject
{
public:
	PowerUp();
	void Init(float x, float y, int boundX, int boundY);

	void Collided(int ObjectID);

	void Destroy();
	void Render();

};