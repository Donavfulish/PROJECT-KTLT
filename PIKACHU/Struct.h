#pragma once
#include <iostream>
#include "raylib.h"
using namespace std;

struct board
{
	int width, lenght;
	int** n;
	Rectangle rec;
	int check;
	char data;
};

struct cell
{
	int indexRow, indexCol;
	Vector2 postion;
};
void Paint_Broad(int c[][11]);