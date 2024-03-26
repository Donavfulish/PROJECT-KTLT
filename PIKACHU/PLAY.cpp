﻿#include <iostream>
#include "struct.h"
#include "raylib.h"
#include "soundlib.h"
#include <algorithm>
#include <vector>
#include <random>

#define RCO_NONE -1
#define RCO_EXIT 0
#define RCO_OPTION 1
#define RCO_TOURNAMENT 2

#define LEVEL_BUTTON_SIZE 220

// Hàm hiển thị và thực hiện các chức năng của cửa sổ Pikachu Menu - Play
void GameStarting_Play()
{
    RightClickOn = RCO_NONE;
    // Khai báo kích thước màn hình
    const int screenWidth = 1200;
    const int screenHeight = 900;

    SetTargetFPS(60);
    // Khởi tạo cửa sổ
    SetWindowTitle("Pikachu Menu - Play");

    // Đặt font chữ Amatic SC Bold.ttf
    font = LoadFont("Amatic SC Bold.ttf");

    // Đặt font size
    int fontSize = 70;

    // Tính toạ độ để vẽ các nút
    const int buttonSpacing = 80; // Khoảng cách giữa các nút
    int buttonX = screenWidth * 0.28;
    int buttonY = screenHeight * 0.5;

    // Tải texture Background từ máy tính
    Texture2D texture = LoadTexture("GameStarting_Play.png");

    // Vòng lặp chính
    while (!WindowShouldClose())
    {
        if (!IsSoundPlaying(sound_BackgroundMenu)) PlaySound(sound_BackgroundMenu);

        // Bắt đầu vẽ
        BeginDrawing();
        ClearBackground(SKYBLUE);

        // Insert Background cho Menu
        DrawTexture(texture, 0, 0, WHITE);

        // Vẽ các nút
            // Vẽ button OPTION
        Rectangle rec_Option // Lưu thông tin button hình chữ nhật "OPTION"
        {
            buttonX - MeasureTextEx(font, "TOURNAMENT", fontSize, 1).x / 2 - TEXT_MARGIN,
            buttonY,
            MeasureTextEx(font, "TOURNAMENT", fontSize, 1).x + TEXT_MARGIN * 2,
            MeasureTextEx(font, "OPTION", fontSize, 1).y
        };
        DrawRectangleRec(rec_Option, Fade(ORANGE, 0.7f));
        if (CheckCollisionPointRec(GetMousePosition(), rec_Option))
        {
            DrawRectangleRec(rec_Option, Fade(RED, 0.8f));
            DrawTextEx(font, "OPTION", { buttonX - MeasureTextEx(font, "OPTION", fontSize, 1).x / 2, rec_Option.y }, fontSize, 1, WHITE);
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                PlaySound(sound_ClickOnButton);
                RightClickOn = RCO_OPTION;
            }
        }
        else DrawTextEx(font, "OPTION", { buttonX - MeasureTextEx(font, "OPTION", fontSize, 1).x / 2, rec_Option.y }, fontSize, 1, BLACK);
        DrawRectangleLinesEx(rec_Option, BORDER_WIDTH, BLACK);
        // Vẽ button TOURNAMENT
        Rectangle rec_Tournament // Lưu thông tin button hình chữ nhật "TOURNAMENT"
        {
            buttonX - MeasureTextEx(font, "TOURNAMENT", fontSize, 1).x / 2 - TEXT_MARGIN,
            buttonY + buttonSpacing,
            MeasureTextEx(font, "TOURNAMENT", fontSize, 1).x + TEXT_MARGIN * 2,
            MeasureTextEx(font, "TOURNAMENT", fontSize, 1).y
        };
        DrawRectangleRec(rec_Tournament, Fade(ORANGE, 0.7f));
        if (CheckCollisionPointRec(GetMousePosition(), rec_Tournament))
        {
            DrawRectangleRec(rec_Tournament, Fade(RED, 0.8f));
            DrawTextEx(font, "TOURNAMENT", { buttonX - MeasureTextEx(font, "TOURNAMENT", fontSize, 1).x / 2, rec_Tournament.y }, fontSize, 1, WHITE);
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                PlaySound(sound_ClickOnButton);
                RightClickOn = RCO_TOURNAMENT;
            }
        }
        else DrawTextEx(font, "TOURNAMENT", { buttonX - MeasureTextEx(font, "TOURNAMENT", fontSize, 1).x / 2, rec_Tournament.y }, fontSize, 1, BLACK);
        DrawRectangleLinesEx(rec_Tournament, BORDER_WIDTH, BLACK);
        // Vẽ button BACK
        Rectangle rec_Back // Lưu thông tin button hình chữ nhật "BACK"
        {
            buttonX - MeasureTextEx(font, "TOURNAMENT", fontSize, 1).x / 2 - TEXT_MARGIN,
            buttonY + 2 * buttonSpacing,
            MeasureTextEx(font, "TOURNAMENT", fontSize, 1).x + TEXT_MARGIN * 2,
            MeasureTextEx(font, "BACK", fontSize, 1).y
        };
        DrawRectangleRec(rec_Back, Fade(ORANGE, 0.7f));
        if (CheckCollisionPointRec(GetMousePosition(), rec_Back))
        {
            DrawRectangleRec(rec_Back, Fade(RED, 0.8f));
            DrawTextEx(font, "BACK", { buttonX - MeasureTextEx(font, "BACK", fontSize, 1).x / 2, rec_Back.y }, fontSize, 1, WHITE);
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                PlaySound(sound_ClickOnButton);
                RightClickOn = RCO_EXIT;
            }
        }
        else DrawTextEx(font, "BACK", { buttonX - MeasureTextEx(font, "BACK", fontSize, 1).x / 2, rec_Back.y }, fontSize, 1, RED);
        DrawRectangleLinesEx(rec_Back, BORDER_WIDTH, BLACK);

        // Kết thúc vẽ
        EndDrawing();

