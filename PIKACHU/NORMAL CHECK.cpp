#include <iostream>
#include "Struct.h"

using namespace std;
// Hàm kiểm tra xem hai ô có ở cạnh nhau không
bool nextcheck(board** val, int i1, int j1, int i2, int j2) 
{
    // Kiểm tra hai ô cùng cột
    if ((i1 + 1 == i2 || i1 - 1 == i2) && (j1 == j2)) {
            return true;
    }

    // Kiểm tra hai ô cùng hàng
    if ((j1 + 1 == j2 || j1 - 1 == j2) && (i1 == i2)) {
            return true;
    }
    return false;
}

// Hàm kiểm tra xem một hàng/cột nằm trong giới hạn cho trước có trống không 
bool linecheck(board** val, int i1, int j1, int i2, int j2) 
{
    // Kiểm tra một  hàng
    if (i1 == i2) 
    {
        int y, x, count = 0;
        x = (j1 > j2) ? j1 : j2;
        y = (j1 > j2) ? j2 : j1;

        // Đếm số ô không trống
        for (int i = x; i <= y; i++) {
            if (val[i1][i].check = 0) {
                count++;
                if (count == 2) return false;
            }
        }

        // Hàng có một ô không trống thì phải là một trong hai đầu mút
        if ((count == 1) && (((val[i1][j1].check = 0) && (val[i2][j2].check = 1)) || ((val[i1][j1].check = 1) && (val[i2][j2].check = 2)))) 
            return true;

        // Hàng hoàn toàn trống
        else if (count == 0) 
            return true;

        return false;
    }

    // Kiểm tra một cột
    if (j1 == j2) 
    {
        int x, y, count = 0;
        x = (i1 > i2) ? i1 : i2;
        y = (i1 > i2) ? i2 : i1;

        // Đếm số ô không trống
        for (int i = x; i <= y; i++) {
            if (val[i][j1].check = 0)
            {
                count++;
                if (count == 2) return false;
            }
        }
        // Cột có một ô không trống thì phải là một trong hai đầu mút
        if ((count == 1) && (((val[i1][j1].check = 0) && (val[i2][j2].check = 1)) || ((val[i1][j1].check = 1) && (val[i2][j2].check = 0)))) 
            return true;

        // Cột hoàn toàn trống
        else if (count == 0) 
            return true;

        return false;
    }
    return false;
}

// Hàm kiểm tra matching loại I
bool Icheck(board** val, int i1, int j1, int i2, int j2)
{
    
    // I Theo hàng
    if (i1 == i2) {
        int y, x, count = 0;
        x = (j1 > j2) ? j1 : j2;
        y = (j1 > j2) ? j2 : j1;

        // Giữa hai ô mà bị chặn thì trả về false
        for (int i = x + 1; i < y; i++) 
        {
            if (val[i1][i].check = 0)
                return false;
        }
        return true;
    }

    // I Theo cột
    if (j1 == j2)
    {
        int x, y, count = 0;
        x = (i1 > i2) ? i1 : i2;
        y = (i1 > i2) ? i2 : i1;

        // Giữa hai ô mà bị chặn thì trả về false
        for (int i = x; i <= y; i++) 
        {
            if (val[i][j1].check = 0)
                return false;
        }
        return true;
    }
    return false;
}

// Hàm kiểm tra matching loại L
bool Lcheck(board** val, int i1, int j1, int i2, int j2) 
{
    // Nếu chung hàng hoặc cột thì không thể là loại L
    if (i1 == i2 || j1 == j2) 
        return false;

    bool c1, c2;
    // Kiểm tra ô tại góc của đường nối chữ L, nếu ô này không trống trả về false
    // Trường hợp ô tại góc có chỉ số i1, j2
    if (val[i1][j2].check = 1) 
    {
        c1 = linecheck(val, i1, j1, i1, j2);
        c2 = linecheck(val, i1, j2, i2, j2);
        if (c1 && c2) 
            return true;
    }

    // Trường hợp ô tại góc có chỉ số i2, j1
    if (val[i2][j1].check = 0) 
    {
        c1 = linecheck(val, i1, j1, i2, j1);
        c2 = linecheck(val, i2, j1, i2, j2);
        if (c1 && c2) 
            return true;
    }
    return false;
}

