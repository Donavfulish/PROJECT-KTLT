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
#include <string>
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

#define OPTION_NEXT_LEVEL OPTION_PLAY_AGAIN

#define RCO_LEVEL_4x4 1
#define RCO_LEVEL_6x6 2
#define RCO_LEVEL_8x8 3
#define RCO_LEVEL_10x10 4

vector<int> cellID;
vector<Texture> cellTexture;
int start, choice1;

void ModeButtonPressed(Texture2D mode_normal, Texture2D mode_advanced, int& status)
{
    if (status == NORMAL_MODE)
    {
        DrawTexture(mode_normal, 182, 353.3, WHITE);
        Rectangle dest = { 309.7, 353.3, 127.7, 63.6 };
        if (CheckCollisionPointRec(GetMousePosition(), dest))
        {
            Rectangle source = { 1.0f * mode_normal.width / 2, 0, 1.0f * mode_normal.width / 2, 1.0f * mode_normal.height };
            DrawTexturePro(mode_normal, source, dest, { 0, 0 }, 0, Fade(ORANGE, 0.5f));
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                PlaySound(sound_ClickOnButton);
                status = ADVANCED_MODE;
            }
        }
    }
    else if (status == ADVANCED_MODE)
    {
        DrawTexture(mode_advanced, 182, 353.3, WHITE);
        Rectangle dest = { 182, 353.3, 127.7, 63.6 };
        if (CheckCollisionPointRec(GetMousePosition(), dest))
        {
            Rectangle source = { 0, 0, 1.0f * mode_normal.width / 2, 1.0f * mode_normal.height };
            DrawTexturePro(mode_advanced, source, dest, { 0, 0 }, 0, Fade(YELLOW, 0.5f));
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                PlaySound(sound_ClickOnButton);
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

    // Tải texture Background từ máy tính
    Texture2D texture = LoadTexture("GameStarting_Play.png");
    Texture2D mode_normal = LoadTexture("button_mode_Normal.png");
    Texture2D mode_advanced = LoadTexture("button_mode_Advanced.png");
    int mode = NORMAL_MODE;

    // Vòng lặp chính
    while (!WindowShouldClose())
    {
        if (!IsSoundPlaying(sound_BackgroundMenu)) PlaySound(sound_BackgroundMenu);
        if (IsSoundPlaying(sound_BackgroundPlay)) StopSound(sound_BackgroundPlay);

        // Bắt đầu vẽ
        BeginDrawing();
        ClearBackground(SKYBLUE);

        // Insert Background cho Menu
        DrawTexture(texture, 0, 0, WHITE);

        ModeButtonPressed(mode_normal, mode_advanced, mode);

        // Xác định vùng diện tích của các button
        Rectangle rect_Option = { 177, 450, 264.9, 69.9 };
        Rectangle rect_Tournament = { 177, 533.9, 264.9, 69.9 };
        Rectangle rect_Exit = { 177, 617.7, 264.9, 69.9 };

        // Kiểm tra xem nếu cá nút được bấm
        if (CheckCollisionPointRec(GetMousePosition(), rect_Option))
        {
            DrawRectangleRec(rect_Option, Fade(GREEN, 0.3f));
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                PlaySound(sound_ClickOnButton);
                RightClickOn = RCO_OPTION;
            }
        }
        else if (CheckCollisionPointRec(GetMousePosition(), rect_Tournament))
        {
            DrawRectangleRec(rect_Tournament, Fade(GREEN, 0.3f));
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                PlaySound(sound_ClickOnButton);
                RightClickOn = RCO_TOURNAMENT;
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
            case RCO_OPTION:
                GameStarting_Play_Option(mode);
                break;
            case RCO_TOURNAMENT:
                Play_TOURNAMENT(mode);
                break;
            case RCO_EXIT:
                SetWindowTitle("Pikachu Menu");
                WantToExit = true;
                break;
            }
        }
        
        RightClickOn = RCO_NONE;
        if (WantToExit) break;
#pragma endregion
    }

    // Giải phóng texture Background
    UnloadTexture(texture);
}

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
        if (IsSoundPlaying(sound_BackgroundPlay)) StopSound(sound_BackgroundPlay);

        // Bắt đầu vẽ
        BeginDrawing();
        ClearBackground(SKYBLUE);

        // Insert Background cho Menu
        DrawTexture(texture, 0, 0, WHITE);

        // Xác định vị trí các nút chọn Level
        Vector2 pos4x4 = { 76.2, 340 };
        Vector2 pos6x6 = { 351.8, 340 };
        Vector2 pos8x8 = { 627.8, 340 };
        Vector2 pos10x10 = { 903.8, 340 };

        // Xác định vùng diện tích nút Exit
        Rectangle rect_Back = { 490, 810, 220, 60.3 };

        // Vẽ các button chọn Level
        DrawTextureV(Texture_Option_4x4, pos4x4, WHITE);
        DrawTextureV(Texture_Option_6x6, pos6x6, WHITE);
        DrawTextureV(Texture_Option_8x8, pos8x8, WHITE);
        DrawTextureV(Texture_Option_10x10, pos10x10, WHITE);

        // Kiểm tra vị trí chuột và button chuột click vào
        if (CheckCollisionPointRec(GetMousePosition(), { pos4x4.x, pos4x4.y, 220, 220 }))
        {
            DrawTextureV(Texture_Option_4x4, pos4x4, Fade(GREEN, 0.5f));
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                PlaySound(sound_ClickOnButton);
                RightClickOn = RCO_LEVEL_4x4;
            }
        }
        else if (CheckCollisionPointRec(GetMousePosition(), { pos6x6.x, pos6x6.y, 220, 220 }))
        {
            DrawTextureV(Texture_Option_6x6, pos6x6, Fade(GREEN, 0.5f));
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                PlaySound(sound_ClickOnButton);
                RightClickOn = RCO_LEVEL_6x6;
            }
        }
        else if (CheckCollisionPointRec(GetMousePosition(), { pos8x8.x, pos8x8.y, 220, 220 }))
        {
            DrawTextureV(Texture_Option_8x8, pos8x8, Fade(GREEN, 0.5f));
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                PlaySound(sound_ClickOnButton);
                RightClickOn = RCO_LEVEL_8x8;
            }
        }
        else if (CheckCollisionPointRec(GetMousePosition(), { pos10x10.x, pos10x10.y, 220, 220 }))
        {
            DrawTextureV(Texture_Option_10x10, pos10x10, Fade(GREEN, 0.5f));
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                PlaySound(sound_ClickOnButton);
                RightClickOn = RCO_LEVEL_10x10;
            }
        }
        else if (CheckCollisionPointRec(GetMousePosition(), rect_Back))
        {
            DrawRectangleRec(rect_Back, Fade(GREEN, 0.3f));
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
            case RCO_LEVEL_4x4:
                if (mode == NORMAL_MODE) Play_OPTION(4);
                else Play_OPTION_ADVANCED(4);
                break;
            case RCO_LEVEL_6x6:
                if (mode == NORMAL_MODE) Play_OPTION(6);
                else Play_OPTION_ADVANCED(6);
                break;
            case RCO_LEVEL_8x8:
                if (mode == NORMAL_MODE) Play_OPTION(8);
                else Play_OPTION_ADVANCED(8);
                break;
            case RCO_LEVEL_10x10:
                if (mode == NORMAL_MODE) Play_OPTION(10);
                else Play_OPTION_ADVANCED(10);
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

// Hàm hiển thị cửa sổ chơi và thực thi quá trình chơi
void Play_OPTION(int size)
{
    start = GetTime();
    // Khai báo kích thước màn hình
    const int screenWidth = 1200;
    const int screenHeight = 900;

    // Cấp phát bộ nhớ cho con trỏ lưu dữ liệu của lưới ô 2 chiều
    srand(time(0));
    vector<int> ArrayRandom;
    int count = -1, countcell;
    int** c = new int* [size + 1];
    for (int i = 0; i < size + 2; i++)
        c[i] = new int[size + 2];

    // Khởi tạo -1 cho tất cả giá trị
    for (int i = 0; i < size + 2; i++) {
        for (int j = 0; j < size + 2; j++) {
            c[i][j] = -1;
        }
    }

    // Khởi tạo vector ngẫu nhiên các chỉ số nguyên tượng trưng cho mỗi chữ cái sau đó đảo thứ tự ngẫu nhiên
    int value = -1; // Value
    int occ = 6; // Occurrences: Biến lưu số lần xuất hiện tối đa của một ô (phải là số chẵn)
    int cur = 0; // Current: Biến đếm xem ô đang duyệt là ô thứ mấy
    for (int i = 1; i <= size; i++)
    {
        for (int j = 1; j <= size; j++)
        {
            if (cur++ % occ == 0) value++; // Nếu <occ> ô liên tiếp có giá trị giống nhau (là val) thì val tăng lên 1 
            ArrayRandom.push_back(value);
        }
    }
    shuffle(ArrayRandom.begin(), ArrayRandom.end(), default_random_engine(time(nullptr)));

    // Lưu các chỉ số được đảo ngẫu nhiên vào một mảng hai chiều kiểu nguyên
    for (int i = 1; i <= size; i++)
        for (int j = 1; j <= size; j++)
            c[i][j] = ArrayRandom[++count];

    // Khởi tạo biến matrix
    matrix Matrix;
    Matrix.life = size/ 2;
    Matrix.death = 0;
    Matrix.size = size;
    Matrix.score = 0;
    Matrix.time = size * size * 3;
    float currenttime = Matrix.time;
    float penaltyTime = 0; // Mỗi lần sử dụng Move Suggestion: penaltyTime tăng lên 5 giây


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
    char s[4];
    Rectangle recBulb = { 750, 380, 125, 125 };
    Rectangle recSetting = { 900, 380, 120, 120 };

    // Khởi tạo Textures cho các Cell
    arrangeCellID();
    LoadNCellTexture(countDistinctCell(c, Matrix.size));
    countcell = countCellOccurrences(c, Matrix.size);
    int choiceoption = 0;
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
        for (int i = Matrix.life - 1; i >= Matrix.life - Matrix.death; i--)
            DrawTexturePro(heart, { 0, 0, float(heart.width), float(heart.height) }, { float(heartX + 50 * i), float(heartY), 60, 60 }, { 0, 0 }, 0, BLACK);

        // Hiển thị tên người chơi
        DrawTextEx(font, User.username.c_str(), { 910, 548 }, fontSize, 2, BLACK);

        // Hiển thị sự thay đổi của điểm số
        _itoa_s(Matrix.score, s, 10);
        DrawTextEx(font, s, { 910, 675 }, fontSize, 2, BLACK);
        
        // Biến lưu số cell còn lại trước khi người chơi chọn pair tiếp theo
        int prev_countCell = countcell;

        // Vẽ lưới
        Paint_Broad(c, size, Matrix);
        if (choiceoption == 0 && !isGameFinish) PickCell(c, size, countcell, Matrix);
        if (choiceoption == 0 && !isGameFinish) PickOption(c, recBulb, recSetting, Matrix, Bulb, Setting, countcell, choiceoption, penaltyTime);
        
        if (choiceoption == 1)
        {
            setting_option = GameSetting(Settingboard, choiceoption);
            if (setting_option != 0) choiceoption = 0;
        }
        
        // Cập nhật thời gian và vẽ thanh thời gian
        if (!isGameFinish) Matrix.time = currenttime - (GetTime() - start - penaltyTime);
        DrawRectangle(225, 150, 410, 40, Fade(LIGHTGRAY, 200));
        DrawRectangle(230, 155, 400, 30, RAYWHITE);
        DrawRectangle(230, 155, Matrix.time/currenttime * 400, 30, { 255, 105, 180, 180 });

        // Game Finishing Verify
        int endgame_option = GameFinishingVerify(isGameFinish, result_win, result_lose_time, result_lose_life, countcell, Matrix.life - Matrix.death, Matrix.time, currenttime, Matrix.score);
        // Kết thúc vẽ
        EndDrawing();

        // Nếu người chơi đã chọn 2 ô chính xác, kiểm tra xem PlayBoard còn Valid Pair không
        if (countcell != 0 && countcell != prev_countCell)
        {
            int status = -1;
            vector<Vector2> validPair = MoveSuggestion(Matrix, c, status);
            while (validPair[0].x == -1 && validPair[0].y == -1)
            {
                penaltyTime -= 10;
                shuffleMatrix(c, size);
                validPair = MoveSuggestion(Matrix, c, status);
            }
        }

        if (setting_option == 3)
        {
            SaveGame(Matrix, c, 1);
            break;
        }
        if (setting_option == OPTION_PLAY_AGAIN)
        {
            Play_OPTION(size);
            break;
        }
        if (setting_option == OPTION_BACK_TO_MENU)
        {
            break;
        }

        if (endgame_option == OPTION_PLAY_AGAIN)
        {
            if (countcell == 0)
            {
                leaderboardSaving(Matrix, 1, User.username);
                Play_OPTION(size);
                break;
            }
            else
            {
                Play_OPTION(size);
                break;
            }
        }
        if (endgame_option == OPTION_BACK_TO_MENU)
        {
            if (countcell == 0)
            {
                leaderboardSaving(Matrix, 1, User.username);
                break;
            }
            else
            {
                break;
            }
        }
    }
    StopSound(sound_BackgroundPlay);
    UnloadFont(font);
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

// Hàm hiển thị cửa sổ chơi và thực thi quá trình chơi
void Play_OPTION_ADVANCED(int size)
{
    start = GetTime();
    // Khai báo kích thước màn hình
    const int screenWidth = 1200;
    const int screenHeight = 900;

    // Cấp phát bộ nhớ cho con trỏ lưu dữ liệu của lưới ô 2 chiều
    srand(time(0));
    vector<int> ArrayRandom;
    int count = -1, countcell;
    int** c = new int* [size + 1];
    for (int i = 0; i < size + 2; i++)
        c[i] = new int[size + 2];

    // Khởi tạo -1 cho tất cả giá trị
    for (int i = 0; i < size + 2; i++) {
        for (int j = 0; j < size + 2; j++) {
            c[i][j] = -1;
        }
    }

    // Khởi tạo vector ngẫu nhiên các chỉ số nguyên tượng trưng cho mỗi chữ cái sau đó đảo thứ tự ngẫu nhiên
    int value = -1; // Value
    int occ = 6; // Occurrences: Biến lưu số lần xuất hiện tối đa của một ô (phải là số chẵn)
    int cur = 0; // Current: Biến đếm xem ô đang duyệt là ô thứ mấy
    for (int i = 1; i <= size; i++)
    {
        for (int j = 1; j <= size; j++)
        {
            if (cur++ % occ == 0) value++; // Nếu <occ> ô liên tiếp có giá trị giống nhau (là val) thì val tăng lên 1 
            ArrayRandom.push_back(value);
        }
    }
    shuffle(ArrayRandom.begin(), ArrayRandom.end(), default_random_engine(time(nullptr)));

    // Khởi tạo Linkedlist
    str_linkedList* list = new str_linkedList[size + 1];
    for (int i = 1; i <= size; i++)
    {
        list[i].width = 0;
        list[i].pHead = nullptr;
        list[i].pTail = nullptr;
    }

    // Lưu các chỉ số được đảo ngẫu nhiên vào một mảng hai chiều kiểu nguyên
    for (int i = 1; i <= size; i++)
    {
        str_node* pCurr = list[i].pHead;
        for (int j = 1; j <= size; j++)
        {
            c[i][j] = ArrayRandom[++count];
            addTail(list[i], c[i][j]);
        }
    }

    // Khởi tạo biến matrix
    matrix Matrix;
    Matrix.life = size / 2;
    Matrix.death = 0;
    Matrix.size = size;
    Matrix.score = 0;
    Matrix.time = size * size * 3;
    float currenttime = Matrix.time;
    float penaltyTime = 0; // Mỗi lần sử dụng Move Suggestion: penaltyTime tăng lên 5 giây
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
    int heartX = 195;
    int heartY = 82;
    int fontSize = 50;
    int setting_option = 0;
    int choiceadvanced = 0;
    Font font = GetFontDefault();
    Font font_name = LoadFont("Roboto.ttf");
    char s[4];
    Rectangle recBulb = { 750, 380, 125, 125 };
    Rectangle recSetting = { 900, 380, 120, 120 };

    // Khởi tạo Textures cho các Cell
    arrangeCellID();
    LoadNCellTexture(countDistinctCell(c, Matrix.size));
    countcell = countCellOccurrences(c, Matrix.size);

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
        for (int i = Matrix.life - 1; i >= Matrix.life - Matrix.death; i--)
            DrawTexturePro(heart, { 0, 0, float(heart.width), float(heart.height) }, { float(heartX + 50 * i), float(heartY), 60, 60 }, { 0, 0 }, 0, BLACK);

        // Hiển thị tên người chơi
        DrawTextEx(font, User.username.c_str(), { 910, 548 }, fontSize, 2, BLACK);

        // Hiển thị sự thay đổi của điểm số
        _itoa_s(Matrix.score, s, 10);
        DrawTextEx(font, s, { 910, 675 }, fontSize, 2, BLACK);

        // Biến lưu số ô còn lại trước khi người chơi chọn pair tiếp theo
        int prev_countCell = countcell;

        // Vẽ lưới
        PaintBroad_Advanced(list, c, size, Matrix);
        if (choiceadvanced == 0 && !isGameFinish) PickCell_Advanced(list, c, size, countcell, Matrix);
        if (choiceadvanced == 0 && !isGameFinish) PickOption_Advanced(list, c, recBulb, recSetting, Matrix, Bulb, Setting, countcell, choiceadvanced, penaltyTime);
        if (choiceadvanced == 1)
        {
            setting_option = GameSetting(Settingboard, choiceadvanced);
            if (setting_option != 0) choiceadvanced = 0;
        }
        // Cập nhật thời gian và vẽ thanh thời gian
        if (!isGameFinish) Matrix.time = currenttime - (GetTime() - start - penaltyTime);
        DrawRectangle(225, 150, 410, 40, Fade(LIGHTGRAY, 200));
        DrawRectangle(230, 155, 400, 30, RAYWHITE);
        DrawRectangle(230, 155, Matrix.time/currenttime * 400, 30, { 255, 105, 180, 180 });
        
        // Game Finishing Verify
        int endgame_option = GameFinishingVerify(isGameFinish, result_win, result_lose_time, result_lose_life, countcell, Matrix.life - Matrix.death, Matrix.time, currenttime, Matrix.score);
        EndDrawing();

        // Nếu người chơi đã chọn 2 ô chính xác, kiểm tra xem PlayBoard còn Valid Pair không
        if (countcell != 0 && countcell != prev_countCell)
        {
            int status = -1;
            vector<Vector2> validPair = MoveSuggestion(Matrix, c, status);
            while (validPair[0].x == -1 && validPair[0].y == -1)
            {
                penaltyTime -= 10;
                shuffleMatrix_Advanced(list, c, size);
                validPair = MoveSuggestion(Matrix, c, status);
            }
        }       

        if (setting_option == 3)
        {
            SaveGame(Matrix, c, 2);
            break;
        }
        if (setting_option == OPTION_PLAY_AGAIN )
        {
            Play_OPTION_ADVANCED(size);
            break;
        }
        if (setting_option == OPTION_BACK_TO_MENU )
        {
            break;
        }

        if (endgame_option == OPTION_PLAY_AGAIN)
        {
            if (countcell == 0)
            {
                leaderboardSaving(Matrix, 2, User.username);
                Play_OPTION_ADVANCED(size);
                break;
            }
            else
            {
                Play_OPTION_ADVANCED(size);
                break;
            }
        }
        if (endgame_option == OPTION_BACK_TO_MENU)
        {
            if (countcell == 0)
            {
                leaderboardSaving(Matrix, 2, User.username);
                break;
            }
            else
            {
                break;
            }
        }
    }
    StopSound(sound_BackgroundPlay);
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

// Hàm tạo cửa sổ PlayBoard cho chế độ TOURNAMENT mode NORMAL
int Play_TOURNAMENT_NORMAL(float playTime, float& runningtime, int& score, int lives, int& lives_left, int size)
{
    start = GetTime();
    // Khai báo kích thước màn hình
    const int screenWidth = 1200;
    const int screenHeight = 900;

    // Cấp phát bộ nhớ cho con trỏ lưu dữ liệu của lưới ô 2 chiều
    srand(time(0));
    vector<int> ArrayRandom;
    int count = -1, countcell;
    int** c = new int* [size + 1];
    for (int i = 0; i < size + 2; i++)
        c[i] = new int[size + 2];

    // Khởi tạo -1 cho tất cả giá trị
    for (int i = 0; i < size + 2; i++) {
        for (int j = 0; j < size + 2; j++) {
            c[i][j] = -1;
        }
    }

    // Khởi tạo vector ngẫu nhiên các chỉ số nguyên tượng trưng cho mỗi chữ cái sau đó đảo thứ tự ngẫu nhiên
    int value = -1; // Value
    int occ = 6; // Occurrences: Biến lưu số lần xuất hiện tối đa của một ô (phải là số chẵn)
    int cur = 0; // Current: Biến đếm xem ô đang duyệt là ô thứ mấy
    for (int i = 1; i <= size; i++)
    {
        for (int j = 1; j <= size; j++)
        {
            if (cur++ % occ == 0) value++; // Nếu <occ> ô liên tiếp có giá trị giống nhau (là val) thì val tăng lên 1 
            ArrayRandom.push_back(value);
        }
    }
    shuffle(ArrayRandom.begin(), ArrayRandom.end(), default_random_engine(time(nullptr)));

    // Lưu các chỉ số được đảo ngẫu nhiên vào một mảng hai chiều kiểu nguyên
    for (int i = 1; i <= size; i++)
        for (int j = 1; j <= size; j++)
            c[i][j] = ArrayRandom[++count];

    // Khởi tạo biến matrix
    matrix Matrix;
    Matrix.life = lives;
    Matrix.death = lives - lives_left;
    Matrix.size = size;
    Matrix.score = score;
    Matrix.time = runningtime;
    float SubTime = Matrix.time;
    float currenttime = playTime;
    float penaltyTime = 0; // Mỗi lần sử dụng Move Suggestion: penaltyTime tăng lên 5 giây


    // Lấy background và các hình trang trí
    SetWindowTitle("Pikachu - PlayBoard");
    Texture2D background = LoadTexture("BACKground.png");
    Texture2D result_pass;
    if (size == 10)
        result_pass = LoadTexture("Result_Win.png");
    else
        result_pass = LoadTexture("Result_Pass.png");
    Texture2D result_lose_time = LoadTexture("Result_TimeRanOut.png");
    Texture2D result_lose_life = LoadTexture("Result_OutOfLives.png");
    Texture2D heart = LoadTexture("heart.png");
    Texture2D Bulb = LoadTexture("Bulb.png");
    Texture2D Setting = LoadTexture("Setting.png");
    Texture2D Settingboard = LoadTexture("Settingboard.png");
    int heartX = 195;
    int heartY = 82;
    int fontSize = 50;
    int choiceoption = 0;
    int setting_option = 0;
    Font font = GetFontDefault();
    Font font_name = LoadFont("Roboto.ttf");
    char s[4];
    Rectangle recBulb = { 750, 380, 125, 125 };
    Rectangle recSetting = { 900, 380, 120, 120 };

    // Khởi tạo Textures cho các Cell
    arrangeCellID();
    LoadNCellTexture(countDistinctCell(c, Matrix.size));
    countcell = countCellOccurrences(c, Matrix.size);

    bool isGameFinish = false;
    int endgame_option = 0;
    int prev_endgame_option = 0;
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
        for (int i = Matrix.life - 1; i >= Matrix.life - Matrix.death; i--)
            DrawTexturePro(heart, { 0, 0, float(heart.width), float(heart.height) }, { float(heartX + 50 * i), float(heartY), 60, 60 }, { 0, 0 }, 0, BLACK);

        // Hiển thị tên người chơi
        DrawTextEx(font, User.username.c_str(), { 910, 548 }, fontSize, 2, BLACK);

        // Biến lưu số cell còn lại trước khi người chơi chọn pair tiếp theo
        int prev_countCell = countcell;

        // Hiển thị sự thay đổi của điểm số
        _itoa_s(Matrix.score, s, 10);
        DrawTextEx(font, s, { 910, 675 }, fontSize, 2, BLACK);

        // Vẽ lưới
        Paint_Broad(c, size, Matrix);
        if (choiceoption == 0 && !isGameFinish) PickCell(c, size, countcell, Matrix);
        if (choiceoption == 0 && !isGameFinish) PickOption(c, recBulb, recSetting, Matrix, Bulb, Setting, countcell, choiceoption, penaltyTime);
        if (choiceoption == 1)
        {
            setting_option = GameSetting(Settingboard, choiceoption);
            if (setting_option != 0) choiceoption = 0;
        }
        // Cập nhật thời gian và vẽ thanh thời gian
        if (!isGameFinish) Matrix.time = SubTime - (GetTime() - start - penaltyTime);
        DrawRectangle(225, 150, 410, 40, Fade(LIGHTGRAY, 200));
        DrawRectangle(230, 155, 400, 30, RAYWHITE);
        DrawRectangle(230, 155, Matrix.time / currenttime * 400, 30, { 255, 105, 180, 180 });

        // Game Finishing Verify
        endgame_option = GameFinishingVerify(isGameFinish, result_pass, result_lose_time, result_lose_life, countcell, Matrix.life, Matrix.time, currenttime, Matrix.score);

        // Kết thúc vẽ
        EndDrawing();

        // Nếu người chơi đã chọn 2 ô chính xác, kiểm tra xem PlayBoard còn Valid Pair không
        if (countcell != 0 && countcell != prev_countCell)
        {
            int status = -1;
            vector<Vector2> validPair = MoveSuggestion(Matrix, c, status);
            while (validPair[0].x == -1 && validPair[0].y == -1)
            {
                penaltyTime -= 10;
                shuffleMatrix(c, size);
                validPair = MoveSuggestion(Matrix, c, status);
            }
        }

        if (setting_option == OPTION_SAVE_GAME)
        {
            SaveGame(Matrix, c, 3);
            break;
        }
        if (prev_endgame_option == 0 && isGameFinish)
        {
            prev_endgame_option = 1;
            continue; // Câu lệnh giúp tránh trường hợp tọa độ cell cuối cùng click trùng với tọa độ của button -> vô tình kích hoạt ngay button
        }

        if (setting_option != 0 && setting_option != 4|| endgame_option == OPTION_NEXT_LEVEL || endgame_option == OPTION_PLAY_AGAIN || endgame_option == OPTION_BACK_TO_MENU)
        {
            break;
        }
    }
    UnloadFont(font_name);
    UnloadTexture(background);
    UnloadTexture(result_pass);
    UnloadTexture(result_lose_life);
    UnloadTexture(result_lose_time);
    UnloadTexture(heart);
    UnloadTexture(Bulb);
    UnloadTexture(Setting);
    UnloadAllCellTexture();

    score = Matrix.score;
    lives_left = Matrix.life - Matrix.death;
    runningtime = Matrix.time;
    if (setting_option == OPTION_BACK_TO_MENU) runningtime = 0; // Phụ check: Nếu back to menu và runningtime == 0 -> thoát ra giữa trận -> chưa thắng
    if (endgame_option == OPTION_NEXT_LEVEL && countcell == 0) return 1;
    else if (setting_option == OPTION_PLAY_AGAIN || endgame_option == OPTION_PLAY_AGAIN) return 2;
    else if (setting_option == OPTION_BACK_TO_MENU || endgame_option == OPTION_BACK_TO_MENU) return 3;
    return 3;
}

