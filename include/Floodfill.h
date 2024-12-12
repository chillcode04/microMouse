#ifndef FLOODFILL_H
#define FLOODFILL_H

#include <queue>
#include "motorControll.h"
using namespace std;

extern int width, height; 

extern queue<pair<int, int>> Way; 

extern uint8_t maze[6][6];

extern int currentDirection;            // 0 Báº¯c 1 ÄÃ´ng 2 Nam 3 TÃ¢y
extern int dx[];            // Di chuyá»ƒn: trÃªn, dÆ°á»›i, trÃ¡i, pháº£i
extern int dy[];
extern int distanceToEnd[6][6];             // Máº£ng khoáº£ng cÃ¡ch

bool isValid(int y, int x, int dist, int width, int height, uint8_t mazeVal, int direction);

bool CheckWay(int y, int x, int a, int b);

bool wallBetween(int currentY, int currentX, int nextY, int nextX);

void turnToDirection(int currentDirection, int targetDirection);

int calculateTargetDirection(int currentX, int currentY, int nextX, int nextY);

void GoToNextCell(int currentY, int currentX, int nextY, int nextX, int currentDirection);

void floodFill(int endY, int endX);

void findPath(int startY, int startX, int endY,  int endX);

void SolveMaze(queue<pair<int, int>> &Way);

void moveForward();

void turnLeft();

void turnRight();

#endif // FLOODFILL_H