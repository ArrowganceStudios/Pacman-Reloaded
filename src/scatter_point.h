#pragma once

#include "static_object.h"
#include "globals.h"

class ScatterPoint : public StaticObject
{
public:
	ScatterPoint();
	void Init(float x, float y, int boundX, int boundY, ALLEGRO_BITMAP *image);
}