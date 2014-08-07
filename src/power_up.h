#pragma once

#include "static_object.h"

class PowerUp : public StaticObject
{
	PowerUp();
	Init(float x, float y, int boundX, int boundY);

	void Collided(ObjectID);

	void Destroy();
	void Render();

}