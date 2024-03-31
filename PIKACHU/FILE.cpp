#include <iostream>
#include "struct.h"
#include <fstream>

using namespace std;

void saveGame(int life, int size, int** c, vector<int> cellID)
{
	ofstream f;
	f.open("Data\\saveGame.txt");
	f << life << endl;
	f << endl;
	f << size << "x" << size << endl << endl;
	for (int i = 1; i <= size; i++)
	{
		for (int j = 1; j <= size; j++)
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