#include <iostream>
#include "struct.h"
#include "raylib.h"
#include "soundlib.h"
#include <algorithm>
#include <vector>
#include <random>
#include <chrono>
#include <thread>
#include <fstream>
using namespace std;

#define RCO_NONE -1
#define RCO_EXIT 0
#define RCO_OPTION 1
#define RCO_TOURNAMENT 2

#define LEVEL_BUTTON_SIZE 220
#define NORMAL_MODE 0
#define ADVANCED_MODE 1

#define OPTION_PLAY_AGAIN 1
#define OPTION_BACK_TO_MENU 2
#define OPTION_SAVE_GAME 3
int GameFinishingVerify(bool& isGameFinish, Texture2D win, Texture2D lose_time, Texture2D lose_life, int countcell, int life, float time);

void ModeButtonPressed(Texture2D mode_normal, Texture2D mode_advanced, int& status)
{
    if (status == NORMAL_MODE)
    {
        DrawTexture(mode_normal, 209.3, 353.3, WHITE);
        Rectangle dest = { 337, 353.3, 127.7, 63.6 };
        if (CheckCollisionPointRec(GetMousePosition(), dest))
        {
            Rectangle source = { 1.0f * mode_normal.width / 2, 0, 1.0f * mode_normal.width / 2, 1.0f * mode_normal.height };
            DrawTexturePro(mode_normal, source, dest, { 0, 0 }, 0, Fade(ORANGE, 0.5f));
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                status = ADVANCED_MODE;
            }
        }
    }
    else if (status == ADVANCED_MODE)
    {   
        DrawTexture(mode_advanced, 209.3, 353.3, WHITE);
        Rectangle dest = { 209.3, 353.3, 127.7, 63.6 };
        if (CheckCollisionPointRec(GetMousePosition(), dest))
        {
            Rectangle source = { 0, 0, 1.0f * mode_normal.width / 2, 1.0f * mode_normal.height };
            DrawTexturePro(mode_advanced, source, dest, { 0, 0 }, 0, Fade(YELLOW, 0.5f));
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                status = NORMAL_MODE;
            }
        }
    }
}

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
    Texture2D mode_normal = LoadTexture("button_mode_Normal.png");
    Texture2D mode_advanced = LoadTexture("button_mode_Advanced.png");
    int mode = NORMAL_MODE;

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
            // Vẽ button chọn mode
        ModeButtonPressed(mode_normal, mode_advanced, mode);
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
                GameStarting_Play_Option(mode);
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
void GameStarting_Play_Option(int mode)
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
                if (mode == NORMAL_MODE) Play_OPTION(4, 4);
                else Play_OPTION_ADVANCED(4, 4);
                break;
            case RCO_LEVEL_6x6:
                if (mode == NORMAL_MODE) Play_OPTION(6, 6);
                else Play_OPTION_ADVANCED(6, 6);
                break;
            case RCO_LEVEL_8x8:
                if (mode == NORMAL_MODE) Play_OPTION(8, 8);
                else Play_OPTION_ADVANCED(8, 8);
                break;
            case RCO_LEVEL_10x10:
                if (mode == NORMAL_MODE) Play_OPTION(10, 10);
                else Play_OPTION_ADVANCED(10, 10);
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
int start;
int choice = 0;
void Play_OPTION(int boardWidth, int boardLength)
{
    start = GetTime();
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

    // Khởi tạo biến matrix
    matrix Matrix;
    Matrix.val = val;
    Matrix.life = boardLength / 2;
    Matrix.width = boardWidth;
    Matrix.height = boardLength;
    Matrix.score = 0;
    Matrix.time = boardLength * boardWidth * 3;
    float currenttime = Matrix.time;
    int tmp = Matrix.life;


    // Lấy background và các hình trang trí
    SetWindowTitle("Pikachu - PlayBoard");
    Texture2D background = LoadTexture("BACKground.png");
    Texture2D result_win = LoadTexture("Result_Win.png");
    Texture2D result_lose_time = LoadTexture("Result_TimeRanOut.png");
    Texture2D result_lose_life = LoadTexture("Result_OutOfLives.png");
    Texture2D heart = LoadTexture("heart.png");
    Texture2D Bulb = LoadTexture("Bulb.png");
    Texture2D Setting = LoadTexture("Setting.png");
    Texture2D Settingboard = LoadTexture("Settingboard.png");
    //Texture2D 
    int heartX = 195;
    int heartY = 82;
    int fontSize = 50;
    int setting_option = 0;
    Font font = GetFontDefault();
    Font font_name = LoadFont("Roboto.ttf");
    char s[4];
    Rectangle recBulb = { 750, 380, 125, 125 };
    Rectangle recSetting = { 900, 380, 120, 120 };

    // Khởi tạo Textures cho các Cell
    arrangeCellID();
    LoadNCellTexture(countDistinctCell(c, Matrix.height, Matrix.width));
    countcell = countCellOccurrences(c, Matrix.height, Matrix.width);

    bool isGameFinish = false;
    // Khởi tạo cửa sổ chơi
    while (!WindowShouldClose()) 
    {
        // Chơi nhạc
        StopSound(sound_BackgroundMenu);
        if (!IsSoundPlaying(sound_BackgroundPlay)) PlaySound(sound_BackgroundPlay);

        // Vẽ background
        BeginDrawing();
        DrawTexturePro(background, { 0, 0, float(background.width), float(background.height) }, { 0, 0, 1200, 900 }, { 0, 0 }, 0, RAYWHITE);

        // Vẽ button gợi ý và option in game
        DrawTexturePro(Bulb, { 0, 0, float(Bulb.width), float(Bulb.height) }, { 750, 380, 125, 125 }, { 0, 0 }, 0, RAYWHITE);
        DrawTexturePro(Setting, { 0, 0, float(Setting.width), float(Setting.height) }, { 900, 380, 120, 120 }, { 0, 0 }, 0, RAYWHITE);


        // Màn có độ khó N*N thì sẽ được cung cấp N/2 mạng sống
        for (int i = 0; i < Matrix.life; i++)
            DrawTexturePro(heart, { 0, 0, float(heart.width), float(heart.height) }, { float(heartX + 50 * i), float(heartY), 60, 60 }, { 0, 0 }, 0, RAYWHITE);
        for (int i = tmp - 1; i >= Matrix.life; i--)
            DrawTexturePro(heart, { 0, 0, float(heart.width), float(heart.height) }, { float(heartX + 50 * i), float(heartY), 60, 60 }, { 0, 0 }, 0, BLACK);

        // Hiển thị tên người chơi
        DrawTextEx(font, User.username.c_str(), { 910, 548 }, fontSize, 2, BLACK);

        // Hiển thị sự thay đổi của điểm số
        _itoa_s(Matrix.score, s, 10);
        DrawTextEx(font, s, { 910, 675 }, fontSize, 2, BLACK);

        // Vẽ lưới
        Paint_Broad(c, boardLength, boardWidth, Matrix);
        if (!isGameFinish) PickCell(c, boardLength, boardWidth, countcell, Matrix);
        if (!isGameFinish) PickOption(c, recBulb, recSetting, Matrix, Bulb, Setting, countcell, choice);
        if (choice == 1)
        {
            setting_option = GameSetting(Settingboard);
            if (setting_option == OPTION_PLAY_AGAIN)
            {
                choice = 0;
                Play_OPTION(boardWidth, boardLength);
                break;
            }
            if (setting_option == OPTION_BACK_TO_MENU)
            {
                choice = 0;
                break;
            }
            if (setting_option == OPTION_SAVE_GAME)
            {
                SaveGame(Matrix, c);
                choice = 0;
                break;
            }
        }

        // Cập nhật thời gian và vẽ thanh thời gian
        if (!isGameFinish) currenttime = Matrix.time - (GetTime() - start);
        DrawRectangle(225, 150, 410, 40, Fade(LIGHTGRAY, 200));
        DrawRectangle(230, 155, 400, 30, RAYWHITE);
        DrawRectangle(230, 155, currenttime / Matrix.time * 400, 30, { 255, 105, 180, 180 });

        // Game Finishing Verify
        int endgame_option = GameFinishingVerify(isGameFinish, result_win, result_lose_time, result_lose_life, countcell, Matrix.life, currenttime);
        // Kết thúc vẽ
        EndDrawing();
        if (endgame_option == OPTION_PLAY_AGAIN)
        {
            Play_OPTION(boardWidth, boardLength);
            break;
        }
        if (endgame_option == OPTION_BACK_TO_MENU)
        {
            break;
        }
    }
    UnloadFont(font_name);
    UnloadTexture(background);
    UnloadTexture(result_win);
    UnloadTexture(result_lose_life);
    UnloadTexture(result_lose_time);
    UnloadTexture(heart);
    UnloadTexture(Bulb);
    UnloadTexture(Setting);
    UnloadTexture(Settingboard);
    UnloadAllCellTexture();
}
void SaveGame(matrix Matrix, int** c)
{
    ofstream fs;
    fs.open("SaveData.txt", std::ios::out);
    if (!fs.is_open()) return;
    else
    {
        fs << Matrix.height << "\n";
        fs << Matrix.life << " " << Matrix.score << " " << Matrix.time << "\n";
        for (int i = 1; i <= Matrix.height; i++)
        {
            for (int j = 1; j <= Matrix.width; j++)
            {
                fs << c[i][j] << " ";
            }
            fs << "\n";
        }
        //f << ;
    }
    fs.close();
}
int GameSetting(Texture2D Is) // Is stand for interface setting
{
    DrawRectangle(0, 0, 1200, 900, Fade(BLACK, 0.5f));
    DrawTexturePro(Is, { 0, 0, 1.0f * Is.width, 1.0f * Is.height }, { 0, 0, 1.0f * GetScreenWidth(), 1.0f * GetScreenHeight() }, { 0, 0 }, 0, WHITE);
    Rectangle rect_PlayAgain = { 488.75, 533.25, 221.3, 40.5 };
    Rectangle rect_BackToMenu = { 488.75, 583.6, 221.3, 40.5 };
    Rectangle rect_SaveGame = { 488.75, 482.95, 221.3, 40.5 };
    if (CheckCollisionPointRec(GetMousePosition(), rect_PlayAgain))
    {   
        DrawRectangleRec(rect_PlayAgain, Fade(RED, 0.5f));
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            return OPTION_PLAY_AGAIN;
        }
    }
    else if (CheckCollisionPointRec(GetMousePosition(), rect_BackToMenu))
    {
        DrawRectangleRec(rect_BackToMenu, Fade(RED, 0.5f));
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            return OPTION_BACK_TO_MENU;
        }
    }
    else if (CheckCollisionPointRec(GetMousePosition(), rect_SaveGame))
    {
        DrawRectangleRec(rect_SaveGame, Fade(RED, 0.5f));
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            return OPTION_SAVE_GAME;
        }
    }
}
// Hàm hiển thị cửa sổ chơi và thực thi quá trình chơi
void Play_OPTION_ADVANCED(int boardWidth, int boardLength)
{
    start = GetTime();
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

    // Khởi tạo Linkedlist
    str_linkedList* list = new str_linkedList[boardWidth + 1];
    for (int i = 1; i <= boardWidth; i++)
    {
        list[i].width = 0;
        list[i].pHead = nullptr;
        list[i].pTail = nullptr;
    }

    // Lưu các chỉ số được đảo ngẫu nhiên vào một mảng hai chiều kiểu nguyên
    for (int i = 1; i <= boardWidth; i++)
    {
        str_node* pCurr = list[i].pHead;
        for (int j = 1; j <= boardLength; j++)
        {
            c[i][j] = ArrayRandom[++count];
            addTail(list[i], c[i][j]);
        }
    }

    // Chuyển chỉ số thành ký tự vào matrix
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
    //Matrix.time = boardLength * boardWidth * 3;
    Matrix.time = boardLength * boardWidth;
    float currenttime = Matrix.time;
    int tmp = Matrix.life;


    // Lấy background và các hình trang trí
    SetWindowTitle("Pikachu - PlayBoard");
    Texture2D background = LoadTexture("BACKground.png");
    Texture2D result_win = LoadTexture("Result_Win.png");
    Texture2D result_lose_time = LoadTexture("Result_TimeRanOut.png");
    Texture2D result_lose_life = LoadTexture("Result_OutOfLives.png");
    Texture2D heart = LoadTexture("heart.png");
    Texture2D Bulb = LoadTexture("Bulb.png");
    Texture2D Setting = LoadTexture("Setting.png");
    int heartX = 195;
    int heartY = 82;
    int fontSize = 50;
    Font font = GetFontDefault();
    Font font_name = LoadFont("Roboto.ttf");
    char s[4];
    Rectangle recBulb = { 750, 380, 125, 125 };
    Rectangle recSetting = { 900, 380, 120, 120 };

    // Khởi tạo Textures cho các Cell
    arrangeCellID();
    LoadNCellTexture(countDistinctCell(c, Matrix.height, Matrix.width));
    countcell = countCellOccurrences(c, Matrix.height, Matrix.width);

    bool isGameFinish = false;
    // Khởi tạo cửa sổ chơi
    while (!WindowShouldClose())
    {
        // Chơi nhạc
        StopSound(sound_BackgroundMenu);
        if (!IsSoundPlaying(sound_BackgroundPlay)) PlaySound(sound_BackgroundPlay);

        // Vẽ background
        BeginDrawing();
        DrawTexturePro(background, { 0, 0, float(background.width), float(background.height) }, { 0, 0, 1200, 900 }, { 0, 0 }, 0, RAYWHITE);

        // Vẽ button gợi ý và option in game
        DrawTexturePro(Bulb, { 0, 0, float(Bulb.width), float(Bulb.height) }, { 750, 380, 125, 125 }, { 0, 0 }, 0, RAYWHITE);
        DrawTexturePro(Setting, { 0, 0, float(Setting.width), float(Setting.height) }, { 900, 380, 120, 120 }, { 0, 0 }, 0, RAYWHITE);

        // Màn có độ khó N*N thì sẽ được cung cấp N/2 mạng sống
        for (int i = 0; i < Matrix.life; i++)
            DrawTexturePro(heart, { 0, 0, float(heart.width), float(heart.height) }, { float(heartX + 50 * i), float(heartY), 60, 60 }, { 0, 0 }, 0, RAYWHITE);
        for (int i = tmp - 1; i >= Matrix.life; i--)
            DrawTexturePro(heart, { 0, 0, float(heart.width), float(heart.height) }, { float(heartX + 50 * i), float(heartY), 60, 60 }, { 0, 0 }, 0, BLACK);

        // Hiển thị tên người chơi
        DrawTextEx(font, User.username.c_str(), { 910, 548 }, fontSize, 2, BLACK);

        // Hiển thị sự thay đổi của điểm số
        _itoa_s(Matrix.score, s, 10);
        DrawTextEx(font, s, { 910, 675 }, fontSize, 2, BLACK);

        // Vẽ lưới
        PaintBroad_Advanced(list, c, boardLength, boardWidth, Matrix);
        if (!isGameFinish) PickCell_Advanced(list, c, boardLength, boardWidth, countcell, Matrix);
        if (!isGameFinish) PickOption_Advanced(list, c, recBulb, recSetting, Matrix, Bulb, countcell);

        // Cập nhật thời gian và vẽ thanh thời gian
        if (!isGameFinish) currenttime = Matrix.time - (GetTime() - start);
        DrawRectangle(225, 150, 410, 40, Fade(LIGHTGRAY, 200));
        DrawRectangle(230, 155, 400, 30, RAYWHITE);
        DrawRectangle(230, 155, currenttime / Matrix.time * 400, 30, { 255, 105, 180, 180 });
        
        // Game Finishing Verify
        int endgame_option = GameFinishingVerify(isGameFinish, result_win, result_lose_time, result_lose_life, countcell, Matrix.life, currenttime);
        EndDrawing();

        if (endgame_option == OPTION_PLAY_AGAIN)
        {
            Play_OPTION_ADVANCED(boardWidth, boardLength);
            break;
        }
        if (endgame_option == OPTION_BACK_TO_MENU)
        {
            break;
        }
    }
    UnloadFont(font_name);
    UnloadTexture(background);
    UnloadTexture(result_win);
    UnloadTexture(result_lose_life);
    UnloadTexture(result_lose_time);
    UnloadTexture(heart);
    UnloadTexture(Bulb);
    UnloadTexture(Setting);
    UnloadAllCellTexture();
}

