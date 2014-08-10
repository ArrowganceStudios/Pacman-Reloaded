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

void Ghost::Init(float x, float y, int boundX, int boundY, Ghost &enemy, Pacman &player,int GhostID, ALLEGRO_BITMAP *image)
{
	MobileObject::Init(x, y, boundX, boundY, image);

	Ghost::velocity = velocity;

	Ghost::GhostID = GhostID;
	Ghost::away = away;
	Ghost::enemy = &enemy;
	Ghost::player = &player;

	maxFrame = 4;
	curFrame = 0;
	frameCount = 0;								
	frameDelay = 5;
	frameWidth = 32;
	frameHeight = 32;
	animationColumns = 4;
	animationRows = 4;

	clock_tick = 0;

	if(image != NULL)
		Ghost::image = image;
	 
	Ghost::SetDir(-1);
	Ghost::ChangeState(CHASE);
}

void Ghost::SetTarget(float targetX, float targetY, int targetDirection, int away)
{
	
	Ghost::targetX = targetX;
	Ghost::targetY = targetY;
	Ghost::targetDirection = targetDirection;
	Ghost::away = away;
	
	
}

void Ghost::Update()
{
	//AI
	if(!((int)x % tileSize) && !((int)y % tileSize) && (map[GetRow()][GetColumn()] == 2))
	{
		if(state == CHASE)
				SetTarget(player->GetX(),player->GetY(), player->GetDirection(), away);

		if(GhostID == CLYDE && state != FRIGHTENED)
			if(sqrt((pow(GetDistanceX(player->GetX(), 0),2) + pow(GetDistanceY(player->GetY(), 0),2))) <= 8*tileSize)
			{
				if(state != CHASE)
					ChangeState(CHASE);
			}
			else 
				if(state != SCATTER)
					ChangeState(SCATTER);

		AI(targetX, targetY,targetDirection, GhostID);
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

void Ghost::SetScatterPoint(float ScatterPointX, float ScatterPointY)
	{
		Ghost::ScatterPointX = ScatterPointX;
		Ghost::ScatterPointY = ScatterPointY;
		

	}
void  Ghost::ChangeState(int newState)
	{
			state = newState;
			
			if(state == CHASE)
				{
					ReverseDirection();
					SetTarget(player->GetX(),player->GetY(), player->GetDirection(), away);
					velocity = 2;
				}
			else if(state == SCATTER)
				{
					ReverseDirection();
					SetTarget(ScatterPointX, ScatterPointY, -1, 0);
					velocity = 2;
				}
			else if(state == RETREATING)
				{
					//image = al_load_bitmap("data/img/gh6.png");
					SetTarget(304, 320, -1, 0);
					velocity = 2;
				}
			else if(state == FRIGHTENED)
				{
					ReverseDirection();
					clock_tick = 0;
					//image = al_load_bitmap("data/img/gh5.png");
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

void Ghost::Clock()
{
	if(state == FRIGHTENED || state == SCATTER)
		if(clock_tick == 7)
			ChangeState(CHASE);
		else if(state == CHASE)
			if(clock_tick == 0)
				ChangeState(SCATTER);
	clock_tick++;
			
	if(clock_tick >= 27)
		clock_tick = 0;

}

float Ghost::GetDistanceX(float targetX, int dx)
{
	return  abs(enemy->x - targetX + dx);
}

float Ghost::GetDistanceY(float targetY, int dy)
{
	return  abs(enemy->y - targetY + dy);
}

void Ghost::ReverseDirection()
{
	if(GetDirection() == RIGHT)
		SetDir(LEFT);
	else if(GetDirection() == UP)
		SetDir(DOWN);
	else if(GetDirection() == LEFT)
		SetDir(RIGHT);
	else if(GetDirection() == DOWN)
		SetDir(UP);
}

void Ghost::AI(float targetX, float targetY,int targetDirection, int GhostID)
{
	if(state == FRIGHTENED)
	{
		RandomMovement();	
	}	

	else
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
			if(GhostID == INKY) //whch means inky, simplest but non-intuitinal condition
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

void Ghost::Collided(int ObjectID)
{
	if(state == FRIGHTENED)
		ChangeState(RETREATING);
		

}