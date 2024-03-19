#include <iostream>
#include "struct.h"
#include "raylib.h"
#include <time.h>
#include <vector>

using namespace std;
Rectangle rec = { 100, 100, 200, 80 };
board val[11][11];

// KHOI TAO BANG
void Paint_Broad(int c[][11])
{
    rec = { 10,10,75,75 };
    for (int i = 0; i < 10; i++)
    {
        rec.y += 75;
        rec.x = 10;
        for (int j = 0; j < 10; j++)
        {
            rec.x += 75;
            if (c[i][j] != -1)
            {
                //VE CAC O CO CAC CHU CAI DUOC TAO NGAU NHIEN
                char asciiChar = 'A' + c[i][j];
                char text[2] = { asciiChar, '\0' };
                val[i][j].data = text[0];

                DrawRectangleRounded(rec, 0, 0, Fade(BLUE, 0.6f));
                DrawRectangleLines(rec.x, rec.y, rec.width, rec.height, Fade(BLACK, 2));
                DrawText(text, rec.x + 7.5 + MeasureText(text, 50) / 2, rec.y + MeasureText(text, 50) / 2, 50, Fade(BLACK, 0.8f));
            }
        }
    }
}

//CAP NHAT CAC O DUOC CHON
Vector2 selectedCells[2] = { {-1, -1}, {-1, -1} };
void PickCell(int c[][11])
{
    rec = { 10,10,75,75 };
    for (int i = 0; i < 10; i++)
    {
        rec.y += 75;
        rec.x = 10;
        for (int j = 0; j < 10; j++)
        {
            rec.x += 75;
            // KIEM TRA VI TRI CON TRO CHUOT
            if (CheckCollisionPointRec(GetMousePosition(), rec) && c[i][j] != -1)
            {

                // NEU CON TRO CHUOT DANG O VI TRI NAO THI O VUONG DUOC CHUYEN SANG MAU DO GIONG NHU CO VUA
                DrawRectangleRounded(rec, 0, 0, Fade(RED, 0.7f));
                DrawText(&val[i][j].data, rec.x + 7.5 + MeasureText(&val[i][j].data, 50) / 2, rec.y + MeasureText(&val[i][j].data, 50) / 2, 50, Fade(WHITE, 0.6f));

                // CAP NHAT TRANG THAI O VUONG NEU NHU CON TRO CHUOT CLICK VAO
                if (IsMouseButtonPressed(0))
                {
                    // NEU CLICK O DAU TIEN THI CAP NHAT VECTOR VI TRI 1
                    if (selectedCells[0].x == -1)
                        selectedCells[0] = { float(j), float(i) };

                    // NEU CLICK O THU HAI THI CAP NHAT VECTOR VI TRI 2
                    else if (selectedCells[1].x == -1)
                        selectedCells[1] = { float(j), float(i) };
                }
            }
        }
    }

    // NEU DA CHON DUOC MOT O THI O DO DUOC BOI DEN
    if (selectedCells[0].x != -1 && selectedCells[1].x == -1)
    {
        // LUU TOA DO VA VI TRI 
        int x1 = 10 + 75 * (selectedCells[0].x + 1);
        int y1 = 10 + 75 * (selectedCells[0].y + 1);
        int i1 = selectedCells[0].y;
        int j1 = selectedCells[0].x;
        Rectangle rec1 = { x1, y1, 75, 75 };

        // BOI DEN
        DrawRectangleRounded(rec1, 0, 0, Fade(BLACK, 1));
        DrawText(&val[i1][j1].data, rec1.x + 7.5 + MeasureText(&val[i1][j1].data, 50) / 2, rec1.y + MeasureText(&val[i1][j1].data, 50) / 2, 50, Fade(WHITE, 0.6f));
    }

    // NEU DA CHON DUOC 2 O THI KIEM TRA, NEU THOA MAN DIEU KIEN THI XOA CA 2 O
    else if (selectedCells[1].x != -1) 
    {
        // LUU TOA DO VA VI TRI
        int x1 = 10 + 75 * (selectedCells[0].x + 1);
        int y1 = 10 + 75 * (selectedCells[0].y + 1);
        int x2 = 10 + 75 * (selectedCells[1].x + 1);
        int y2 = 10 + 75 * (selectedCells[1].y + 1);
        int i1 = selectedCells[0].y;
        int j1 = selectedCells[0].x;
        int i2 = selectedCells[1].y;
        int j2 = selectedCells[1].x;
        Rectangle rec1 = { x1, y1, 75, 75 }, rec2 = { x2, y2, 75, 75 };

        // NEU THOA DIEU KIEN THI XOA VA CAP NHAT LAI DU LIEU CUA O DO VE KHONG
        if (val[i1][j1].data == val[i2][j2].data)
        {
            DrawRectangleRounded(rec1, 0, 0, RAYWHITE);
            DrawRectangleRounded(rec2, 0, 0, RAYWHITE);
            c[i1][j1] = -1;
            c[i2][j2] = -1;
        }

        // NEU KHONG THOA DIEU KIEN THI TRA O VE TRANG THAI BAN DAU
        else
        {
            DrawRectangleRounded(rec1, 0, 0, Fade(BLUE, 0.6f));
            DrawRectangleLines(x1, y1, 75, 75, Fade(BLACK, 2));
            DrawText(&val[i1][j1].data, rec1.x + 7.5 + MeasureText(&val[i1][j1].data, 50) / 2, rec1.y + MeasureText(&val[i1][j1].data, 50) / 2, 50, Fade(WHITE, 0.6f));
            DrawRectangleRounded(rec2, 0, 0, Fade(BLUE, 0.6f));
            DrawRectangleLines(x2, y2, 75, 75, Fade(BLACK, 2));
            DrawText(&val[i2][j2].data, rec2.x + 7.5 + MeasureText(&val[i2][j2].data, 50) / 2, rec2.y + MeasureText(&val[i2][j2].data, 50) / 2, 50, Fade(WHITE, 0.6f));
        }

        // CAP NHAT LAI 2 VECTOR LUU VI TRI
        selectedCells[0] = { -1, -1 };
        selectedCells[1] = { -1, -1 };
    }
}

