#include "mobile_object.h"

void MobileObject::MoveUp()
{
	y -= velocity; // nie w UPDATES?
}
void MobileObject::MoveDown()
{
	y += velocity;
}
void MobileObject::MoveLeft()
{
	x -= velocity;
}
void MobileObject::MoveRight()
{
	x += velocity;
}

void MobileObject::Collided(int ObjectID)
{

}