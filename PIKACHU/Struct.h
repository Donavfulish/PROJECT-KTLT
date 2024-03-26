#pragma once
#include <iostream>
#include "raylib.h"
using namespace std;

static string LinkToTexture = "Texture\\";

#define BORDER_WIDTH 3
#define TEXT_MARGIN 20
static Font font;
static int RightClickOn;
void LoadAllSound();
void GameStarting_Menu();
void GameStarting_Play();
void GameStarting_Play_Option();
void Play_OPTION(int boardWidth, int boardLength);

struct board
{
	int check = 0;
	char data;
};

struct matrix
{
	board** val;
	int width, height, life, score;
};

void Paint_Broad(int** c, int height, int width, matrix Matrix);
void PickCell(int** c, int height, int width, int& countcell, matrix &Matrix);
//int countDistinctCell(int c[][12]);
int countCellOccurrences(int** c, int boardHeight, int boardWidth);
bool checkUseDij(Vector2 A, Vector2 B, int Size, int** c);
