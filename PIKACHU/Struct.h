#pragma once
#include <iostream>
#include "raylib.h"
using namespace std;

void GameStarting_Menu();


struct board
{
	int check = 0;
	char data;
};

struct matrix
{
	board** val;
	int width, length;
};

void Paint_Broad(int c[][12]);
void PickCell(int c[][12]);
bool checkUseDij(Vector2 A, Vector2 B, int Size, int c[][12]);