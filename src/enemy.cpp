#include "enemy.h"
#include <math.h>
#include "player.h"

Ghost::Ghost()
{
	SetID(ENEMY);

	x = 0;
	y = 0;
	boundX = 0;
	boundY = 0;
	velocity = 1;
	away = 0;
	targetX = 0; 
	targetY = 0;
	image = NULL;
}

void Ghost::Init(float x, float y, int boundX, int boundY,int away, Ghost &enemy, Pacman &player,int GhostID, ALLEGRO_BITMAP *image, ALLEGRO_BITMAP *fimage, ALLEGRO_BITMAP *eimage)
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

	dot_counter = 0;
	if(GhostID == BLACKY)
		CanGhostGo = true;
	else
		CanGhostGo = false;

	clock_tick = 0;

	if(image != NULL && fimage != NULL && eimage != NULL)
	{
		Ghost::defaultImage = image;
		Ghost::image = image;
		Ghost::fImage = fimage;
		Ghost::eImage = eimage;
	}
	
	Ghost::SetDir(-1);
	Ghost::ChangeState(CHASE);
}

void Ghost::SetTarget(float targetX, float targetY, int targetDirection, int away)
{

	int dx = 0;
	int dy = 0;

	switch(targetDirection)
	{
	case UP:
		dy -= away*tileSize;
		break;
	case DOWN:
		dy += away*tileSize;
		break;
	case RIGHT:
		dx += away*tileSize;
		break;
	case LEFT:
		dx -= away*tileSize;
		break;
	}

	Ghost::targetX = targetX + dx;
	Ghost::targetY = targetY + dy;

	if(GhostID == INKY && GetState() == CHASE && map[GetRow()][GetColumn()] != 4)
	{

			Ghost::targetX -= enemy->GetX() - Ghost::targetX;
			Ghost::targetY -= enemy->GetY() - Ghost::targetY;
	}

	
}

