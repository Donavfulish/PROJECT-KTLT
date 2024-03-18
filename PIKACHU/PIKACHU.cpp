#include <iostream>
//#include "struct.h"
#include <raylib.h>
using namespace std;
const int Width = 1200;
const int Height = 900;
//#include <iostream>
//#include "struct.h"
//#include "raylib.h"
#include <time.h>
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

using namespace std;
Rectangle rec = { 100, 100, 200, 80 };
int broa[10] = { 0 };
board val[10][10];
// VE BANG NE
void Paint_Broad(int c[][10])
{
    rec = { 10,10,75,75 };
    for (int i = 1; i < 10; i++)
    {
        rec.y += 75;
        rec.x = 10;
        for (int j = 1; j < 10; j++)
        {
            rec.x += 75;
            if (val[i][j].check == 1) {
                //  DrawRectangleRounded(rec, 0.5, 1, Fade(BLACK, 1));
                continue;
            }
            char asciiChar = 'A' + c[i][j];
            char text[2] = { asciiChar, '\0' };
            DrawRectangleRounded(rec, 0, 0, Fade(BLUE, 0.6f));
            DrawRectangleLines(rec.x, rec.y, rec.width, rec.height, Fade(BLACK, 2));
            DrawText(text, rec.x + 7.5 + MeasureText(text, 50) / 2, rec.y + MeasureText(text, 50) / 2, 50, Fade(BLACK, 0.8f));
            int a = GetMouseX();
            int b = GetMouseY();

            if (CheckCollisionPointRec(GetMousePosition(), rec)) {
                DrawRectangleRounded(rec, 0, 0, Fade(RED, 0.7f));
                DrawText(text, rec.x + 7.5 + MeasureText(text, 50) / 2, rec.y + MeasureText(text + c[i][j], 50) / 2, 50, Fade(WHITE, 0.6f));
                if (IsMouseButtonDown(1)) {
                    //  DrawRectangleRounded(rec, 0.5, 1, Fade(BLACK, 0.5f));
                    val[i][j].check = 1;
                }
            }
        }
    }
}



int main()
{
    srand(time(0));
    InitWindow(Width, Height, "dcm van ha");
    int c[10][10];
    for (int i = 1; i < 10; i++)
        for (int j = 1; j < 10; j++)
        {
            c[i][j] = rand() % 26;
            //cout << c[i][j] << "\n";
        }
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        Paint_Broad(c);
        EndDrawing();
    }
    return 0;
}

// Au sua 123