#include <iostream>
#include "struct.h"
#include "raylib.h"
#include <time.h>

using namespace std;
Rectangle rec = { 100, 100, 200, 80 };
board val[11][11];

bool checkDelete(char c1, char c2)
{
    return c1 == c2;
}
// KHOI TAO BANG
void Paint_Broad(int c[][11])
{
    int press = 0;
    cell cell1;
    rec = { 10,10,75,75 };
    for (int i = 0; i < 10; i++)
    {
        rec.y += 75;
        rec.x = 10;
        for (int j = 0; j < 10; j++)
        {
            rec.x += 75;
            char asciiChar = 'A' + c[i][j];
            char text[2] = { asciiChar, '\0' };
            val[i][j].data = text[0];

            if (val[i][j].check == 1 && press == 0)
            {
                DrawRectangleRounded(rec, 0, 0, Fade(BLACK, 0.5));
                DrawText(text, rec.x + 7.5 + MeasureText(text, 50) / 2, rec.y + MeasureText(text, 50) / 2, 50, Fade(WHITE, 0.6f));
                press = 1;
                cell1.postion.x = 10 + 75 * (i - 1);
                cell1.postion.y = 10 + 75 * (j - 1);
                cell1.indexRow = i;
                cell1.indexCol = j;
                continue;
            }
            else if (val[i][j].check == 1 && press == 1)
            {
                press = 0;
                if (checkDelete(text[0], val[cell1.indexRow][cell1.indexCol].data))
                {
                    DrawRectangleRounded(rec, 0, 0, WHITE);
                    DrawRectangleRounded({ cell1.postion.x, cell1.postion.y, 75, 75 }, 0, 0, WHITE);
                }
                else
                {
                    DrawRectangleRounded(rec, 0, 0, Fade(BLUE, 0.6f));
                    DrawRectangleLines(rec.x, rec.y, rec.width, rec.height, Fade(BLACK, 2));
                    DrawText(text, rec.x + 7.5 + MeasureText(text, 50) / 2, rec.y + MeasureText(text, 50) / 2, 50, Fade(BLACK, 0.8f));
                    DrawRectangleRounded({cell1.postion.x, cell1.postion.y, 75,75 }, 0, 0, Fade(BLUE, 0.6f));
                    DrawRectangleLines(cell1.postion.x, cell1.postion.y, 75, 75, Fade(BLACK, 2));
                    DrawText(text, cell1.postion.x + 7.5 + MeasureText(text, 50) / 2, cell1.postion.y + MeasureText(text, 50) / 2, 50, Fade(BLACK, 0.8f));

                }
                continue;
            }

            DrawRectangleRounded(rec, 0, 0, Fade(BLUE, 0.6f));
            DrawRectangleLines(rec.x, rec.y, rec.width, rec.height, Fade(BLACK, 2));
            DrawText(text, rec.x + 7.5 + MeasureText(text, 50) / 2, rec.y + MeasureText(text, 50) / 2, 50, Fade(BLACK, 0.8f));

            if (CheckCollisionPointRec(GetMousePosition(), rec)) 
            {
                DrawRectangleRounded(rec, 0, 0, Fade(RED, 0.7f));
                DrawText(text, rec.x + 7.5 + MeasureText(text, 50) / 2, rec.y + MeasureText(text , 50) / 2, 50, Fade(WHITE, 0.6f));
                
                if (IsMouseButtonPressed(0))
                    val[i][j].check = 1;
            }
        }
    }
}


