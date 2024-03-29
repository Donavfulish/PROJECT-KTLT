#pragma once
#include <iostream>
#include <vector>
#include "raylib.h"
using namespace std;

static string LinkToTexture = "Texture\\";

void LoginWindow();

#define BORDER_WIDTH 3
#define TEXT_MARGIN 20
static Font font;
static int RightClickOn;
void LoadAllSound();
void GameStarting_Menu();
void GameStarting_Play();
void GameStarting_Play_Option();
void Play_OPTION(int boardWidth, int boardLength);
void Play_OPTION_ADVANCED(int boardWidth, int boardLength);

extern vector<int> cellID;
extern vector<Texture> cellTexture;
void arrangeCellID();
void LoadNCellTexture(int N);
void UnloadAllCellTexture();

struct Account
{
	string username;
	string password;
};

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

struct str_node
{
	int val;
	str_node* pNext;
};

struct str_linkedList
{
	str_node* pHead;
	str_node* pTail;
	int width;
};

struct InputBox {
	Rectangle rect;
	string text;
	Font font;
	bool active;
};

void setInputBoxActive(InputBox& inputBox);
void fillTextInputBox(InputBox& inputBox);
void DrawInputBox(InputBox& inputBox);
void DrawInputBox_Hide(InputBox& inputBox);

str_node* createNode(int data);
void addTail(str_linkedList& list, int data);
void removeHead(str_linkedList& list);
void removeAtK(str_linkedList& list, int k);
void deleteLinkedList(str_linkedList& list);

void Paint_Broad(int** c, int height, int width, matrix Matrix);
void PickCell(int** c, int height, int width, int& countcell, matrix &Matrix);
void PickOption(int** c, Rectangle recBulb, Rectangle recSetting, matrix& Matrix, Texture2D Bulb);
int countDistinctCell(int** c, int boardHeight, int boardWidth);
int countCellOccurrences(int** c, int boardHeight, int boardWidth);
bool checkUseDij(Vector2 A, Vector2 B, int Size, int** c);
vector<Vector2> MoveSuggestion(matrix Matrix, int** c, int& status);

void PaintBroad_Advanced(str_linkedList*& list, int** c, int height, int width, matrix Matrix);
void PickCell_Advanced(str_linkedList*& list, int** c, int width, int height, int& countcell, matrix& Matrix);
void PickOption_Advanced(str_linkedList* list, int** c, Rectangle recBulb, Rectangle recSetting, matrix& Matrix, Texture2D Bulb);