#pragma region Thực hiện chức năng sau khi click chuột
        bool WantToExit = false;
        if (RightClickOn != RCO_NONE)
        {
            switch (RightClickOn)
            {
            case RCO_OPTION:
                GameStarting_Play_Option();
                break;
            case RCO_TOURNAMENT:
                break;
            case RCO_EXIT:
                SetWindowTitle("Pikachu Menu");
                WantToExit = true;
                break;
            }
        }
        
        if (WantToExit) break;
#pragma endregion
    }

    // Giải phóng texture Background
    UnloadTexture(texture);
}


#define RCO_LEVEL_4x4 1
#define RCO_LEVEL_6x6 2
#define RCO_LEVEL_8x8 3
#define RCO_LEVEL_10x10 4
// Hàm hiển thị và thực hiện các chức năng của cửa sổ Pikachu Menu - Play - Option
void GameStarting_Play_Option()
{
    RightClickOn = RCO_NONE;
    // Khai báo kích thước màn hình
    const int screenWidth = 1200;
    const int screenHeight = 900;

    SetTargetFPS(60);
    // Khởi tạo cửa sổ
    SetWindowTitle("Pikachu Menu - Play - Option");

    // Đặt font chữ Amatic SC Bold.ttf
    font = LoadFont("Amatic SC Bold.ttf");

    // Đặt font size
    int fontSize = 70;

    // Tính khoảng cách giữa các nút
    int buttonSpacing = 275; 

    // Tải texture Background từ máy tính
    Texture2D texture = LoadTexture("GameStarting_Play_Option.png");

    // Lưu Texture cho các Button chọn Level
    string nameTexture; // Biến lưu tạm tên các texture trên máy
    nameTexture = "Level_4x4.png";
    Image Image_Option_4x4 = LoadImage((LinkToTexture + nameTexture).c_str());
    Texture2D Texture_Option_4x4 = LoadTextureFromImage(Image_Option_4x4);
    UnloadImage(Image_Option_4x4);
    nameTexture = "Level_6x6.png";
    Image Image_Option_6x6 = LoadImage((LinkToTexture + nameTexture).c_str());
    Texture2D Texture_Option_6x6 = LoadTextureFromImage(Image_Option_6x6);
    UnloadImage(Image_Option_6x6);
    nameTexture = "Level_8x8.png";
    Image Image_Option_8x8 = LoadImage((LinkToTexture + nameTexture).c_str());
    Texture2D Texture_Option_8x8 = LoadTextureFromImage(Image_Option_8x8);
    UnloadImage(Image_Option_8x8);
    nameTexture = "Level_10x10.png";
    Image Image_Option_10x10 = LoadImage((LinkToTexture + nameTexture).c_str());
    Texture2D Texture_Option_10x10 = LoadTextureFromImage(Image_Option_10x10);
    UnloadImage(Image_Option_10x10);

    while (!WindowShouldClose())
    {
        if (!IsSoundPlaying(sound_BackgroundMenu)) PlaySound(sound_BackgroundMenu);

        // Bắt đầu vẽ
        BeginDrawing();
        ClearBackground(SKYBLUE);

        // Insert Background cho Menu
        DrawTexture(texture, 0, 0, WHITE);

        /* ------------------------------------------------VẼ CÁC BUTTON CHỌN LEVEL------------------------------------------------*/
        // Vẽ button chọn Level 4x4
        Rectangle rec_Option_4x4
        {
            0.06f * screenWidth, screenHeight / 2 - LEVEL_BUTTON_SIZE / 2,
            LEVEL_BUTTON_SIZE, LEVEL_BUTTON_SIZE
        };
        DrawTexturePro(Texture_Option_4x4,{ 0, 0, 1.0f * Texture_Option_4x4.width, 1.0f * Texture_Option_4x4.height }, rec_Option_4x4, { 0, 0 }, 0, WHITE);
        if (CheckCollisionPointRec(GetMousePosition(), rec_Option_4x4))
        {
            DrawTexturePro(Texture_Option_4x4, { 0, 0, 1.0f * Texture_Option_4x4.width, 1.0f * Texture_Option_4x4.height }, rec_Option_4x4, { 0, 0 }, 0, Fade(RED, 0.5f));
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                PlaySound(sound_ClickOnButton);
                RightClickOn = RCO_LEVEL_4x4;
            }
        }

        // Vẽ button chọn Level 6x6
        Rectangle rec_Option_6x6
        {
            0.06f * screenWidth + buttonSpacing, screenHeight / 2 - LEVEL_BUTTON_SIZE / 2,
            LEVEL_BUTTON_SIZE, LEVEL_BUTTON_SIZE
        };
        DrawTexturePro(Texture_Option_6x6, { 0, 0, 1.0f * Texture_Option_6x6.width, 1.0f * Texture_Option_6x6.height }, rec_Option_6x6, { 0, 0 }, 0, WHITE);
        if (CheckCollisionPointRec(GetMousePosition(), rec_Option_6x6))
        {
            DrawTexturePro(Texture_Option_6x6, { 0, 0, 1.0f * Texture_Option_6x6.width, 1.0f * Texture_Option_6x6.height }, rec_Option_6x6, { 0, 0 }, 0, Fade(RED, 0.5f));
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                PlaySound(sound_ClickOnButton);
                RightClickOn = RCO_LEVEL_6x6;
            }
        }

        // Vẽ button chọn Level 8x8
        Rectangle rec_Option_8x8
        {
            0.06f * screenWidth + 2 * buttonSpacing, screenHeight / 2 - LEVEL_BUTTON_SIZE / 2,
            LEVEL_BUTTON_SIZE, LEVEL_BUTTON_SIZE
        };
        DrawTexturePro(Texture_Option_8x8, { 0, 0, 1.0f * Texture_Option_8x8.width, 1.0f * Texture_Option_8x8.height }, rec_Option_8x8, { 0, 0 }, 0, WHITE);
        if (CheckCollisionPointRec(GetMousePosition(), rec_Option_8x8))
        {
            DrawTexturePro(Texture_Option_8x8, { 0, 0, 1.0f * Texture_Option_8x8.width, 1.0f * Texture_Option_8x8.height }, rec_Option_8x8, { 0, 0 }, 0, Fade(RED, 0.5f));
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                PlaySound(sound_ClickOnButton);
                RightClickOn = RCO_LEVEL_8x8;
            }
        }

        // Vẽ button chọn Level 10x10
        Rectangle rec_Option_10x10
        {
            0.06f * screenWidth + 3 * buttonSpacing, screenHeight / 2 - LEVEL_BUTTON_SIZE / 2,
            LEVEL_BUTTON_SIZE, LEVEL_BUTTON_SIZE
        };
        DrawTexturePro(Texture_Option_10x10, { 0, 0, 1.0f * Texture_Option_10x10.width, 1.0f * Texture_Option_10x10.height }, rec_Option_10x10, { 0, 0 }, 0, WHITE);
        if (CheckCollisionPointRec(GetMousePosition(), rec_Option_10x10))
        {
            DrawTexturePro(Texture_Option_10x10, { 0, 0, 1.0f * Texture_Option_10x10.width, 1.0f * Texture_Option_10x10.height }, rec_Option_10x10, { 0, 0 }, 0, Fade(RED, 0.5f));
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                PlaySound(sound_ClickOnButton);
                RightClickOn = RCO_LEVEL_10x10;
            }
        }

        // Vẽ button BACK
        Rectangle rec_Back // Lưu thông tin button hình chữ nhật "BACK"
        {
            screenWidth / 2 - MeasureTextEx(font, "BACK", fontSize, 1).x / 2 - TEXT_MARGIN,
            screenHeight * 0.85,
            MeasureTextEx(font, "BACK", fontSize, 1).x + TEXT_MARGIN * 2,
            MeasureTextEx(font, "BACK", fontSize, 1).y
        };
        DrawRectangleRec(rec_Back, Fade(ORANGE, 0.7f));
        if (CheckCollisionPointRec(GetMousePosition(), rec_Back))
        {
            DrawRectangleRec(rec_Back, Fade(RED, 0.8f));
            DrawTextEx(font, "BACK", { screenWidth / 2 - MeasureTextEx(font, "BACK", fontSize, 1).x / 2, rec_Back.y }, fontSize, 1, WHITE);
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                PlaySound(sound_ClickOnButton);
                RightClickOn = RCO_EXIT;
            }
        }
        else DrawTextEx(font, "BACK", { screenWidth / 2 - MeasureTextEx(font, "BACK", fontSize, 1).x / 2, rec_Back.y }, fontSize, 1, RED);
        DrawRectangleLinesEx(rec_Back, BORDER_WIDTH, BLACK);

        // Kết thúc vẽ
        EndDrawing();