int GameFinishingVerify(bool& isGameFinish, Texture2D win, Texture2D lose_time, Texture2D lose_life, int countcell, int life, float time)
{
    // Nếu không còn ô nào nữa thì3 kết quả YOU WIN
    if (countcell == 0)
    {
        isGameFinish = true;
        DrawRectangle(0, 0, 1200, 900, Fade(BLACK, 0.5f));
        DrawTexturePro(win, { 0, 0, 1.0f * win.width, 1.0f * win.height }, { 0, 0, 1.0f * GetScreenWidth(), 1.0f * GetScreenHeight() }, { 0, 0 }, 0, WHITE);
    }

    // Nếu hết thời gian thì GAME OVER
    else if (time <= 0)
    {
        isGameFinish = true;
        DrawRectangle(0, 0, 1200, 900, Fade(BLACK, 0.5f));
        DrawTexturePro(lose_time, { 0, 0, 1.0f * win.width, 1.0f * win.height }, { 0, 0, 1.0f * GetScreenWidth(), 1.0f * GetScreenHeight() }, { 0, 0 }, 0, WHITE);
    }

    // Nếu hết mạng thì GAME OVER
    else if (life == 0)
    {
        isGameFinish = true;
        DrawRectangle(0, 0, 1200, 900, Fade(BLACK, 0.5f));
        DrawTexturePro(lose_life, { 0, 0, 1.0f * win.width, 1.0f * win.height }, { 0, 0, 1.0f * GetScreenWidth(), 1.0f * GetScreenHeight() }, { 0, 0 }, 0, WHITE);
    }

    if (isGameFinish)
    {
        Rectangle rect_PlayAgain = { 488.75, 533.25, 221.3, 40.5 };
        Rectangle rect_BackToMenu = { 488.75, 583.6, 221.3, 40.5 };
        if (CheckCollisionPointRec(GetMousePosition(), rect_PlayAgain))
        {
            DrawRectangleRec(rect_PlayAgain, Fade(RED, 0.5f));
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                return OPTION_PLAY_AGAIN;
            }
        }
        else if (CheckCollisionPointRec(GetMousePosition(), rect_BackToMenu))
        {
            DrawRectangleRec(rect_BackToMenu, Fade(RED, 0.5f));
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                return OPTION_BACK_TO_MENU;
            }
        }
    }
    return 0;
}

