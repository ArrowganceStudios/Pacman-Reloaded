#include "enemy.h"
#include <iostream>
#include <math.h>
#include "player.h"

Ghost::Ghost()
{
	SetID(ENEMY);

	MobileObject::MobileObject();
	x = 0;
	y = 0;
	boundX = 0;
	boundY = 0;
	velocity = 1;

	image = NULL;
}

void Ghost::Init(float x, float y, int boundX, int boundY, int state, int away, Ghost &enemy, ALLEGRO_BITMAP *image)
{
	MobileObject::Init(x, y, boundX, boundY,state, image);

	Ghost::velocity = velocity;

	Ghost::away = away;
	Ghost::enemy = &enemy;

	maxFrame = 4;
	curFrame = 0;
	frameCount = 0;								
	frameDelay = 6;
	frameWidth = 32;
	frameHeight = 32;
	animationColumns = 4;
	animationRows = 4;


	Ghost::image = image;
	Ghost::SetDir(-1);
	Ghost::ChangeState(state, CHASEandSCATTER);
}
void Ghost::Update(float targetX, float targetY, int targetDirection)
{
	//AI
	if(!((int)x % tileSize) && !((int)y % tileSize) && (map[GetRow()][GetColumn()] == 2))
	{
		AI(targetX, targetY,targetDirection);
	}

	switch(direction)
	{
		case UP:
			if(CanMoveUp()  || (int)y % tileSize) MoveUp();
			break;
		case DOWN:
			if(CanMoveDown() || (int)y % tileSize) MoveDown();
			break;
		case LEFT:
			if(CanMoveLeft() || (int)x % tileSize) MoveLeft();
			break;
		case RIGHT:
			if(CanMoveRight() || (int)x % tileSize) MoveRight();
			break;
	}
	if(x < 2)
		x = WIDTH + tileSize;
	else if(x > WIDTH+30)
		x = 0;
	if(y < 2)
		y = HEIGHT + tileSize;
	else if (y > HEIGHT+30)
		y = 0;
}

void  Ghost::ChangeState(int &state, int newState)
	{
		if(state == CHASEandSCATTER)
			{}
		else if(state == RETREATING)
			{}
		else if(state == FRIGHTENED)
			{}

		state = newState;

		if(state == CHASEandSCATTER)
			{
				velocity = 2;
			}
		else if(state == RETREATING)
			{
				velocity = 2;
			}
		else if(state == FRIGHTENED)
			{
				velocity = 1;
			}
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


float Ghost::GetDistanceX(float targetX, int dx)
{
	return  abs(enemy->x - targetX + dx);
}

float Ghost::GetDistanceY(float targetY, int dy)
{
	return  abs(enemy->y - targetY + dy);
}

void Ghost::AI(float targetX, float targetY,int targetDirection)
{
	float angle = 0;

	int distanceX = 0;
	int distanceY = 0;

	int dx = 0;
	int dy = 0;

	switch(targetDirection)
		{
		case UP:
			dy += away*tileSize;
			break;
		case DOWN:
			dy -= away*tileSize;
			break;
		case RIGHT:
			dx -= away*tileSize;
			break;
		case LEFT:
			dx += away*tileSize;
			break;
		}

			distanceX = GetDistanceX(targetX, dx);
			distanceY = GetDistanceY(targetY, dy);
		if(away == 2) //whch means inky, simplest but non-intuitinal condition
		{
			dx += distanceX;
			dy += distanceY;
		}

		angle = AngleToTarget(targetX, targetY, dx, dy);

		if(distanceX > distanceY && (CanMoveRight() || CanMoveLeft()))
		{
			if(cos(angle) >= 0 && CanMoveRight() && (GetDirection() != LEFT))
				SetDir(RIGHT);
			else if(cos(angle) < 0 && CanMoveLeft() && (GetDirection() != RIGHT))
				SetDir(LEFT);
			else 
				RandomMovement();
		}
		else
		{
			if(sin(angle) >= 0 && CanMoveDown() && (GetDirection() != UP))
				SetDir(DOWN);
			else if(sin(angle) < 0 && CanMoveUp() && (GetDirection() != DOWN))
				SetDir(UP);
			else
				RandomMovement();
		}
}

void Ghost::RandomMovement()
{
	//there is no loop here, as this function is being called every 0.016s when needed anyway.
	switch(rand() % 4)
	{
	case UP:
		if(CanMoveUp() && (GetDirection() != DOWN)) SetDir(UP);
		break;
	case LEFT:
		if(CanMoveLeft() && (GetDirection() != RIGHT)) SetDir(LEFT);
		break;
	case DOWN:
		if(CanMoveDown() && (GetDirection() != UP)) SetDir(DOWN);
		break;
	case RIGHT:
		if(CanMoveRight() && (GetDirection() != LEFT)) SetDir(RIGHT);
		break;
	}
}