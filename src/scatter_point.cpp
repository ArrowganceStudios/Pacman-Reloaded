#include "scatter_point.h"

ScatterPoint::ScatterPoint()
{
	StaticObject::StaticObject();
	float x = 0;
	float y = 0;
}

void ScatterPoint::Init(float x, float y)
{
	ScatterPoint::x = x;
	ScatterPoint::y = y;
}
