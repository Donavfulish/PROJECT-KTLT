#include <iostream>
#include "struct.h"
#include "raylib.h"
#include "soundlib.h"
#include <time.h>
#include <set>
#include <map>
#include <vector>
#include <algorithm>
#include <random>
#include <string>

using namespace std;
Rectangle rec = { 100, 100, 200, 80 };
Vector2 selectedCells[2] = { {-1, -1}, {-1, -1} };

// Khởi tạo lưới ô chữ cái
void Paint_Broad(int** c, int size, matrix Matrix)
{
    // Khởi tạo kích thước font và ô chữ
    float recSize = 55 * 10 / size;
    float fontSize = 50.0f;
    Font font = GetFontDefault();
    rec = { 70 - recSize,250 - recSize, recSize, recSize };

    // Vẽ lưới ô
    for (int i = 1; i <= size; i++)
    {
        rec.y += recSize;
        rec.x = 70 - recSize;
        for (int j = 1; j <= size; j++)
        {
            rec.x += recSize;

            // Kiểm tra ô đã bị xóa chưa
            if (c[i][j] != -1)
                DrawTexturePro(cellTexture[c[i][j]], { 0, 0, 1.0f * cellTexture[c[i][j]].width, 1.0f * cellTexture[c[i][j]].height }, rec, { 0, 0 }, 0, WHITE);
        }
    }
}

