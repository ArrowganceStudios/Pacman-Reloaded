#include "enemy.h"
#include <iostream>
#include <math.h>
#include "player.h"

Ghost::Ghost()
{
	MobileObject::MobileObject();
	x = 0;
	y = 0;
	boundX = 0;
	boundY = 0;
	velocity = 1;

	image = NULL;
}

void Ghost::Init(float x, float y, int boundX, int boundY, float velocity, ALLEGRO_BITMAP *image)
{
	MobileObject::Init(x, y, boundX, boundY, image);

	Ghost::velocity = velocity;

	maxFrame = 2;
	curFrame = 0;
	frameCount = 0;								
	frameDelay = 15;
	frameWidth = 32;
	frameHeight = 32;
	animationColumns = 2;
	animationRows = 4;

	Ghost::image = image;
	Ghost::SetDir(-1);
}
void Ghost::Update(int map[][21], Pacman &player, int away, Ghost &enemy)
{
	/*if(!((int)x % 32) && !((int)y % 32))
	{
		bool go = false;				// this is the shittiest shitty shit in the shitty history of shit 
		while(!go)
		{
			switch(rand() % 4)
			{
				case UP:
					if(CanMoveUp()) 
					{
						Ghost::SetDir(UP);
						go = true;
					}
					break;
				case DOWN:
					if(CanMoveDown()) 
					{
						Ghost::SetDir(DOWN);
						go = true;
					}
					break;
				case LEFT:
					if(CanMoveLeft()) 
					{
						Ghost::SetDir(LEFT);
						go = true;
					}
					break;
				case RIGHT:
					if(CanMoveRight()) 
					{
						Ghost::SetDir(RIGHT);
						go = true;
					}
					break;
			}
		}
	}*/
	//AI
	if(!((int)x % 32) && !((int)y % 32) && (map[GetRow()][GetColumn()] == 2))
	{
		AI(player, away, enemy);
	}

	switch(direction)
	{
		case UP:
			if(CanMoveUp()  || (int)y % 32) MoveUp();
			break;
		case DOWN:
			if(CanMoveDown() || (int)y % 32) MoveDown();
			break;
		case LEFT:
			if(CanMoveLeft() || (int)x % 32) MoveLeft();
			break;
		case RIGHT:
			if(CanMoveRight() || (int)x % 32) MoveRight();
			break;
	}
	if(x < 2)
		x = WIDTH + 32;
	else if(x > WIDTH+30)
		x = 0;
	if(y < 2)
		y = HEIGHT + 32;
	else if (y > HEIGHT+30)
		y = 0;
}

void Ghost::Render()
{
	MobileObject::Render();

	switch(GetDirection())
	{
		case UP:
			animationRows = 0;
			break;
		case DOWN:
			animationRows = 1;
			break;
		case LEFT:
			animationRows = 2;
			break;
		case RIGHT:
			animationRows = 3;
			break;
	}
	if(++frameCount > frameDelay)
	{
		curFrame++;
		if(curFrame >= maxFrame)
			curFrame = 0;
		else if(curFrame <= 0)
			curFrame = maxFrame;

		frameCount = 0;
	}
	int fx = (curFrame % animationColumns) * frameWidth;
	int fy = (animationRows) * frameHeight;
	
	al_draw_bitmap_region(image, fx, fy, frameWidth, frameHeight, x - frameWidth, y - frameHeight, 0);
}

float Ghost::GetDistanceX(Pacman &player, int dx, Ghost &enemy)
{
	return  abs(enemy.x - player.GetX() + dx);
}

float Ghost::GetDistanceY(Pacman &player, int dy, Ghost &enemy)
{
	return  abs(enemy.y - player.GetY() + dy);
}

void Ghost::AI(Pacman &player, int away, Ghost &enemy)
{
	float angle = 0;

	int distanceX = 0;
	int distanceY = 0;

	int dx = 0;
	int dy = 0;

	switch(player.GetDirection())
		{
		case UP:
			dy += away*32;
			break;
		case DOWN:
			dy -= away*32;
			break;
		case RIGHT:
			dx -= away*32;
			break;
		case LEFT:
			dx += away*32;
			break;
		}
		
		if(away == 2) //whch means inky, simplest but non-intuitinal condition
		{
			distanceX = GetDistanceX(player, dx, enemy);
			distanceY = GetDistanceY(player, dy, enemy);
			dx += distanceX;
			dy += distanceY;
		}
		else 
		{
			distanceX = GetDistanceX(player, dx, enemy);
			distanceY = GetDistanceY(player, dy, enemy);
		}

		angle = AngleToTarget(player, dx, dy);

		if(distanceX > distanceY && (CanMoveRight() || CanMoveLeft()))
		{
			if(cos(angle) >= 0 && CanMoveRight() && (GetDirection() != LEFT))
				SetDir(RIGHT);
			else if(cos(angle) < 0 && CanMoveLeft() && (GetDirection() != RIGHT))
				SetDir(LEFT);
			else 
				PriorityMovement();
		}
		else
		{
			if(sin(angle) >= 0 && CanMoveDown() && (GetDirection() != UP))
				SetDir(DOWN);
			else if(sin(angle) < 0 && CanMoveUp() && (GetDirection() != DOWN))
				SetDir(UP);
			else
				PriorityMovement();
		}
}

void Ghost::PriorityMovement()
{
	if(CanMoveUp() && (GetDirection() != DOWN)) SetDir(UP);
	else if(CanMoveLeft() && (GetDirection() != RIGHT)) SetDir(LEFT);
	else if(CanMoveDown() && (GetDirection() != UP)) SetDir(DOWN);
	else if(CanMoveRight() && (GetDirection() != LEFT)) SetDir(RIGHT);
}