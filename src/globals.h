#pragma once
namespace
{
	const int WIDTH = 640 - 32;
	const int HEIGHT = 640;
	
	enum ID{PLAYER, ENEMY, COIN, PILL, FRUITS};
	enum STATE{TITLE, PLAYING, LOST};
	enum GHOSTSTATE{CHASE, FRIGHTENED, SCATTER, RETREATING};  
	enum PACMANTSTATE{NORMAL, POWERUP, DYING, WINNER};
	enum GHOSTID{BLACKY, PINKY, INKY, CLYDE}; 
	
	int keys = -1;
	enum KEYS{UP, DOWN, LEFT, RIGHT, ENTER};
	
	int left_coins = 0;

	const int mapSize = 19 * 20;
	const int tileSize = 32;
	
	int map[20][21] =		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
							 0, 0, 2, 1, 1, 2, 1, 1, 1, 2, 0, 2, 1, 1, 1, 2, 1, 1, 2, 0, 0,
							 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0,
							 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0,
							 0, 0, 2, 1, 1, 2, 1, 2, 1, 2, 2, 2, 1, 2, 1, 2, 1, 1, 2, 0, 0,
							 0, 0, 5, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 5, 0, 0,
							 0, 0, 2, 1, 1, 2, 0, 2, 1, 2, 0, 2, 1, 2, 0, 2, 1, 1, 2, 0, 0,
							 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0,
							 0, 0, 0, 0, 0, 1, 0, 2, 1, 2, 2, 2, 1, 2, 0, 1, 0, 0, 0, 0, 0,
							 1, 1, 1, 1, 1, 2, 1, 2, 0, 0, 3, 0, 0, 2, 1, 2, 1, 1, 1, 1, 1,
							 0, 0, 0, 0, 0, 1, 0, 1, 0, 4, 4, 4, 0, 1, 0, 1, 0, 0, 0, 0, 0,
							 0, 0, 0, 0, 0, 1, 0, 1, 0, 4, 4, 4, 0, 1, 0, 1, 0, 0, 0, 0, 0,
							 0, 0, 2, 1, 1, 2, 0, 1, 0, 0, 0, 0, 0, 1, 0, 2, 1, 1, 2, 0, 0,
							 0, 0, 5, 0, 0, 1, 0, 2, 1, 1, 1, 1, 1, 2, 0, 1, 0, 0, 5, 0, 0,
							 0, 0, 2, 2, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 2, 2, 0, 0,
							 0, 0, 0, 1, 0, 2, 1, 2, 2, 0, 0, 0, 2, 2, 1, 2, 0, 1, 0, 0, 0,
							 0, 0, 2, 2, 1, 2, 0, 0, 2, 2, 0, 2, 2, 0, 0, 2, 1, 2, 2, 0, 0,
							 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0,
							 0, 0, 2, 1, 1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 2, 0, 0,
							 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	//Legend:
	//0 - wall
	//1 - empty tile
	//2 - intersection point
	//3 - Ghost House doors
	//4 - Ghost House
	//5 - Power Ups
}