// Hàm kiểm tra matching loại Z
bool Zcheck(board** val, int i1, int j1, int i2, int j2)
{
    // Nếu cùng hàng/cột thì không thể matching loại Z
    if (i1 == i2 || j1 == j2)
        return false;

    // Matching loại Z sẽ sinh ra ba nhánh, kiểm tra trạng thái các nhánh này ( hai nhánh trên và một nhánh thân )
    bool c1, c2, c3;
    int x, y;
    // Trường hợp nhánh thân là cột
    x = (j1 < j2) ? j1 : j2;
    y = (j1 < j2) ? j2 : j1;

    for (int i = x + 1; i < y; i++) {
        c3 = linecheck(val, i1, i, i2, i);
        if (c3) 
        {
            c1 = linecheck(val, i1, j1, i1, i);
            c2 = linecheck(val, i2, j2, i2, i);
            if (c1 && c2)
                return true;
        }
    }
    // Trường hợp nhánh thân là hàng
    x = (i1 < i2) ? i1 : i2;
    y = (i1 < i2) ? i2 : i1;

    for (int i = x + 1; i < y; i++) {
        c3 = linecheck(val, i, j1, i, j2);
        if (c3) {
            c1 = linecheck(val, i1, j1, i, j1);
            c2 = linecheck(val, i2, j2, i, j2);
            if (c1 && c2)
                return true;
        }
    }
    return false;
}

// Hàm kiểm tra matching loại U
bool Ucheck(board** val, int i1, int j1, int i2, int j2, int length, int width) 
{
    // Kiểm tra nếu cả hai ô cùng ở một cạnh ngoài cùng của lưới thì có thể matching U
    if (((i1 == i2) && (i1 == 0 || i1 == length - 1) || ((j1 == j2) && (j1 == 0 || j1 == width - 1)))) 
        return true;

    // Tương tự matching Z, matching U sẽ bao gồm ba nhánh, hai nhánh cạnh và một nhánh đáy
    bool c1, c2, c3;
    int x, y;

    // Trường hợp nhánh đáy là cột
    x = (j1 < j2) ? j1 : j2;
    y = (j1 < j2) ? j2 : j1;

    for (int i = 0; i < width; i++) {
        if (i <= x || i >= y) 
        {
            c3 = linecheck(val, i1, i, i2, i);
            if (c3)
            {
                c1 = linecheck(val, i1, j1, i1, i);
                c2 = linecheck(val, i2, j2, i2, i);
                if (c1 && c2)
                    return true;
            }

            else if (i == 0 || i == width - 1) 
            {
                c1 = linecheck(val, i1, j1, i1, i);
                c2 = linecheck(val, i2, j2, i2, i);
                if ((c1 && c2) || (c1 && j2 == i) || (j1 == i && c2)) 
                    return true;
            }
        }
    }

    // Trường hợp nhánh đáy là hàng 
    x = (i1 < i2) ? i1 : i2;
    y = (i1 < i2) ? i2 : i1;

    for (int i = 0; i < length; i++) 
    {
        if (i <= x || i >= y) 
        {
            c3 = linecheck(val, i, j1, i, j2);
            if (c3) 
            {
                c1 = linecheck(val, i1, j1, i, j1);
                c2 = linecheck(val, i2, j2, i, j2);
                if (c1 && c2) 
                    return true;
            }

            else if (i == 0 || i == (length - 1)) 
            {
                c1 = linecheck(val, i1, j1, i, j1);
                c2 = linecheck(val, i2, j2, i, j2);
                if ((c1 && c2) || (c1 && i2 == i) || (i1 == i && c2)) 
                    return true;
            }
        }
    }
    return false;
}

// Hàm kiểm tra loại matching của hai ô đưa vào
bool allcheck(board** val, int i1, int j1, int i2, int j2, int length, int width) 
{
    // Matching cạnh nhau
    if (nextcheck(val, i1, j1, i2, j2)) 
        return true;

    // Matching loại I
    else if (Icheck(val, i1, j1, i2, j2))
        return true;

    // Matching loại L
    else if (Lcheck(val, i1, j1, i2, j2))
        return true;

    // Matching loại Z
    else if (Zcheck(val, i1, j1, i2, j2))
        return true;

    // Matching loại U
    else if (Ucheck(val, i1, j1, i2, j2, length, width))
        return true;

    // Không Matching
    return false;
}