// Hàm tạo cửa sổ PlayBoard cho chế độ TOURNAMENT mode ADVANCED
int Play_TOURNAMENT_ADVANCED(float playTime, float& runningtime, int& score, int lives, int& lives_left, int size)
{
    start = GetTime();
    // Khai báo kích thước màn hình
    const int screenWidth = 1200;
    const int screenHeight = 900;

    // Cấp phát bộ nhớ cho con trỏ lưu dữ liệu của lưới ô 2 chiều
    srand(time(0));
    vector<int> ArrayRandom;
    int count = -1, countcell;
    int** c = new int* [size + 1];
    for (int i = 0; i < size + 2; i++)
        c[i] = new int[size + 2];

    // Khởi tạo -1 cho tất cả giá trị
    for (int i = 0; i < size + 2; i++) {
        for (int j = 0; j < size + 2; j++) {
            c[i][j] = -1;
        }
    }

    // Khởi tạo vector ngẫu nhiên các chỉ số nguyên tượng trưng cho mỗi chữ cái sau đó đảo thứ tự ngẫu nhiên
    int value = -1; // Value
    int occ = 6; // Occurrences: Biến lưu số lần xuất hiện tối đa của một ô (phải là số chẵn)
    int cur = 0; // Current: Biến đếm xem ô đang duyệt là ô thứ mấy
    for (int i = 1; i <= size; i++)
    {
        for (int j = 1; j <= size; j++)
        {
            if (cur++ % occ == 0) value++; // Nếu <occ> ô liên tiếp có giá trị giống nhau (là val) thì val tăng lên 1 
            ArrayRandom.push_back(value);
        }
    }
    shuffle(ArrayRandom.begin(), ArrayRandom.end(), default_random_engine(time(nullptr)));

    // Khởi tạo Linkedlist
    str_linkedList* list = new str_linkedList[size+ 1];
    for (int i = 1; i <= size; i++)
    {
        list[i].width = 0;
        list[i].pHead = nullptr;
        list[i].pTail = nullptr;
    }

    // Lưu các chỉ số được đảo ngẫu nhiên vào một mảng hai chiều kiểu nguyên
    for (int i = 1; i <= size; i++)
    {
        str_node* pCurr = list[i].pHead;
        for (int j = 1; j <= size; j++)
        {
            c[i][j] = ArrayRandom[++count];
            addTail(list[i], c[i][j]);
        }
    }

    // Khởi tạo biến matrix
    matrix Matrix;
    Matrix.life = lives;
    Matrix.death = lives - lives_left;
    Matrix.size = size;
    Matrix.score = score;
    Matrix.time = runningtime;
    float SubTime = Matrix.time;
    float currenttime = playTime;
    float penaltyTime = 0; // Mỗi lần sử dụng Move Suggestion: penaltyTime tăng lên 5 giây

    // Lấy background và các hình trang trí
    SetWindowTitle("Pikachu - PlayBoard");
    Texture2D background = LoadTexture("BACKground.png");
    Texture2D result_pass;
    if (size == 10)
        result_pass = LoadTexture("Result_Win.png");
    else
        result_pass = LoadTexture("Result_Pass.png");
    Texture2D result_lose_time = LoadTexture("Result_TimeRanOut.png");
    Texture2D result_lose_life = LoadTexture("Result_OutOfLives.png");
    Texture2D heart = LoadTexture("heart.png");
    Texture2D Bulb = LoadTexture("Bulb.png");
    Texture2D Setting = LoadTexture("Setting.png");
    Texture2D Settingboard = LoadTexture("Settingboard.png");
    int heartX = 195;
    int heartY = 82;
    int fontSize = 50;
    int choiceoption = 0;
    int setting_option = 0;
    Font font = GetFontDefault();
    Font font_name = LoadFont("Roboto.ttf");
    char s[4];
    Rectangle recBulb = { 750, 380, 125, 125 };
    Rectangle recSetting = { 900, 380, 120, 120 };

    // Khởi tạo Textures cho các Cell
    arrangeCellID();
    LoadNCellTexture(countDistinctCell(c, Matrix.size));
    countcell = countCellOccurrences(c, Matrix.size);

    bool isGameFinish = false;
    int endgame_option = 0;
    int prev_endgame_option = 0;
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
        for (int i = Matrix.life - 1; i >= Matrix.life - Matrix.death; i--)
            DrawTexturePro(heart, { 0, 0, float(heart.width), float(heart.height) }, { float(heartX + 50 * i), float(heartY), 60, 60 }, { 0, 0 }, 0, BLACK);

        // Hiển thị tên người chơi
        DrawTextEx(font, User.username.c_str(), { 910, 548 }, fontSize, 2, BLACK);

        // Hiển thị sự thay đổi của điểm số
        _itoa_s(Matrix.score, s, 10);
        DrawTextEx(font, s, { 910, 675 }, fontSize, 2, BLACK);

        // Biến lưu số ô còn lại trước khi người chơi chọn pair tiếp theo
        int prev_countCell = countcell;

        // Vẽ lưới
        PaintBroad_Advanced(list, c, size, Matrix);
        if (choiceoption == 0 && !isGameFinish) PickCell_Advanced(list, c, size, countcell, Matrix);
        if (choiceoption == 0 && !isGameFinish) PickOption_Advanced(list, c, recBulb, recSetting, Matrix, Bulb, Setting, countcell, choiceoption, penaltyTime);
        if (choiceoption == 1)
        {
            setting_option = GameSetting(Settingboard, choiceoption);
            if (setting_option != 0) choiceoption = 0;
        }
        // Cập nhật thời gian và vẽ thanh thời gian
        if (!isGameFinish) Matrix.time = SubTime - (GetTime() - start - penaltyTime);
        DrawRectangle(225, 150, 410, 40, Fade(LIGHTGRAY, 200));
        DrawRectangle(230, 155, 400, 30, RAYWHITE);
        DrawRectangle(230, 155, Matrix.time / currenttime * 400, 30, { 255, 105, 180, 180 });

        // Game Finishing Verify
        endgame_option = GameFinishingVerify(isGameFinish, result_pass, result_lose_time, result_lose_life, countcell, Matrix.life, Matrix.time, currenttime, Matrix.score);

        // Kết thúc vẽ
        EndDrawing();

        // Nếu người chơi đã chọn 2 ô chính xác, kiểm tra xem PlayBoard còn Valid Pair không
        if (countcell != 0 && countcell != prev_countCell)
        {
            int status = -1;
            vector<Vector2> validPair = MoveSuggestion(Matrix, c, status);
            while (validPair[0].x == -1 && validPair[0].y == -1)
            {
                penaltyTime -= 10;
                shuffleMatrix_Advanced(list, c, size);
                validPair = MoveSuggestion(Matrix, c, status);
            }
        }

        if (setting_option == OPTION_SAVE_GAME)
        {
            SaveGame(Matrix, c, 4);
            break;
        }
        if (prev_endgame_option == 0 && isGameFinish)
        {
            prev_endgame_option = 1;
            continue; // Câu lệnh giúp tránh trường hợp tọa độ cell cuối cùng click trùng với tọa độ của button -> vô tình kích hoạt ngay button
        }
        if (setting_option != 0 && setting_option != 4 || endgame_option == OPTION_NEXT_LEVEL || endgame_option == OPTION_PLAY_AGAIN || endgame_option == OPTION_BACK_TO_MENU)
        {
            break;
        }
    }
    UnloadFont(font_name);
    UnloadTexture(background);
    UnloadTexture(result_pass);
    UnloadTexture(result_lose_life);
    UnloadTexture(result_lose_time);
    UnloadTexture(heart);
    UnloadTexture(Bulb);
    UnloadTexture(Setting);
    UnloadAllCellTexture();

    score = Matrix.score;
    lives_left = Matrix.life - Matrix.death;
    runningtime = Matrix.time;
    if (setting_option == OPTION_BACK_TO_MENU) runningtime = 0; // Phụ check: Nếu back to menu và runningtime == 0 -> thoát ra giữa trận -> chưa thắng
    if (endgame_option == OPTION_NEXT_LEVEL && countcell == 0) return 1;
    else if (setting_option == OPTION_PLAY_AGAIN || endgame_option == OPTION_PLAY_AGAIN) return 2;
    else if (setting_option == OPTION_BACK_TO_MENU || endgame_option == OPTION_BACK_TO_MENU) return 3;
    return 3;
}

