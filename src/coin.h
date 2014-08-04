#pragma once

#include "static_object.h"

class Coin : public StaticObject
{
public:
	Coin::Coin();

	void Init(float x, float y, int boundX, int boundY);

	void Destroy();
	void Render();
};