#include <iostream>
#include "raylib.h"

#define BORDER_WIDTH 3
#define TEXT_MARGIN 20
Font font;

void GameStarting_Menu()
{
    // Khai báo kích thước màn hình
    const int screenWidth = 1200;
    const int screenHeight = 900;

    SetTargetFPS(60);
    // Khởi tạo cửa sổ
    InitWindow(screenWidth, screenHeight, "Pikachu Menu");

    // Đặt font chữ Amatic SC Bold.ttf
    font = LoadFont("Amatic SC Bold.ttf");
    SetTextureFilter(font.texture, 0); // Tắt anti-aliasing cho văn bản (Giúp chữ Pikachu đỡ bị vỡ)

    // Đặt font size
    int fontSize = 70;

    // Tính toạ độ để vẽ các nút
    const int buttonSpacing = 80; // Khoảng cách giữa các nút
    int buttonX = screenWidth * 0.28;
    int buttonY = screenHeight * 0.45;

    // Tải texture Background từ máy tính
    Texture2D texture = LoadTexture("GameStarting_Menu.png");

    // Vòng lặp chính
    while (!WindowShouldClose())
    {
        // Bắt đầu vẽ
        BeginDrawing();
        ClearBackground(SKYBLUE);

        // Insert Background cho Menu
        DrawTexture(texture, 0, 0, WHITE);

        // Vẽ các nút
            // Vẽ button PLAY
        Rectangle rec_Play // Lưu thông tin button hình chữ nhật "Play"
        {
            buttonX - MeasureTextEx(font, "RESUME GAME", fontSize, 1).x / 2 - TEXT_MARGIN,
            buttonY,
            MeasureTextEx(font, "RESUME GAME", fontSize, 1).x + TEXT_MARGIN * 2,
            MeasureTextEx(font, "PLAY", fontSize, 1).y
        };
        DrawRectangleRec(rec_Play, Fade(ORANGE, 0.7f));
        if (CheckCollisionPointRec(GetMousePosition(), rec_Play))
        {
            DrawRectangleRec(rec_Play, Fade(RED, 0.8f));
            DrawTextEx(font, "PLAY", { buttonX - MeasureTextEx(font, "PLAY", fontSize, 1).x / 2, rec_Play.y }, fontSize, 1, WHITE);
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) break;
        }
        else DrawTextEx(font, "PLAY", { buttonX - MeasureTextEx(font, "PLAY", fontSize, 1).x / 2, rec_Play.y }, fontSize, 1, BLACK);
        DrawRectangleLinesEx(rec_Play, BORDER_WIDTH, BLACK);
        // Vẽ button RESUME GAME
        Rectangle rec_ResumeGame // Lưu thông tin button hình chữ nhật "PLAY"
        {
            buttonX - MeasureTextEx(font, "RESUME GAME", fontSize, 1).x / 2 - TEXT_MARGIN,
            buttonY + buttonSpacing,
            MeasureTextEx(font, "RESUME GAME", fontSize, 1).x + TEXT_MARGIN * 2,
            MeasureTextEx(font, "RESUME GAME", fontSize, 1).y
        };
        DrawRectangleRec(rec_ResumeGame, Fade(ORANGE, 0.7f));
        if (CheckCollisionPointRec(GetMousePosition(), rec_ResumeGame))
        {
            DrawRectangleRec(rec_ResumeGame, Fade(RED, 0.8f));
            DrawTextEx(font, "RESUME GAME", { buttonX - MeasureTextEx(font, "RESUME GAME", fontSize, 1).x / 2, rec_ResumeGame.y }, fontSize, 1, WHITE);
            // ...
        }
        else DrawTextEx(font, "RESUME GAME", { buttonX - MeasureTextEx(font, "RESUME GAME", fontSize, 1).x / 2, rec_ResumeGame.y }, fontSize, 1, BLACK);

        DrawRectangleLinesEx(rec_ResumeGame, BORDER_WIDTH, BLACK);
        // Vẽ button LEADERBOARD
        Rectangle rec_Leaderboard // Lưu thông tin button hình chữ nhật "LEADERBOARD"
        {
            buttonX - MeasureTextEx(font, "RESUME GAME", fontSize, 1).x / 2 - TEXT_MARGIN,
            buttonY + buttonSpacing * 2,
            MeasureTextEx(font, "RESUME GAME", fontSize, 1).x + TEXT_MARGIN * 2,
            MeasureTextEx(font, "LEADERBOARD", fontSize, 1).y
        };
        DrawRectangleRec(rec_Leaderboard, Fade(ORANGE, 0.7f));
        if (CheckCollisionPointRec(GetMousePosition(), rec_Leaderboard))
        {
            DrawRectangleRec(rec_Leaderboard, Fade(RED, 0.8f));
            DrawTextEx(font, "LEADERBOARD", { buttonX - MeasureTextEx(font, "LEADERBOARD", fontSize, 1).x / 2, rec_Leaderboard.y }, fontSize, 1, WHITE);
            // ...
        }
        else DrawTextEx(font, "LEADERBOARD", { buttonX - MeasureTextEx(font, "LEADERBOARD", fontSize, 1).x / 2, rec_Leaderboard.y }, fontSize, 1, BLACK);
        DrawRectangleLinesEx(rec_Leaderboard, BORDER_WIDTH, BLACK);
        // Vẽ button CREDIT
        Rectangle rec_Credit // Lưu thông tin button hình chữ nhật "CREDIT"
        {
            buttonX - MeasureTextEx(font, "RESUME GAME", fontSize, 1).x / 2 - TEXT_MARGIN,
            buttonY + buttonSpacing * 3,
            MeasureTextEx(font, "RESUME GAME", fontSize, 1).x + TEXT_MARGIN * 2,
            MeasureTextEx(font, "CREDIT", fontSize, 1).y
        };
        DrawRectangleRec(rec_Credit, Fade(ORANGE, 0.7f));
        if (CheckCollisionPointRec(GetMousePosition(), rec_Credit))
        {
            DrawRectangleRec(rec_Credit, Fade(RED, 0.8f));
            DrawTextEx(font, "CREDIT", { buttonX - MeasureTextEx(font, "CREDIT", fontSize, 1).x / 2, rec_Credit.y }, fontSize, 1, WHITE);
            // ...
        }
        else DrawTextEx(font, "CREDIT", { buttonX - MeasureTextEx(font, "CREDIT", fontSize, 1).x / 2, rec_Credit.y }, fontSize, 1, BLACK);
        DrawRectangleLinesEx(rec_Credit, BORDER_WIDTH, BLACK);
        // Vẽ button EXIT
        Rectangle rec_Exit // Lưu thông tin button hình chữ nhật "EXIT"
        {
            buttonX - MeasureTextEx(font, "RESUME GAME", fontSize, 1).x / 2 - TEXT_MARGIN,
            buttonY + buttonSpacing * 4,
            MeasureTextEx(font, "RESUME GAME", fontSize, 1).x + TEXT_MARGIN * 2,
            MeasureTextEx(font, "EXIT", fontSize, 1).y
        };
        DrawRectangleRec(rec_Exit, Fade(ORANGE, 0.7f));
        if (CheckCollisionPointRec(GetMousePosition(), rec_Exit))
        {
            DrawRectangleRec(rec_Exit, Fade(RED, 0.8f));
            DrawTextEx(font, "EXIT", { buttonX - MeasureTextEx(font, "EXIT", fontSize, 1).x / 2, rec_Exit.y }, fontSize, 1, WHITE);
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) break;
        }
        else DrawTextEx(font, "EXIT", { buttonX - MeasureTextEx(font, "EXIT", fontSize, 1).x / 2, rec_Exit.y }, fontSize, 1, BLACK);
        DrawRectangleLinesEx(rec_Exit, BORDER_WIDTH, BLACK);




        // Kết thúc vẽ
        EndDrawing();
    }

    // Giải phóng texture Background
    UnloadTexture(texture);

    // Đóng cửa sổ
    CloseWindow();
}