//void Play_OPTION_TOURNAMENT(float& currenttime, int boardWidth, int boardLength)
//{
//    start = GetTime();
//    // Khai báo kích thước màn hình
//    const int screenWidth = 1200;
//    const int screenHeight = 900;
//
//    // Cấp phát bộ nhớ cho con trỏ lưu dữ liệu của lưới ô 2 chiều
//    srand(time(0));
//    vector<int> ArrayRandom;
//    int count = -1, countcell;
//    int** c = new int* [boardWidth + 1];
//    for (int i = 0; i < boardWidth + 2; i++)
//        c[i] = new int[boardLength + 2];
//
//    // Khởi tạo -1 cho tất cả giá trị
//    for (int i = 0; i < boardWidth + 2; i++) {
//        for (int j = 0; j < boardLength + 2; j++) {
//            c[i][j] = -1;
//        }
//    }
//
//    // Cấp phát bộ nhớ cho matrix
//    board** val = new board * [boardWidth + 1];
//    for (int i = 0; i < boardWidth + 2; i++)
//        val[i] = new board[boardLength + 2];
//
//    // Khởi tạo vector ngẫu nhiên các chỉ số nguyên tượng trưng cho mỗi chữ cái sau đó đảo thứ tự ngẫu nhiên
//    int value = -1; // Value
//    int occ = 6; // Occurrences: Biến lưu số lần xuất hiện tối đa của một ô (phải là số chẵn)
//    int cur = 0; // Current: Biến đếm xem ô đang duyệt là ô thứ mấy
//    for (int i = 1; i <= boardWidth; i++)
//    {
//        for (int j = 1; j <= boardLength; j++)
//        {
//            if (cur++ % occ == 0) value++; // Nếu <occ> ô liên tiếp có giá trị giống nhau (là val) thì val tăng lên 1 
//            ArrayRandom.push_back(value);
//        }
//    }
//    shuffle(ArrayRandom.begin(), ArrayRandom.end(), default_random_engine(time(nullptr)));
//
//    // Lưu các chỉ số được đảo ngẫu nhiên vào một mảng hai chiều kiểu nguyên
//    for (int i = 1; i <= boardWidth; i++)
//        for (int j = 1; j <= boardLength; j++)
//            c[i][j] = ArrayRandom[++count];
//
//    // Chuyyển chỉ số thành ký tự vào matrix
//    for (int i = 1; i <= boardWidth; i++)
//        for (int j = 1; j <= boardLength; j++)
//        {
//            char asciiChar = 'A' + c[i][j];
//            char text[2] = { asciiChar, '\0' };
//            val[i][j].data = text[0];
//        }
//
//    // Khởi tạo biến matrix
//    matrix Matrix;
//    Matrix.val = val;
//    Matrix.life = boardLength / 2;
//    Matrix.width = boardWidth;
//    Matrix.height = boardLength;
//    Matrix.score = 0;
//    Matrix.time = boardLength * boardWidth * 3;
//    int tmp = Matrix.life;
//
//
//    // Lấy background và các hình trang trí
//    SetWindowTitle("Pikachu - PlayBoard");
//    Texture2D background = LoadTexture("BACKground.png");
//    Texture2D result_win = LoadTexture("Result_Win.png");
//    Texture2D result_lose_time = LoadTexture("Result_TimeRanOut.png");
//    Texture2D result_lose_life = LoadTexture("Result_OutOfLives.png");
//    Texture2D heart = LoadTexture("heart.png");
//    Texture2D Bulb = LoadTexture("Bulb.png");
//    Texture2D Setting = LoadTexture("Setting.png");
//    int heartX = 195;
//    int heartY = 82;
//    int fontSize = 50;
//    Font font = GetFontDefault();
//    Font font_name = LoadFont("Roboto.ttf");
//    char s[4];
//    Rectangle recBulb = { 750, 380, 125, 125 };
//    Rectangle recSetting = { 900, 380, 120, 120 };
//
//    // Khởi tạo Textures cho các Cell
//    arrangeCellID();
//    LoadNCellTexture(countDistinctCell(c, Matrix.height, Matrix.width));
//    countcell = countCellOccurrences(c, Matrix.height, Matrix.width);
//
//    bool isGameFinish = false;
//    // Khởi tạo cửa sổ chơi
//    while (!WindowShouldClose())
//    {
//        // Chơi nhạc
//        StopSound(sound_BackgroundMenu);
//        if (!IsSoundPlaying(sound_BackgroundPlay)) PlaySound(sound_BackgroundPlay);
//
//        // Vẽ background
//        BeginDrawing();
//        DrawTexturePro(background, { 0, 0, float(background.width), float(background.height) }, { 0, 0, 1200, 900 }, { 0, 0 }, 0, RAYWHITE);
//
//        // Vẽ button gợi ý và option in game
//        DrawTexturePro(Bulb, { 0, 0, float(Bulb.width), float(Bulb.height) }, { 750, 380, 125, 125 }, { 0, 0 }, 0, RAYWHITE);
//        DrawTexturePro(Setting, { 0, 0, float(Setting.width), float(Setting.height) }, { 900, 380, 120, 120 }, { 0, 0 }, 0, RAYWHITE);
//
//
//        // Màn có độ khó N*N thì sẽ được cung cấp N/2 mạng sống
//        for (int i = 0; i < Matrix.life; i++)
//            DrawTexturePro(heart, { 0, 0, float(heart.width), float(heart.height) }, { float(heartX + 50 * i), float(heartY), 60, 60 }, { 0, 0 }, 0, RAYWHITE);
//        for (int i = tmp - 1; i >= Matrix.life; i--)
//            DrawTexturePro(heart, { 0, 0, float(heart.width), float(heart.height) }, { float(heartX + 50 * i), float(heartY), 60, 60 }, { 0, 0 }, 0, BLACK);
//
//        // Hiển thị tên người chơi
//        DrawTextEx(font, User.username.c_str(), { 910, 548 }, fontSize, 2, BLACK);
//
//        // Hiển thị sự thay đổi của điểm số
//        _itoa_s(Matrix.score, s, 10);
//        DrawTextEx(font, s, { 910, 675 }, fontSize, 2, BLACK);
//
//        // Vẽ lưới
//        Paint_Broad(c, boardLength, boardWidth, Matrix);
//        if (!isGameFinish) PickCell(c, boardLength, boardWidth, countcell, Matrix);
//        if (!isGameFinish) PickOption(c, recBulb, recSetting, Matrix, Bulb, countcell);
//
//        // Cập nhật thời gian và vẽ thanh thời gian
//        if (!isGameFinish) currenttime = Matrix.time - (GetTime() - start);
//        DrawRectangle(225, 150, 410, 40, Fade(LIGHTGRAY, 200));
//        DrawRectangle(230, 155, 400, 30, RAYWHITE);
//        DrawRectangle(230, 155, currenttime / Matrix.time * 400, 30, { 255, 105, 180, 180 });
//
//        // Game Finishing Verify
//        int endgame_option = GameFinishingVerify(isGameFinish, result_win, result_lose_time, result_lose_life, countcell, Matrix.life, currenttime);
//
//        // Kết thúc vẽ
//        EndDrawing();
//
//        if (endgame_option == OPTION_PLAY_AGAIN)
//        {
//            Play_OPTION(boardWidth, boardLength);
//            break;
//        }
//        if (endgame_option == OPTION_BACK_TO_MENU)
//        {
//            break;
//        }
//    }
//    UnloadFont(font_name);
//    UnloadTexture(background);
//    UnloadTexture(result_win);
//    UnloadTexture(result_lose_life);
//    UnloadTexture(result_lose_time);
//    UnloadTexture(heart);
//    UnloadTexture(Bulb);
//    UnloadTexture(Setting);
//    UnloadAllCellTexture();
//}
int startsave;
// Chế độ RESUME
void Play_Save()
{
    matrix Matrix;
    startsave = GetTime();

    // Mở file lưu dữ liệu save game
    ifstream fs;
    fs.open("SaveData.txt");
    if (!fs.is_open()) return;

    // Khai báo kích thước màn hình
    const int screenWidth = 1200;
    const int screenHeight = 900;

    // Đọc dữ liệu và Cấp phát bộ nhớ cho con trỏ lưu dữ liệu của lưới ô 2 chiều
    fs >> Matrix.height;
    Matrix.width = Matrix.height;
    int boardLength = Matrix.width;
    int boardWidth = Matrix.height;
    srand(time(0));
    vector<int> ArrayRandom;
    int count = -1, countcell;
    int** c = new int* [Matrix.height + 1];
    for (int i = 0; i < Matrix.height + 2; i++)
        c[i] = new int[Matrix.height + 2];

    // Khởi tạo -1 cho tất cả giá trị
    for (int i = 0; i < Matrix.height + 2; i++) {
        for (int j = 0; j < Matrix.height + 2; j++) {
            c[i][j] = -1;
        }
    }

    // Cấp phát bộ nhớ cho matrix
    board** val = new board * [Matrix.height + 1];
    for (int i = 0; i < Matrix.height + 2; i++)
        val[i] = new board[Matrix.height + 2];

    // Khởi tạo biến matrix
    Matrix.val = val;
    fs >> Matrix.life >> Matrix.score >> Matrix.time;
    float currenttime = Matrix.time;
    int tmp = Matrix.life;
    // Lưu các chỉ số được đảo ngẫu nhiên vào một mảng hai chiều kiểu nguyên
    for (int i = 1; i <= Matrix.height; i++)
        for (int j = 1; j <= Matrix.width; j++)
            fs >> c[i][j];



    // Lấy background và các hình trang trí
    SetWindowTitle("Pikachu - PlayBoard");
    Texture2D background = LoadTexture("BACKground.png");
    Texture2D result_win = LoadTexture("Result_Win.png");
    Texture2D result_lose_time = LoadTexture("Result_TimeRanOut.png");
    Texture2D result_lose_life = LoadTexture("Result_OutOfLives.png");
    Texture2D heart = LoadTexture("heart.png");
    Texture2D Bulb = LoadTexture("Bulb.png");
    Texture2D Setting = LoadTexture("Setting.png");
    Texture2D Settingboard = LoadTexture("Settingboard.png");

    //Texture2D 
    int heartX = 195;
    int heartY = 82;
    int fontSize = 50;
    int setting_option = 0;
    Font font = GetFontDefault();
    Font font_name = LoadFont("Roboto.ttf");
    char s[4];
    Rectangle recBulb = { 750, 380, 125, 125 };
    Rectangle recSetting = { 900, 380, 120, 120 };

    // Khởi tạo Textures cho các Cell
    arrangeCellID();
    LoadNCellTexture(countDistinctCell(c, Matrix.height, Matrix.width));
    countcell = countCellOccurrences(c, Matrix.height, Matrix.width);

    bool isGameFinish = false;
    // Khởi tạo cửa sổ chơi
    while (!WindowShouldClose())
    {
        // Chơi nhạc
        StopSound(sound_BackgroundMenu);
        if (!IsSoundPlaying(sound_BackgroundPlay)) PlaySound(sound_BackgroundPlay);

        // Vẽ background
        BeginDrawing();
        DrawTexturePro(background, { 0, 0, float(background.width), float(background.height) }, { 0, 0, 1200, 900 }, { 0, 0 }, 0, RAYWHITE);

        // Vẽ button gợi ý và option in game
        DrawTexturePro(Bulb, { 0, 0, float(Bulb.width), float(Bulb.height) }, { 750, 380, 125, 125 }, { 0, 0 }, 0, RAYWHITE);
        DrawTexturePro(Setting, { 0, 0, float(Setting.width), float(Setting.height) }, { 900, 380, 120, 120 }, { 0, 0 }, 0, RAYWHITE);


        // Màn có độ khó N*N thì sẽ được cung cấp N/2 mạng sống
        for (int i = 0; i < Matrix.life; i++)
            DrawTexturePro(heart, { 0, 0, float(heart.width), float(heart.height) }, { float(heartX + 50 * i), float(heartY), 60, 60 }, { 0, 0 }, 0, RAYWHITE);
        for (int i = tmp - 1; i >= Matrix.life; i--)
            DrawTexturePro(heart, { 0, 0, float(heart.width), float(heart.height) }, { float(heartX + 50 * i), float(heartY), 60, 60 }, { 0, 0 }, 0, BLACK);

        // Hiển thị tên người chơi
        DrawTextEx(font, User.username.c_str(), { 910, 548 }, fontSize, 2, BLACK);

        // Hiển thị sự thay đổi của điểm số
        _itoa_s(Matrix.score, s, 10);
        DrawTextEx(font, s, { 910, 675 }, fontSize, 2, BLACK);

        // Vẽ lưới
        Paint_Broad(c, boardLength, boardWidth, Matrix);
        if (!isGameFinish) PickCell(c, boardLength, boardWidth, countcell, Matrix);
        if (!isGameFinish) PickOption(c, recBulb, recSetting, Matrix, Bulb, Setting, countcell, choice);
        if (choice == 1)
        {
            setting_option = GameSetting(Settingboard);
            if (setting_option == OPTION_PLAY_AGAIN)
            {
                choice = 0;
                Play_OPTION(boardWidth, boardLength);
                break;
            }
            if (setting_option == OPTION_BACK_TO_MENU)
            {
                choice = 0;
                break;
            }
            if (setting_option == OPTION_SAVE_GAME)
            {
                SaveGame(Matrix, c);
                choice = 0;
                break;
            }
        }

        // Cập nhật thời gian và vẽ thanh thời gian
        if (!isGameFinish) currenttime = Matrix.time - (GetTime() - startsave);
        DrawRectangle(225, 150, 410, 40, Fade(LIGHTGRAY, 200));
        DrawRectangle(230, 155, 400, 30, RAYWHITE);
        DrawRectangle(230, 155, currenttime / Matrix.time * 400, 30, { 255, 105, 180, 180 });

        // Game Finishing Verify
        int endgame_option = GameFinishingVerify(isGameFinish, result_win, result_lose_time, result_lose_life, countcell, Matrix.life, currenttime);
        // Kết thúc vẽ
        EndDrawing();
        if (endgame_option == OPTION_PLAY_AGAIN)
        {
            Play_OPTION(boardWidth, boardLength);
            break;
        }
        if (endgame_option == OPTION_BACK_TO_MENU)
        {
            break;
        }
    }
    UnloadFont(font_name);
    UnloadTexture(background);
    UnloadTexture(result_win);
    UnloadTexture(result_lose_life);
    UnloadTexture(result_lose_time);
    UnloadTexture(heart);
    UnloadTexture(Bulb);
    UnloadTexture(Setting);
    UnloadTexture(Settingboard);
    UnloadAllCellTexture();
}