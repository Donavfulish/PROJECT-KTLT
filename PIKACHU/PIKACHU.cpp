#include <iostream>
#include "struct.h"
#include <raylib.h>
#include <algorithm>
#include <vector>
#include <random>

using namespace std;
const int Width = 1200;
const int Height = 900;

int main()
{
    GameStarting_Menu();
    srand(time(0));
    InitWindow(Width, Height, "dcm van ha");
    vector<int> ArrayRandom;
    int count = -1, c[11][11];

    for (int i = 1; i <= 4; i++)
        for (int j = 0; j <= 25; j++)
            ArrayRandom.push_back(j);
    shuffle(ArrayRandom.begin(), ArrayRandom.end(), default_random_engine(time(nullptr)));

    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            c[i][j] = ArrayRandom[++count];
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        Paint_Broad(c);
        EndDrawing();
    }
    return 0;
}

// Au sua 123