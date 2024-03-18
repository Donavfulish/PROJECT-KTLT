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

	board() {
		check = 0;
	}
};

void Paint_Broad();