#pragma once

#include "static_object.h"

class Coin : public StaticObject
{
public:
	Coin();

	void Init(float x, float y, int boundX, int boundY);

	void Render();

	void Collided();
};
