#include "power_up.h"

PowerUp::PowerUp()
{
	SetID(PILL);
	StaticObject::StaticObject();
}

void PowerUp::Init(float x, float y, int boundX, int boundY)
{
	StaticObject::Init(x, y, boundX, boundY, NULL);
	PowerUp::SetAlive(true);
	PowerUp::SetCollidable(true);
}

void PowerUp::Destroy()
{
}

void PowerUp::Render()
{
	al_draw_filled_circle(GetX() - 16, GetY() - 16, 6, al_map_rgb_f(1, 1, 0));			//TEMPORARY
}

void PowerUp::Collided()
{
	
		SetAlive(false);
	
}
