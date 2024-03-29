#include <iostream>
#include "struct.h"
#include <fstream>

using namespace std;

void saveGame(int life, int boardHeight, int boardWidth, int** c, vector<int> cellID)
{
	ofstream f;
	f.open("Data\\saveGame.txt");
	f << life << endl;
	f << endl;
	f << boardHeight << "x" << boardWidth << endl << endl;
	for (int i = 1; i <= boardHeight; i++)
	{
		for (int j = 1; j <= boardWidth; j++)
		{
			f << c[i][j] << " ";
		}
		f << endl;
	}
	f << endl;
	for (int x : cellID)
	{
		f << x << " ";
	}
	f.close();
}