// Setting
int GameSetting(Texture2D Is, int choiceoption) // Is stand for interface setting
{
    if (choiceoption == 1)
    {
        DrawRectangle(0, 0, 1200, 900, Fade(BLACK, 0.5f));
        DrawTexturePro(Is, { 0, 0, 1.0f * Is.width, 1.0f * Is.height }, { 0, 0, 1.0f * GetScreenWidth(), 1.0f * GetScreenHeight() }, { 0, 0 }, 0, WHITE);
        Rectangle rect_PlayAgain = { 488.75, 533.25, 221.3, 40.5 };
        Rectangle rect_BackToMenu = { 488.75, 583.6, 221.3, 40.5 };
        Rectangle rect_SaveGame = { 488.75, 482.95, 221.3, 40.5 };
        Rectangle rect_Continue = { 489.3, 430.95, 221.3, 44.3 };
        if (CheckCollisionPointRec(GetMousePosition(), rect_PlayAgain))
        {
            DrawRectangleRec(rect_PlayAgain, Fade(RED, 0.5f));
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                return 1;
            }
        }
        else if (CheckCollisionPointRec(GetMousePosition(), rect_BackToMenu))
        {
            DrawRectangleRec(rect_BackToMenu, Fade(RED, 0.5f));
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                return 2;
            }
        }
        else if (CheckCollisionPointRec(GetMousePosition(), rect_SaveGame))
        {
            DrawRectangleRec(rect_SaveGame, Fade(RED, 0.5f));
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                return 3;
            }
        }
        else if (CheckCollisionPointRec(GetMousePosition(), rect_Continue))
        {
            DrawRectangleRec(rect_Continue, Fade(GREEN, 0.5f));
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                return 4; 
            }
        }
    }
    return 0;
}

