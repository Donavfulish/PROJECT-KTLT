#include <iostream>
#include "Struct.h"


#define RCO_NONE -1
#define RCO_EXIT 0
#define RCO_OPTION 1
#define RCO_TOURNAMENT 2
extern Font font;
extern int RightClickOn = RCO_NONE;

void GameStarting_Play()
{
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
                WantToExit = true;
                break;
            case RCO_TOURNAMENT:
                break;
            case RCO_EXIT:
                WantToExit = true;
                break;
            }
            RightClickOn = RCO_NONE;
        }
        
        if (WantToExit) break;
#pragma endregion
    }

    // Giải phóng texture Background
    UnloadTexture(texture);

    // Đóng cửa sổ
    CloseWindow();
}

void GameStarting_Play_Option()
{
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

    while (!WindowShouldClose())
    {
        
    }
}