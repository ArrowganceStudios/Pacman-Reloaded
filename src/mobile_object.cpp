#include "mobile_object.h"
#include <iostream>

MobileObject::MobileObject()
{
	GameObject::GameObject();
}

void MobileObject::Init(float x, float y, int boundX, int boundY,int state, ALLEGRO_BITMAP *image)
{
	GameObject::Init(x, y, boundX, boundY, image);
}


int MobileObject::GetColumn()
{
	//std::cout << "Column: " << ((int) x) / 32 - 1 << std::endl;
	return ((int) x) / 32;
}
int MobileObject::GetRow()
{
	//std::cout << "Row: " << ((int) y) / 32 - 1 << std::endl;
	return ((int) y) / 32 - 1;
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
	//std::cout << "A One up Row = " << GetRow() - 1 << std::endl;
	//std::cout << "A One up Column = " << GetColumn() << std::endl;
	return (map[GetRow() - 1][GetColumn()]);
}
bool MobileObject::CanMoveDown()
{
	//std::cout << "A One down Row = " << GetRow() + 1 << std::endl;
	//std::cout << "A One down Column = " << GetColumn() << std::endl;
	//if(!(map[GetRow() + 1][GetColumn()] == 3))
		return (map[GetRow() + 1][GetColumn()]);
	/*else if(GetID() == PLAYER)
		return false;
	else if(PlayingState == FRIGHTENED)
		return true;
	else 
		return false;*/
}
bool MobileObject::CanMoveLeft()
{
	//std::cout << "A One left Row = " << GetRow()<< std::endl;
	//std::cout << "A One left Column = " << GetColumn() -1 << std::endl;
	return (map[GetRow()][GetColumn() - 1]);
}
bool MobileObject::CanMoveRight()
{
	//std::cout << "A One right Row = " << GetRow() << std::endl;
	//std::cout << "A One right Column = " << GetColumn() + 1<< std::endl;
	return (map[GetRow()][GetColumn() + 1]);
}

void MobileObject::Collided(int ObjectID)
{

}