// Check end game
int GameFinishingVerify(bool& isGameFinish, Texture2D win, Texture2D lose_time, Texture2D lose_life, int countcell, int life, float time, int currenttime, int score)
{
    // Nếu không còn ô nào nữa thì3 kết quả YOU WIN
    if (countcell == 0)
    {
        isGameFinish = true;
        DrawRectangle(0, 0, 1200, 900, Fade(BLACK, 0.5f));
        DrawTexturePro(win, { 0, 0, 1.0f * win.width, 1.0f * win.height }, { 0, 0, 1.0f * GetScreenWidth(), 1.0f * GetScreenHeight() }, { 0, 0 }, 0, WHITE);
        DrawText(User.username.c_str(), 555.6, 340, 40, BLACK);
        DrawText(to_string(score).c_str(), 555.6, 399.2, 40, BLACK);
        DrawText(formatTime(to_string(currenttime - time).c_str()).c_str(), 555.6, 458.4, 40, BLACK);
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

// Save to leaderboard file
void leaderboardSaving(matrix Matrix, int mode, string name)
{
    fstream fs;
    if (mode == 1)
    {
        fs.open("LeaderboardNormal.txt", std::ios::app);
        if (!fs.is_open()) return;
        int time = Matrix.size * Matrix.size * 3 - Matrix.time;
        fs << Matrix.size << " " << Matrix.score << " " << time << " " << name << "\n";
        fs.close();
        return;
    }
    if (mode == 2)
    {
        fs.open("LeaderboardAdvanced.txt", std::ios::app);
        if (!fs.is_open()) return;
        int time = Matrix.size * Matrix.size * 3 - Matrix.time;
        fs << Matrix.size << " " << Matrix.score << " " << time << " " << name << "\n";
        fs.close();
        return;
    }
    if (mode == 3)
    {
        fs.open("LeaderboardTourNormal.txt", std::ios::app);
        if (!fs.is_open()) return;
        int time = 600 - Matrix.time;
        fs << Matrix.score << " " << time << " " << name << "\n";
        fs.close();
        return;
    }
    if (mode == 4)
    {
        fs.open("LeaderboardTourAdvanced.txt", std::ios::app);
        if (!fs.is_open()) return;
        int time = 600 - Matrix.time;
        fs << Matrix.score << " " << time << " " << name << "\n";
        fs.close();
        return;
    }
}