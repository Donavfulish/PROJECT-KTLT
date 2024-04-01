#include <iostream>
#include <fstream>
#include "raylib.h"
#include "Struct.h"
#include "soundlib.h"

using namespace std;
#define OPTION_PLAY_AGAIN 1
#define OPTION_BACK_TO_MENU 2
#define OPTION_SAVE_GAME 3

int startsave;
// Ghi dữ liệu
void SaveGame(matrix Matrix, int** c, int mode)
{
    ofstream fs;
    fs.open("SaveData.txt", std::ios::out);
    if (!fs.is_open()) return;
    else
    {
        fs << mode << "\n";
        fs << Matrix.size << "\n";
        fs << Matrix.life << " " << Matrix.death << " " << Matrix.score << " " << int(Matrix.time) << "\n";
        for (int i = 1; i <= Matrix.size; i++)
        {
            for (int j = 1; j <= Matrix.size; j++)
            {
                fs << c[i][j] << " ";
            }
            fs << "\n";
        }
        //f << ;
    }
    fs.close();
}


// Đọc dữ liệu
void Play_Save()
{
    matrix Matrix;
    // Mở file lưu dữ liệu save game và đọc các dữ liệu
    ifstream fs;
    fs.open("SaveData.txt");
    if (!fs.is_open()) return;

    // Đọc dữ liệu
    const int screenWidth = 1200;
    const int screenHeight = 900;
    int mode;
    fs >> mode;
    fs >> Matrix.size;
    fs >> Matrix.life >> Matrix.death >> Matrix.score >> Matrix.time;
    int size = Matrix.size;

    // Cấp phát bộ nhớ cho con trỏ lưu dữ liệu của lưới ô 2 chiều
    srand(time(0));
    vector<int> ArrayRandom;
    int** c = new int* [size + 1];
    for (int i = 0; i < size + 2; i++)
        c[i] = new int[size + 2];

    // Khởi tạo -1 cho tất cả giá trị để phục vụ thuật toán
    for (int i = 0; i < size + 2; i++) {
        for (int j = 0; j < size + 2; j++) {
            c[i][j] = -1;
        }
    }

    // Lưu các chỉ số trong file dữ liệu vào con trỏ hai chiều
    for (int i = 1; i <= size; i++)
        for (int j = 1; j <= size; j++)
            fs >> c[i][j];

    // Chơi theo từng chế độ
    if (mode == 1)
        Save_Mode1(c, Matrix);
    else if (mode == 2)
        Save_Mode2(c, Matrix);

}

// Resume Normal
void Save_Mode1(int** c, matrix Matrix)
{
    startsave = GetTime();
    int size = Matrix.size;
    float currenttime = size * size * 3;
    float SubTime = Matrix.time;

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
    int choiceoption = 0;
    int count = -1, countcell;
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

        // Vẽ lưới
        Paint_Broad(c, size, Matrix);
        if (!isGameFinish) PickCell(c, size, countcell, Matrix);
        if (!isGameFinish) PickOption(c, recBulb, recSetting, Matrix, Bulb, Setting, countcell, choiceoption);
        if (choiceoption == 1)
        {
            setting_option = GameSetting(Settingboard, choiceoption);
            if (setting_option == OPTION_PLAY_AGAIN)
            {
                choiceoption = 0;
                Play_OPTION(size);
                break;
            }
            if (setting_option == OPTION_BACK_TO_MENU)
            {
                choiceoption = 0;
                break;
            }
            if (setting_option == OPTION_SAVE_GAME)
            {
                SaveGame(Matrix, c, 1);
                choiceoption = 0;
                break;
            }
        }

        // Cập nhật thời gian và vẽ thanh thời gian
        if (!isGameFinish) Matrix.time = SubTime - (GetTime() - startsave);
        DrawRectangle(225, 150, 410, 40, Fade(LIGHTGRAY, 200));
        DrawRectangle(230, 155, 400, 30, RAYWHITE);
        DrawRectangle(230, 155, Matrix.time / currenttime * 400, 30, { 255, 105, 180, 180 });

        // Game Finishing Verify
        int endgame_option = GameFinishingVerify(isGameFinish, result_win, result_lose_time, result_lose_life, countcell, Matrix.life - Matrix.death, currenttime, 1, Matrix);
        // Kết thúc vẽ
        EndDrawing();
        if (endgame_option == OPTION_PLAY_AGAIN)
        {
            Play_OPTION(size);
            break;
        }
        if (endgame_option == OPTION_BACK_TO_MENU)
        {
            break;
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
    UnloadTexture(Settingboard);
    UnloadAllCellTexture();
}

// Resume Advanced
void Save_Mode2(int** c, matrix Matrix)
{
    startsave = GetTime();
    int size = Matrix.size;
    float currenttime = size * size * 3;
    float SubTime = Matrix.time;

    // Khai báo kích thước màn hình
    const int screenWidth = 1200;
    const int screenHeight = 900;

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
            addTail(list[i], c[i][j]);
        }
    }
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
    int count = -1, countcell;
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

        // Vẽ lưới
        PaintBroad_Advanced(list, c, size, Matrix);
        if (!isGameFinish) PickCell_Advanced(list, c, size, countcell, Matrix);
        if (!isGameFinish) PickOption_Advanced(list, c, recBulb, recSetting, Matrix, Bulb, Setting, countcell, choiceadvanced);
        if (choiceadvanced == 1)
        {
            setting_option = GameSetting(Settingboard, choiceadvanced);
            if (setting_option == OPTION_PLAY_AGAIN)
            {
                Play_OPTION(size);
                choiceadvanced = 0;
                break;
            }
            if (setting_option == OPTION_BACK_TO_MENU)
            {
                choiceadvanced = 0;
                break;
            }
            if (setting_option == OPTION_SAVE_GAME)
            {
                choiceadvanced = 0;
                SaveGame(Matrix, c, 2);
                break;
            }
        }
        // Cập nhật thời gian và vẽ thanh thời gian
        if (!isGameFinish) Matrix.time = SubTime - (GetTime() - startsave);
        DrawRectangle(225, 150, 410, 40, Fade(LIGHTGRAY, 200));
        DrawRectangle(230, 155, 400, 30, RAYWHITE);
        DrawRectangle(230, 155, Matrix.time / currenttime * 400, 30, { 255, 105, 180, 180 });

        // Game Finishing Verify
        int endgame_option = GameFinishingVerify(isGameFinish, result_win, result_lose_time, result_lose_life, countcell, Matrix.life - Matrix.death, currenttime, 2, Matrix);
        EndDrawing();

        if (endgame_option == OPTION_PLAY_AGAIN)
        {
            Play_OPTION_ADVANCED(size);
            break;
        }
        if (endgame_option == OPTION_BACK_TO_MENU)
        {
            break;
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