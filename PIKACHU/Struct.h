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

void Paint_Broad(int c[][11]);
void PickCell(int c[][11]);
