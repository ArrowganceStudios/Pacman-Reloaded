#include "power_up.h"

PowerUp::PowerUp()
{
	SetID(POWERUP);
	StaticObject::StaticObject();
}

PowerUp::Init(float x, float y, int boundX, int boundY)
{
	StaticObject::Init(x, y, boundX, boundY, NULL);
}

PowerUp::Destroy()
{
	SetAlive(false);
}

PowerUp::Render()
{
	al_draw_filled_circle(GetX() - 16, GetY() - 16, 4, al_map_rgb_f(1, 1, 0));			//TEMPORARY
}