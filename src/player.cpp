#include "player.h"

//constructor
Pacman::Pacman(int x, int y, int bx, int by, int lives, int speed, bool mode)
	:x(x), y(y), boundx(bx), boundy(by), lives(lives), speed(speed), mode(mode)
{
}
//accessors
int Pacman::GetX()
{
	return x;
}

int Pacman::GetY()
{
	return y;
}

int Pacman::GetBoundX()
{
	return boundx;
}

int Pacman::GetBoundY()
{
	return boundy;
}

int Pacman::GetLives()
{
	return lives;
}

int Pacman::GetSpeed()
{
	return speed;
}

bool Pacman::GetMode()
{
	return mode;
}

//utility
void Pacman::Move(KEYS direction)
{
	//to be implemented
}