#pragma region Thực hiện chức năng sau khi click chuột
        bool WantToExit = false;
        if (RightClickOn != RCO_NONE)
        {
            switch (RightClickOn)
            {
            case RCO_LEVEL_4x4:
                cout << "4x4";
                Play_OPTION(4, 4);
                break;
            case RCO_LEVEL_6x6:
                Play_OPTION(6, 6);
                break;
            case RCO_LEVEL_8x8:
                Play_OPTION(8, 8);
                break;
            case RCO_LEVEL_10x10:
                Play_OPTION(10, 10);
                break;
            case RCO_EXIT:
                SetWindowTitle("Pikachu Menu - Play");
                WantToExit = true;
                break;
            }
            RightClickOn = RCO_NONE;
        }

        if (WantToExit) break;
#pragma endregion
        
    }
    UnloadTexture(Texture_Option_4x4);
    UnloadTexture(Texture_Option_6x6);
    UnloadTexture(Texture_Option_8x8);
    UnloadTexture(Texture_Option_10x10);
    UnloadTexture(texture);
}

vector<int> cellID;
vector<Texture> cellTexture;

// Hàm hiển thị cửa sổ chơi và thực thi quá trình chơi
void Play_OPTION(int boardWidth, int boardLength)
{
    // Khai báo kích thước màn hình
    const int screenWidth = 1200;
    const int screenHeight = 900;

    // Cấp phát bộ nhớ cho con trỏ lưu dữ liệu của lưới ô 2 chiều
    srand(time(0));
    vector<int> ArrayRandom;
    int count = -1, countcell;
    int** c = new int* [boardWidth + 1];
    for (int i = 0; i < boardWidth + 2; i++)
        c[i] = new int[boardLength + 2];

    // Khởi tạo -1 cho tất cả giá trị
    for (int i = 0; i < boardWidth + 2; i++) {
        for (int j = 0; j < boardLength + 2; j++) {
            c[i][j] = -1;
        }
    }

    // Cấp phát bộ nhớ cho matrix
    board** val = new board * [boardWidth + 1];
    for (int i = 0; i < boardWidth + 2; i++)
        val[i] = new board[boardLength + 2];

    // Khởi tạo vector ngẫu nhiên các chỉ số nguyên tượng trưng cho mỗi chữ cái sau đó đảo thứ tự ngẫu nhiên
    int value = -1; // Value
    int occ = 6; // Occurrences: Biến lưu số lần xuất hiện tối đa của một ô (phải là số chẵn)
    int cur = 0; // Current: Biến đếm xem ô đang duyệt là ô thứ mấy
    for (int i = 1; i <= boardWidth; i++)
    {
        for (int j = 1; j <= boardLength; j++)
        {
            if (cur++ % occ == 0) value++; // Nếu <occ> ô liên tiếp có giá trị giống nhau (là val) thì val tăng lên 1 
            ArrayRandom.push_back(value);
        }
    }
    shuffle(ArrayRandom.begin(), ArrayRandom.end(), default_random_engine(time(nullptr)));

    // Lưu các chỉ số được đảo ngẫu nhiên vào một mảng hai chiều kiểu nguyên
    for (int i = 1; i <= boardWidth; i++)
        for (int j = 1; j <= boardLength; j++)
            c[i][j] = ArrayRandom[++count];

    // Chuyyển chỉ số thành ký tự vào matrix
    for (int i = 1; i <= boardWidth; i++)
        for (int j = 1; j <= boardLength; j++)
        {
            char asciiChar = 'A' + c[i][j];
            char text[2] = { asciiChar, '\0' };
            val[i][j].data = text[0];
        }

    // Khởi tạo biến matrix
    matrix Matrix;
    Matrix.val = val;
    Matrix.life = boardLength / 2;
    Matrix.width = boardWidth;
    Matrix.height = boardLength;
    Matrix.score = 0;
    int tmp = Matrix.life;


    // Lấy background và các hình trang trí
    InitWindow(screenWidth, screenHeight, "dcm van ha");
    Texture2D background = LoadTexture("BACKground.png");
    Texture2D heart = LoadTexture("heart.png");
    int heartX = 190;
    int heartY = 115;

    // Khởi tạo Textures cho các Cell
    arrangeCellID();
    LoadNCellTexture(countDistinctCell(c, Matrix.height, Matrix.width));

    // Khởi tạo cửa sổ chơi
    while (!WindowShouldClose()) {
        StopSound(sound_BackgroundMenu);
        if (!IsSoundPlaying(sound_BackgroundPlay)) PlaySound(sound_BackgroundPlay);

        BeginDrawing();
        DrawTexturePro(background, { 0, 0, float(background.width), float(background.height) }, { 0, 0, 1200, 900 }, { 0, 0 }, 0, RAYWHITE);

        // Màn có độ khó N*N thì sẽ được cung cấp N/2 mạng
        // g sống
        for (int i = 0; i < Matrix.life; i++)
            DrawTexturePro(heart, { 0, 0, float(heart.width), float(heart.height) }, { float(heartX + 50 * i), float(heartY), 60, 60 }, { 0, 0 }, 0, RAYWHITE);
        for (int i = tmp - 1; i >= Matrix.life; i--)
            DrawTexturePro(heart, { 0, 0, float(heart.width), float(heart.height) }, { float(heartX + 50 * i), float(heartY), 60, 60 }, { 0, 0 }, 0, BLACK);
        Paint_Broad(c, boardLength, boardWidth, Matrix);
        PickCell(c, boardLength, boardWidth, countcell, Matrix);
        // Game Finish Verify
        //if (countCell == 0) /* Code here */; // Nếu không còn ô nào trống
        // if (Hàm MoveSuggestion không tìm thấy gợi ý) /* Code here */
        EndDrawing();
    }
    UnloadTexture(background);
    UnloadAllCellTexture();
}