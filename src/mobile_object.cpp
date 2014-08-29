#include "mobile_object.h"
#include <iostream>

MobileObject::MobileObject()
{
	GameObject::GameObject();
	
	state = -1;
}

void MobileObject::Init(float x, float y, int boundX, int boundY, ALLEGRO_BITMAP *image)
{
	GameObject::Init(x, y, boundX, boundY, image);
}


int MobileObject::GetColumn()
{
	return ((int) x) / tileSize;
}
int MobileObject::GetRow()
{
	return ((int) y) / tileSize - 1;
}

void MobileObject::MoveUp()
{
	y -= velocity;
	if((int)y % 32 == 31)
		y++;
}
void MobileObject::MoveDown()
{
	y += velocity;
	if((int)y % 32 == 1)
		y--;
}
void MobileObject::MoveLeft()
{
	x -= velocity;
	if((int)x % 32 == 31)
		x++;
}
void MobileObject::MoveRight()
{
	x += velocity;
	if((int)x % 32 == 1)
		x--;
}

bool MobileObject::CanMoveUp()
{
	return (map[GetRow() - 1][GetColumn()]);
}
bool MobileObject::CanMoveDown()
{
	if(GetState() != RETREATING && (map[GetRow() + 1][GetColumn()] == 3))
		return 0;
	else
		return (map[GetRow() + 1][GetColumn()]);
}
bool MobileObject::CanMoveLeft()
{
	return (map[GetRow()][GetColumn() - 1]);
}
bool MobileObject::CanMoveRight()
{
	return (map[GetRow()][GetColumn() + 1]);
}

void MobileObject::Collided(int ObjectID)
{
	//eeeee????????
}