void Ghost::Update()
{
	//AI
	if(!((int)x % tileSize) && !((int)y % tileSize) && ((map[GetRow()][GetColumn()] == 2) || (map[GetRow()][GetColumn()] == 4)))
	{
		if(GetState() == RETREATING && map[GetRow()][GetColumn()] == 4)
		{															
			ChangeState(CHASE);
			return;
		}

		if(GhostID == CLYDE && state != FRIGHTENED && state != RETREATING)
		{
			if(GetDistance(GetX(), GetY()) <= 8*tileSize)
				ChangeState(CHASE);
			else 
				ChangeState(SCATTER);
		}

		if(state == CHASE && GhostID != CLYDE)
			SetTarget(player->GetX(),player->GetY(), player->GetDirection(), away);

		if(map[GetRow()][GetColumn()] == 4 && CanGhostGo)
				SetTarget(316, 272, -1, 0);
			AI(GhostID);
		
	}

	switch(direction)
	{
		case UP:
			if((CanMoveUp()  || (int)y % tileSize)) MoveUp();
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

	if(x < 1)
		x = WIDTH + tileSize;
	else if(x > WIDTH+31)
		x = 1;
	if(y < 1)
		y = HEIGHT + tileSize;
	else if (y > HEIGHT+31)
		y = 1;
}

void Ghost::SetCanGhostGo(bool CanGhostGo)
{
	Ghost::CanGhostGo = CanGhostGo;
}


bool Ghost::GetIfCanGhostGo()
{
	return CanGhostGo;
}

void Ghost::CheckIfGhostCanGoOut()
{
	if(map[GetRow()][GetColumn()] == 4)
	{
		dot_counter++;
		if(dot_counter >= GhostID*8) 
			SetCanGhostGo(true);
		else
			SetCanGhostGo(false);
	}

}


void Ghost::SetScatterPoint(float ScatterPointX, float ScatterPointY)
{
	Ghost::ScatterPointX = ScatterPointX;
	Ghost::ScatterPointY = ScatterPointY;
}

void Ghost::ChangeState(int newState)
{
	state = newState;
	
	if(state == CHASE)
	{		if(GhostID != CLYDE) 
			ReverseDirection();
		SetCollidable(true);
		SetTarget(player->GetX(),player->GetY(), player->GetDirection(), away);
		velocity = 2;

	}
	else if(state == SCATTER)
	{
		SetCollidable(true);
		SetTarget(ScatterPointX, ScatterPointY, -1, 0);
		velocity = 2;
	}
	else if(state == RETREATING)
	{
		SetCollidable(false);
		SetTarget(320, 320, -1, 0); 
		velocity = 2;
	}
	else if(state == FRIGHTENED)
	{
		ReverseDirection();
		velocity = 1.1;
		clock_tick = 0;
	}
}

void Ghost::Render()
{
	if(state != FRIGHTENED)
	{
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
	}
	else
	{
		animationRows = 0;
		SetImage(fImage);
	}
	if(state == RETREATING)
	{
		animationColumns = 1;
		maxFrame = 1;
		SetImage(eImage);
	}
	if(state == CHASE || state == SCATTER)
	{
		animationColumns = 4;
		maxFrame = 4;
		SetImage(defaultImage);
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

	float blink = 1;

		if(clock_tick > 4 && curFrame > 2 && GetState() == FRIGHTENED)
			blink = 0.05;

		int fx = (curFrame % animationColumns) * frameWidth;
		int fy = (animationRows) * frameHeight;
		
		al_draw_tinted_bitmap_region(image, al_map_rgba_f(1, 1, 1, blink), fx, fy, frameWidth, frameHeight, x - frameWidth, y - frameHeight, 0);
}

void Ghost::SetImage(ALLEGRO_BITMAP *newImage)
{
	Ghost::image = newImage;
}
void Ghost::Clock()
{
	if((state == FRIGHTENED || state == SCATTER) && clock_tick == 7)
		ChangeState(CHASE);
	else if(state == CHASE && clock_tick == 0)
		ChangeState(SCATTER);

	clock_tick++;
			
	if(clock_tick >= 17)
		clock_tick = 0;
}

int Ghost::CanMove(int where)
{
	if(where == UP && direction != DOWN)
		return (map[GetRow() - 1][GetColumn()]);
	else if(where == DOWN && direction != UP)
		if(map[GetRow() + 1][GetColumn()] == 3 && state != RETREATING)
			return 0;
		else
			return (map[GetRow() + 1][GetColumn()]);
	else if(where == RIGHT && direction != LEFT)
		return (map[GetRow()][GetColumn() + 1]);
	else if(where == LEFT && direction != RIGHT)
		return (map[GetRow()][GetColumn() - 1]);
	else 
		return 0;
}

float Ghost::GetDistance(float x,float y)
{
	
	return  sqrt((pow(targetX - x, 2) + pow(targetY - y, 2)));
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

void Ghost::AI(int GhostID)
{
	if(!CanGhostGo)
		SetDir(DOWN);
	else
	{
		if(GetState() == FRIGHTENED)
		{
			RandomMovement();
			return;
		}

	
		int dir[4];
		int min = 999;
		int chosenDirection = -1;

		dir[UP] = GetDistance(GetX(), GetY() - tileSize);
		dir[DOWN] = GetDistance(GetX(), GetY() + tileSize);
		dir[RIGHT] = GetDistance(GetX() + tileSize, GetY());
		dir[LEFT] = GetDistance(GetX() - tileSize, GetY());


		for(int i = 0; i < 4;i++)
			if(CanMove(i))
				if(min > dir[i])
				{
					min = dir[i];
					chosenDirection = i;
				}
	
		if (chosenDirection != -1)
			SetDir(chosenDirection);

		}
}


void Ghost::RandomMovement()
{
	
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

void Ghost::Collided()
{
	if(state == FRIGHTENED)
		ChangeState(RETREATING);
}