//Cập nhật các ô đã được click chọn
void PickCell(int** c, int size, int& countcell, matrix &Matrix) // Biến countCell: lưu tổng số ô còn lại
{
    // Khởi tạo kích thước font và ô chữ
    int recSize = 55 * 10 / size;
    int fontSize = 50;
    Font font = GetFontDefault();
    rec = { 70 - float(recSize),250 - float(recSize), float(recSize), float(recSize) };

    // Thao tác với lưới ô
    for (int i = 1; i <= size; i++)
    {
        rec.y += recSize;
        rec.x = 70 - recSize;
        for (int j = 1; j <= size; j++)
        {
            rec.x += recSize;
            // Kiểm tra vị trí con trỏ chuột
            if (CheckCollisionPointRec(GetMousePosition(), rec) && c[i][j] != -1)
            {
                // Con trỏ chuột di tới đâu thì ô ở đó hiện đỏ lên (giống như cờ vua online)
                DrawRectangleRounded(rec, 0, 0, Fade(RED, 0.7f));

                // Nếu click chuột thì bắt đầu cập nhật
                if (IsMouseButtonPressed(0))
                {
                    // Tạo âm thanh
                    PlaySound(sound_ClickOnCell);

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
        int x1 = 70 - recSize + recSize * (selectedCells[0].x);
        int y1 = 250 - recSize + recSize * (selectedCells[0].y);
        int i1 = selectedCells[0].y;
        int j1 = selectedCells[0].x;
        Rectangle rec1 = { x1, y1, recSize, recSize };

        // Chuyển ô thành màu đen
        DrawRectangleRounded(rec1, 0, 0, Fade(BLACK, 0.6f));
    }

    // Nếu đã chọn xong một cặp thì kiểm tra điều kiện, thõa mãn thì xóa cả 2 ô
    else if (selectedCells[1].x == selectedCells[0].x && selectedCells[1].y == selectedCells[0].y)
    {
        selectedCells[0] = { -1, -1 };
        selectedCells[1] = { -1, -1 };
    }
    else if (selectedCells[1].x != -1)
    {
        // Lưu tọa độ và vị trí 2 ô
        int x1 = 70 - recSize * (selectedCells[0].x);
        int y1 = 250 - recSize * (selectedCells[0].y);
        int x2 = 70 - recSize * (selectedCells[1].x);
        int y2 = 250 - recSize * (selectedCells[1].y);
        int i1 = selectedCells[0].y;
        int j1 = selectedCells[0].x;
        int i2 = selectedCells[1].y;
        int j2 = selectedCells[1].x;
        Rectangle rec1 = { x1, y1, recSize, recSize }, rec2 = { x2, y2, recSize, recSize };

        // Nếu thõa điều kiện thì dữ liệu chứa trong ô bị xóa, trạng thái của ô từ 0 trở thành 1
        if (c[i1][j1] == c[i2][j2] && checkUseDij(selectedCells[0], selectedCells[1], size, c))
        {
            // Đúng thì cộng thêm 10 điểm
            Matrix.score += 10;

            // Xóa ô và trả dữ liệu ô về không có
            DrawRectangleRounded(rec1, 0, 0, RAYWHITE);
            DrawRectangleRounded(rec2, 0, 0, RAYWHITE);
            c[i1][j1] = -1;
            c[i2][j2] = -1;
   
            // Tạo âm thanh
            PlaySound(sound_Correct);
            countcell = countCellOccurrences(c, size); // Âu thêm vô để check thôi, Hà xóa cũng được 
        }

        // Nếu không thõa thì trở về trạng thái ban đầu trước khi click
        else
        {
            PlaySound(sound_Wrong);

            // Trừ đi một mạng chuyển trái tim thành màu đen
            Matrix.death++;
            if (Matrix.score > 0) Matrix.score -= 10;
            
            // Vẽ lại 2 ô như trạng thái ban đầu trước khi click
            DrawTexturePro(cellTexture[c[i1][j1]], { 0, 0, 1.0f * cellTexture[c[i1][j1]].height, 1.0f * cellTexture[c[i1][j1]].width }, rec1, { 0, 0 }, 0, WHITE);
            DrawTexturePro(cellTexture[c[i2][j2]], { 0, 0, 1.0f * cellTexture[c[i2][j2]].height, 1.0f * cellTexture[c[i2][j2]].width }, rec2, { 0, 0 }, 0, WHITE);
        }
        // Cập nhật lại trạng thái ban đầu cho hai vecto lưu vị trí
        selectedCells[0] = { -1, -1 };
        selectedCells[1] = { -1, -1 };
    }
}

// Hàm đếm xem trong bảng PlayBoard có bao nhiêu ô khác nhau
int countDistinctCell(int** c, int size)
{
    set<int> cell;
    for (int i = 1; i <= size; i++)
    {
        for (int j = 1; j <= size; j++)
        {
            if (c[i][j] != -1) cell.insert(c[i][j]);
        }
    }
    return cell.size();
}

// Hàm đếm số lần xuất hiện của các ô trong bảng PlayBoard
int countCellOccurrences(int** c, int size)
{
    int countAll = 0;
    map<char, int> cell_occurences;
    for (int i = 1; i <= size; i++)
    {
        for (int j = 1; j <= size; j++)
        {
            if (c[i][j] != -1)
            {
                cell_occurences['A' + c[i][j]]++;
                countAll++;
            }
        }
    }

    cout << cell_occurences.size() << endl;
    for (pair<char, int> duyet : cell_occurences)
    {
        cout << duyet.first << " : " << duyet.second << endl;
    }
    return countAll;
}

void PickOption(int** c, Rectangle recBulb, Rectangle recSetting, matrix& Matrix, Texture2D Bulb, Texture2D Setting, int& countcell, int& setting_option, float& time)
{
    vector<Vector2> Sugestion;
    int status = -1;
    if (CheckCollisionPointRec(GetMousePosition(), recBulb))
    {
        DrawTexturePro(Bulb, { 0, 0, float(Bulb.width), float(Bulb.height) }, { 750, 380, 125, 125 }, { 0, 0 }, 0, Fade(GREEN, 50));
        if (IsMouseButtonPressed(0))
        {
            // Sử dụng quyền gợi ý
            Sugestion = MoveSuggestion(Matrix, c, status);

            // Khởi tạo các thông số sau khi gợi ý trả về tọa độ 2 ô đúng
            float recSize = 55 * 10 / Matrix.size;
            int i1 = Sugestion[0].y;
            int j1 = Sugestion[0].x;
            int i2 = Sugestion[1].y;
            int j2 = Sugestion[1].x;
            Rectangle recSu1 = { (j1 - 1) * recSize + 70, (i1 - 1) * recSize + 250, recSize, recSize };
            Rectangle recSu2 = { (j2 - 1) * recSize + 70, (i2 - 1) * recSize + 250, recSize, recSize };

      
            c[i1][j1] = -1;
            c[i2][j2] = -1;
            countcell -= 2; // Giảm số lượng ô còn lại trên PlayBoard xuống 2
            time -= 5;

            // Tạo âm thanh
            PlaySound(sound_Correct);
        }
    }

    if (CheckCollisionPointRec(GetMousePosition(), recSetting))
    {
        DrawTexturePro(Setting, { 0, 0, float(Setting.width), float(Setting.height) }, recSetting , { 0, 0 }, 0, Fade(GREEN, 50));
        if (IsMouseButtonPressed(0))
            setting_option = 1;
    }
}
// Sắp xếp ID các giá trị của cell
/* Chi tiết:
* Mỗi cell có giá trị int >= 1
* Cell Textures có ID từ 1 -> 50 (1.png -> 50.png)
* Hàm arrangeCellID sắp xếp random thứ tự tương ứng của Cell ID với giá trị trong Cell
* Tức là thay vì Cell = 1 tương ứng với textures có ID = 1 (1.png) thì giờ nó có thể tương ứng với một ID khác sau random
*/
void arrangeCellID()
{
    cellID.clear();
    for (int i = 1; i <= 50; i++)
    {
        cellID.push_back(i);
    }
    shuffle(cellID.begin(), cellID.end(), default_random_engine(time(nullptr)));
}

// Hàm lưu texture của N cell khác nhau dựa vào thứ tự của cellID
void LoadNCellTexture(int N)
{
    cellTexture.clear();
    for (int i = 0; i < N; i++)
    {
        Texture texture = LoadTexture(("Texture\\Cell\\" + to_string(cellID[i]) + ".png").c_str());
        cellTexture.push_back(texture);
    }
}

void UnloadAllCellTexture()
{
    for (Texture& texture : cellTexture)
    {
        UnloadTexture(texture);
    }
}