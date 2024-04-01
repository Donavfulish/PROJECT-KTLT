#include <iostream>
#include "Struct.h"
#include "soundlib.h"

// RCO: Right Click On
#define RCO_NONE -1
#define RCO_EXIT 0
#define RCO_PLAY 1
#define RCO_RESUME_GAME 2
#define RCO_LEADERBOARD 3
#define RCO_INSTRUCTION 4

// Hàm in ra và thực hiện các chức năng của cửa sổ Pikachu Menu
void GameStarting_Menu()
{
    RightClickOn = RCO_NONE;
    // Khai báo kích thước màn hình
    const int screenWidth = 1200;
    const int screenHeight = 900;

    SetTargetFPS(60);
    // Khởi tạo cửa sổ
    InitWindow(screenWidth, screenHeight, "Pikachu Menu");

    // Tải texture Background từ máy tính
    Texture2D texture = LoadTexture("GameStarting_Menu.png");

    // Vòng lặp chính
    while (!WindowShouldClose())
    {
        if (!IsSoundPlaying(sound_BackgroundMenu)) PlaySound(sound_BackgroundMenu);
        if (IsSoundPlaying(sound_BackgroundPlay)) PlaySound(sound_BackgroundPlay);
        RightClickOn = RCO_NONE;

        // Bắt đầu vẽ
        BeginDrawing();
        ClearBackground(SKYBLUE);

        // Insert Background cho Menu
        DrawTexture(texture, 0, 0, WHITE);

        // Xác định vùng diện tích của các button
        Rectangle rect_Play = { 177, 374.7, 264.9, 69.9 };
        Rectangle rect_ResumeGame = { 177, 458.6, 264.9, 69.9 };
        Rectangle rect_Leaderboard = { 177, 542.4, 264.9, 69.9 };
        Rectangle rect_Instruction = { 177, 626.2, 264.9, 69.9 };
        Rectangle rect_Exit = { 177, 710, 264.9, 69.9 };

        // Kiểm tra xem nếu cá nút được bấm
        if (CheckCollisionPointRec(GetMousePosition(), rect_Play))
        {
            DrawRectangleRec(rect_Play, Fade(GREEN, 0.3f));
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                PlaySound(sound_ClickOnButton);
                RightClickOn = RCO_PLAY;
            }
        }
        else if (CheckCollisionPointRec(GetMousePosition(), rect_ResumeGame))
        {
            DrawRectangleRec(rect_ResumeGame, Fade(GREEN, 0.3f));
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                PlaySound(sound_ClickOnButton);
                RightClickOn = RCO_RESUME_GAME;
            }
        }
        else if (CheckCollisionPointRec(GetMousePosition(), rect_Leaderboard))
        {
            DrawRectangleRec(rect_Leaderboard, Fade(GREEN, 0.3f));
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                PlaySound(sound_ClickOnButton);
                RightClickOn = RCO_LEADERBOARD;
            }
        }
        else if (CheckCollisionPointRec(GetMousePosition(), rect_Instruction))
        {
            DrawRectangleRec(rect_Instruction, Fade(GREEN, 0.3f));
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                PlaySound(sound_ClickOnButton);
                RightClickOn = RCO_INSTRUCTION;
            }
        }
        else if (CheckCollisionPointRec(GetMousePosition(), rect_Exit))
        {
            DrawRectangleRec(rect_Exit, Fade(GREEN, 0.3f));
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                PlaySound(sound_ClickOnButton);
                RightClickOn = RCO_EXIT;
            }
        }

        // Kết thúc vẽ
        EndDrawing();

#pragma region Thực hiện chức năng sau khi click chuột
        bool WantToExit = false;
        if (RightClickOn != RCO_NONE)
        {
            switch (RightClickOn)
            {
            case RCO_PLAY:
                GameStarting_Play();
                break;
            case RCO_RESUME_GAME:
                Play_Save();
                break;
            case RCO_LEADERBOARD:
                createLeaderboard();
                ViewLeaderboard();
                break;
            case RCO_INSTRUCTION:
                Instruction();
                break;
            case RCO_EXIT:
                WantToExit = true;
                break;
            }
        }

        if (WantToExit) break;
#pragma endregion
    }

    // Giải phóng texture Background
    UnloadTexture(texture);

    // Đóng cửa sổ
    CloseWindow();
}