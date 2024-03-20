#include <iostream>
#include "struct.h"
#include "raylib.h"
#include <time.h>
#include <vector>

using namespace std;
Rectangle rec = { 100, 100, 200, 80 };
board val[11][11];
Vector2 selectedCells[2] = { {-1, -1}, {-1, -1} };

// Khởi tạo lưới ô chữ cái
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
            // Kiểm tra ô đã bị xóa chưa
            if (c[i][j] != -1)
            {
                //Nếu chưa thì khởi tạo chữ cái ngẫu nhiên và vẽ ô
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

//Cập nhật các ô đã được click chọn
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
            // Kiểm tra vị trí con trỏ chuột
            if (CheckCollisionPointRec(GetMousePosition(), rec) && c[i][j] != -1)
            {

                // Con trỏ chuột di tới đâu thì ô ở đó hiện đỏ lên (giống như cờ vua online)
                DrawRectangleRounded(rec, 0, 0, Fade(RED, 0.7f));
                DrawText(&val[i][j].data, rec.x + 7.5 + MeasureText(&val[i][j].data, 50) / 2, rec.y + MeasureText(&val[i][j].data, 50) / 2, 50, Fade(WHITE, 0.6f));

                // Nếu click chuột thì bắt đầu cập nhật
                if (IsMouseButtonPressed(0))
                {
                    // Nếu chọn ô đầu tiên trong cặp thì cập nhật vector vị trí 1
                    if (selectedCells[0].x == -1)
                        selectedCells[0] = { float(j), float(i) };

                    // Nếu chọn ô thứ 2 trong cặp thì cập nhật vector vị trí 2
                    else if (selectedCells[1].x == -1)
                        selectedCells[1] = { float(j), float(i) };
                }
            }
        }
    }

    // Ô đầu tiên được chọn trong cặp sẽ chuyển thành màu đen báo hiệu cho việc đã chọn
    if (selectedCells[0].x != -1 && selectedCells[1].x == -1)
    {
        // Lưu lại tọa độ và vị trí ô
        int x1 = 10 + 75 * (selectedCells[0].x + 1);
        int y1 = 10 + 75 * (selectedCells[0].y + 1);
        int i1 = selectedCells[0].y;
        int j1 = selectedCells[0].x;
        Rectangle rec1 = { x1, y1, 75, 75 };

        // Chuyển ô thành màu đen
        DrawRectangleRounded(rec1, 0, 0, Fade(BLACK, 1));
        DrawText(&val[i1][j1].data, rec1.x + 7.5 + MeasureText(&val[i1][j1].data, 50) / 2, rec1.y + MeasureText(&val[i1][j1].data, 50) / 2, 50, Fade(WHITE, 0.6f));
    }

    // Nếu đã chọn xong một cặp thì kiểm tra điều kiện, thõa mãn thì xóa cả 2 ô
    else if (selectedCells[1].x != -1) 
    {
        // Lưu tọa độ và vị trí 2 ô
        int x1 = 10 + 75 * (selectedCells[0].x + 1);
        int y1 = 10 + 75 * (selectedCells[0].y + 1);
        int x2 = 10 + 75 * (selectedCells[1].x + 1);
        int y2 = 10 + 75 * (selectedCells[1].y + 1);
        int i1 = selectedCells[0].y;
        int j1 = selectedCells[0].x;
        int i2 = selectedCells[1].y;
        int j2 = selectedCells[1].x;
        Rectangle rec1 = { x1, y1, 75, 75 }, rec2 = { x2, y2, 75, 75 };

        // Nếu thõa điều kiện thì dữ liệu chứa trong ô bị xóa, trạng thái của ô từ 0 trở thành 1
        if (val[i1][j1].data == val[i2][j2].data)
        {
            DrawRectangleRounded(rec1, 0, 0, RAYWHITE);
            DrawRectangleRounded(rec2, 0, 0, RAYWHITE);
            c[i1][j1] = -1;
            c[i2][j2] = -1;
            val[i1][j1].check = 1;
            val[i2][j2].check = 1;
        }

        // Nếu không thõa thì trở về trạng thái ban đầu trước khi click
        else
        {
            DrawRectangleRounded(rec1, 0, 0, Fade(BLUE, 0.6f));
            DrawRectangleLines(x1, y1, 75, 75, Fade(BLACK, 2));
            DrawText(&val[i1][j1].data, rec1.x + 7.5 + MeasureText(&val[i1][j1].data, 50) / 2, rec1.y + MeasureText(&val[i1][j1].data, 50) / 2, 50, Fade(WHITE, 0.6f));
            DrawRectangleRounded(rec2, 0, 0, Fade(BLUE, 0.6f));
            DrawRectangleLines(x2, y2, 75, 75, Fade(BLACK, 2));
            DrawText(&val[i2][j2].data, rec2.x + 7.5 + MeasureText(&val[i2][j2].data, 50) / 2, rec2.y + MeasureText(&val[i2][j2].data, 50) / 2, 50, Fade(WHITE, 0.6f));
        }

        // Cập nhật lại trạng thái ban đầu cho hai vecto lưu vị trí
        selectedCells[0] = { -1, -1 };
        selectedCells[1] = { -1, -1 };
    }
}

