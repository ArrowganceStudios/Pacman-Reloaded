#pragma once
namespace
{//still dunno why, but k
const int WIDTH = 640 - 32;
const int HEIGHT = 640;

enum ID{PLAYER, ENEMY, COIN, POWERUP, FRUITS};
enum STATE{TITLE, NORMAL, POWER}; 

int keys = -1;
enum KEYS{UP, DOWN, LEFT, RIGHT};

int mapColumns = 19;
int mapSize = 19 * 20;
int tileSize = 32;

int map[20][21] =		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						 0, 0, 2, 1, 1, 2, 1, 1, 1, 2, 0, 2, 1, 1, 1, 2, 1, 1, 2, 0, 0,
						 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0,
						 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0,
						 0, 0, 2, 1, 1, 2, 1, 2, 1, 2, 2, 2, 1, 2, 1, 2, 1, 1, 2, 0, 0,
						 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0,
						 0, 0, 2, 1, 1, 2, 0, 2, 1, 2, 0, 2, 1, 2, 0, 2, 1, 1, 2, 0, 0,
						 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0,
						 0, 0, 0, 0, 0, 1, 0, 2, 1, 2, 2, 2, 1, 2, 0, 1, 0, 0, 0, 0, 0,
						 1, 1, 1, 1, 1, 2, 1, 2, 0, 0, 1, 0, 0, 2, 1, 2, 1, 1, 1, 1, 1,
						 0, 0, 0, 0, 0, 1, 0, 1, 0, 2, 2, 2, 0, 1, 0, 1, 0, 0, 0, 0, 0,
						 0, 0, 0, 0, 0, 1, 0, 1, 0, 2, 2, 2, 0, 1, 0, 1, 0, 0, 0, 0, 0,
						 0, 0, 2, 1, 1, 2, 0, 1, 0, 0, 0, 0, 0, 1, 0, 2, 1, 1, 2, 0, 0,
						 0, 0, 1, 0, 0, 1, 0, 2, 1, 1, 1, 1, 1, 2, 0, 1, 0, 0, 1, 0, 0,
						 0, 0, 2, 2, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 2, 2, 0, 0,
						 0, 0, 0, 1, 0, 2, 1, 2, 2, 0, 0, 0, 2, 2, 1, 2, 0, 1, 0, 0, 0,
						 0, 0, 2, 2, 1, 2, 0, 0, 2, 2, 0, 2, 2, 0, 0, 2, 1, 2, 2, 0, 0,
						 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0,
						 0, 0, 2, 1, 1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 2, 0, 0,
						 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
}