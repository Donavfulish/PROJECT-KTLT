#pragma once
#include <iostream>
#include <vector>
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

extern vector<int> cellID;
extern vector<Texture> cellTexture;
void arrangeCellID();
void LoadNCellTexture(int N);
void UnloadAllCellTexture();

struct board
{
	int check = 0;
	char data;
};

struct matrix
{
	board** val;
	int width, height, life, score;
	float time;
};
struct statusLine
{
	int direct;
	Vector2 position;
};

void Paint_Broad(int** c, int height, int width, matrix Matrix);
void PickCell(int** c, int height, int width, int& countcell, matrix &Matrix);
void PickOption(int** c, Rectangle recBulb, Rectangle recSetting, matrix& Matrix, Texture2D Bulb);
int countDistinctCell(int** c, int boardHeight, int boardWidth);
int countCellOccurrences(int** c, int boardHeight, int boardWidth);
bool checkUseDij(Vector2 A, Vector2 B, int Size, int** c);
vector<Vector2> MoveSuggestion(matrix Matrix, int** c, int& status);
