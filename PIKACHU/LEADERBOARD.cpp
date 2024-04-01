#include <iostream>
#include "struct.h"
#include "raylib.h"
#include "soundlib.h"
#include <algorithm>
#include <vector>
#include <fstream>

using namespace std;
Rectangle rec44 = { 60, 365, 115, 115 };
Rectangle rec66 = { 190, 365, 115, 115 };
Rectangle rec88 = { 60, 495, 115, 115 };
Rectangle rec10 = { 190, 495, 115, 115 };
Rectangle recTour = { 60, 665, 245, 115 };
Rectangle recNormal = { 410, 195, 190, 57 };
Rectangle recAdvanced = { 601, 195, 190, 57 };
Rectangle recExit = { 495, 810, 210, 55 };
Vector2 name = { 510, 385 };
Vector2 score = { 805, 385 };
Vector2 wtime = { 1000, 385 };
int line = 60;

#define RCO_NONE -1
#define RCO_EXIT 0
#define OPTION4 4
#define OPTION6 6
#define OPTION8 8
#define OPTION10 10
#define TOURNAMENT 2
#define MODE_NORMAL 1
#define MODE_ADVANCED 2
int mode = RCO_NONE;
int type = RCO_NONE;
int size = 0;

vector<vector<leaderBoard>> Option(4);
vector<vector<leaderBoard>> Advanced(4);
vector<leaderBoard> Tournament;
vector<leaderBoard> TournamentAdvanced;

bool compareMyStruct(leaderBoard x, leaderBoard y) {
    // Đầu tiên, so sánh theo a
    if (x.score != y.score)
        return x.score > y.score;
    // Nếu a giống nhau, so sánh theo b
    if (x.time != y.time)
        return x.time < y.time;
    // Nếu cả a và b giống nhau, so sánh theo s
    return x.name > y.name;
}

void createLeaderboard()
{
    fstream fs;
    // leaderboard Normal
    fs.open("LeaderboardNormal");
    if (!fs.is_open())
        return;
    else
    {
        int score, time, size, tmp;
        string name;
        leaderBoard l;
        while (!fs.eof())
        {
            fs >> size >> score >> time >> name;
            l.name = name;
            l.score = score;
            l.time = time;
            Option[(size / 2) - 2].push_back(l);
            tmp = size / 2 - 2;
        }
        fs.close();
        Option[tmp].pop_back();
    }
    // leaderboard Advanced
    fs.open("LeaderboardAdvanced");
    if (!fs.is_open())
        return;
    else
    {
        int score, time, size, tmp;
        string name;
        leaderBoard l;
        while (!fs.eof())
        {
            fs >> size >> score >> time >> name;
            fs.ignore();
            l.name = name;
            l.score = score;
            l.time = time;
            Advanced[(size / 2) - 2].push_back(l);
            tmp = size / 2 - 2;
        }
        fs.close();
        Advanced[tmp].pop_back();
    }

    // leaderboard TourNormal
    fs.open("LeaderboardTourNormal");
    if (!fs.is_open())
        return;
    else
    {
        int score, time;
        string name;
        leaderBoard l;
        while (!fs.eof())
        {
            fs >> score >> time >> name;
            l.name = name;
            l.score = score;
            l.time = time;
            Tournament.push_back(l);
        }
        fs.close();
        Tournament.pop_back();
    }

    //leaderboard Advanced;
    fs.open("LeaderboardTourAdvanced");
    if (!fs.is_open())
        return;
    else
    {
        int score, time;
        string name;
        leaderBoard l;
        while (!fs.eof())
        {
            fs >> score >> time >> name;
            l.name = name;
            l.score = score;
            l.time = time;
            TournamentAdvanced.push_back(l);
        }
        fs.close();
        TournamentAdvanced.pop_back();
    }
    // Sort leaderboard

    for (int i = 0; i < 4; i++)
    {
        sort(Option[i].begin(), Option[i].end(), compareMyStruct);
        sort(Advanced[i].begin(), Advanced[i].end(), compareMyStruct);
    }

    sort(Tournament.begin(), Tournament.end(), compareMyStruct);
    sort(TournamentAdvanced.begin(), TournamentAdvanced.end(), compareMyStruct);
}
void ViewLeaderboard()
{
    Texture2D Leaderboard = LoadTexture("leaderboard.png");

    const int screenWidth = 1200;
    const int screenHeight = 900;
    SetTargetFPS(60);
    // Khởi tạo cửa sổ
    SetWindowTitle("Pikachu Leaderboard");

    while (!WindowShouldClose())
    {

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTexture(Leaderboard, 0, 0, RAYWHITE);

        // Chọn chế độ normal hoặc advanced
        if (CheckCollisionPointRec(GetMousePosition(), recNormal))
        {
            DrawRectangleRounded(recNormal, 0, 0, Fade(ORANGE, 0.8f));
            if (IsMouseButtonPressed(0))
                mode = MODE_NORMAL;
        }

        if (CheckCollisionPointRec(GetMousePosition(), recAdvanced))
        {
            DrawRectangleRounded(recAdvanced, 0, 0, Fade(ORANGE, 0.8f));
            if (IsMouseButtonPressed(0))
                mode = MODE_ADVANCED;
        }

        if (mode == MODE_NORMAL)
            DrawRectangleRounded(recNormal, 0, 0, Fade(ORANGE, 0.6f));
        else if (mode == MODE_ADVANCED)
            DrawRectangleRounded(recAdvanced, 0, 0, Fade(ORANGE, 0.6f));

        // Chọn kích cỡ lưới pokemon hoặc chế độ tournament
        if (CheckCollisionPointRec(GetMousePosition(), recTour))
        {
            DrawRectangleRounded(recTour, 0, 0, Fade(ORANGE, 0.8f));
            if (IsMouseButtonPressed(0))
                type = TOURNAMENT;
        }

        if (CheckCollisionPointRec(GetMousePosition(), rec44))
        {
            DrawRectangleRounded(rec44, 0, 0, Fade(ORANGE, 0.8f));
            if (IsMouseButtonPressed(0))
                type = OPTION4;
        }

        if (CheckCollisionPointRec(GetMousePosition(), rec66))
        {
            DrawRectangleRounded(rec66, 0, 0, Fade(ORANGE, 0.8f));
            if (IsMouseButtonPressed(0))
                type = OPTION6;
        }

        if (CheckCollisionPointRec(GetMousePosition(), rec88))
        {
            DrawRectangleRounded(rec88, 0, 0, Fade(ORANGE, 0.8f));
            if (IsMouseButtonPressed(0))
                type = OPTION8;
        }

        if (CheckCollisionPointRec(GetMousePosition(), rec10))
        {
            DrawRectangleRounded(rec10, 0, 0, Fade(ORANGE, 0.8f));
            if (IsMouseButtonPressed(0))
                type = OPTION10;
        }

        if (type == TOURNAMENT)
            DrawRectangleRounded(recTour, 0, 0, Fade(ORANGE, 0.6f));
        else if (type == OPTION4)
            DrawRectangleRounded(rec44, 0, 0, Fade(ORANGE, 0.6f));
        else if (type == OPTION6)
            DrawRectangleRounded(rec66, 0, 0, Fade(ORANGE, 0.6f));
        else if (type == OPTION8)
            DrawRectangleRounded(rec88, 0, 0, Fade(ORANGE, 0.6f));
        else if (type == OPTION10)
            DrawRectangleRounded(rec10, 0, 0, Fade(ORANGE, 0.6f));

        // Kiểm tra nếu có muốn exit

        if (CheckCollisionPointRec(GetMousePosition(), recExit))
        {
            DrawRectangleRounded(recExit, 0, 0, Fade(ORANGE, 0.8f));
            if (IsMouseButtonPressed(0))
                type = RCO_EXIT;
        }

        // In tên
        // 4x4
        if (type == OPTION4)
        {
            if (mode == MODE_NORMAL)
            {
                char s[4];
                for (int i = 0; i < 7 && i < Option[0].size(); i++)
                {
                    DrawTextEx(GetFontDefault(), Option[0][i].name.c_str(), name, 35, 1, BLACK);
                    _itoa_s(Option[0][i].score, s, 10);
                    DrawTextEx(font, s, score, 35, 1, BLACK);
                    _itoa_s(Option[0][i].time, s, 10);
                    DrawTextEx(font, s, wtime, 35, 1, BLACK);
                    name.y += line;
                    score.y += line;
                    wtime.y += line;
                }
                name.y = 385;
                score.y = 385;
                wtime.y = 385;
            }
            else
            {
                char s[4];
                for (int i = 0; i < 7 && i < Advanced[0].size() ; i++)
                    {
                        DrawTextEx(GetFontDefault(), Advanced[0][i].name.c_str(), name, 35, 1, BLACK);
                        _itoa_s(Advanced[0][i].score, s, 10);
                        DrawTextEx(font, s, score, 35, 1, BLACK);
                        _itoa_s(Advanced[0][i].time, s, 10);
                        DrawTextEx(font, s, wtime, 35, 1, BLACK);
                        name.y += line;
                        score.y += line;
                        wtime.y += line;
                    }
                name.y = 385;
                score.y = 385;
                wtime.y = 385;
            }
        }
        //6x6
        if (type == OPTION6)
        {
            if (mode == MODE_NORMAL)
            {
                char s[4];
                for (int i = 0; i < 7 && i < Option[1].size() ; i++)
                {
                    DrawTextEx(GetFontDefault(), Option[1][i].name.c_str(), name, 35, 1, BLACK);
                    _itoa_s(Option[1][i].score, s, 10);
                    DrawTextEx(font, s, score, 35, 1, BLACK);
                    _itoa_s(Option[1][i].time, s, 10);
                    DrawTextEx(font, s, wtime, 35, 1, BLACK);
                    name.y += line;
                    score.y += line;
                    wtime.y += line;
                }
                name.y = 385;
                score.y = 385;
                wtime.y = 385;
            }
            else
            {
                char s[4];
                for (int i = 0; i < 7 && i < Advanced[1].size(); i++)
                {
                    DrawTextEx(GetFontDefault(), Advanced[1][i].name.c_str(), name, 35, 1, BLACK);
                    _itoa_s(Advanced[1][i].score, s, 10);
                    DrawTextEx(font, s, score, 35, 1, BLACK);
                    _itoa_s(Advanced[1][i].time, s, 10);
                    DrawTextEx(font, s, wtime, 35, 1, BLACK);
                    name.y += line;
                    score.y += line;
                    wtime.y += line;
                }
                name.y = 385;
                score.y = 385;
                wtime.y = 385;
            }
        }

        //8x8
        if (type == OPTION8)
        {
            if (mode == MODE_NORMAL)
            {
                char s[4];
                for (int i = 0; i < 7 && i < Option[2].size(); i++)
                {
                    DrawTextEx(GetFontDefault(), Option[2][i].name.c_str(), name, 35, 1, BLACK);
                    _itoa_s(Option[2][i].score, s, 10);
                    DrawTextEx(font, s, score, 35, 1, BLACK);
                    _itoa_s(Option[2][i].time, s, 10);
                    DrawTextEx(font, s, wtime, 35, 1, BLACK);
                    name.y += line;
                    score.y += line;
                    wtime.y += line;
                }
                name.y = 385;
                score.y = 385;
                wtime.y = 385;
            }
            else
            {
                char s[4];
                for (int i = 0; i < 7 && i < Advanced[2].size(); i++)
                {
                    DrawTextEx(GetFontDefault(), Advanced[2][i].name.c_str(), name, 35, 1, BLACK);
                    _itoa_s(Advanced[2][i].score, s, 10);
                    DrawTextEx(font, s, score, 35, 1, BLACK);
                    _itoa_s(Advanced[2][i].time, s, 10);
                    DrawTextEx(font, s, wtime, 35, 1, BLACK);
                    name.y += line;
                    score.y += line;
                    wtime.y += line;
                }
                name.y = 385;
                score.y = 385;
                wtime.y = 385;
            }
        }

        //10x10
        if (type == OPTION10)
        {
            if (mode == MODE_NORMAL)
            {
                char s[4];
                for (int i = 0; i < 7 && i < Option[3].size(); i++)
                {
                    DrawTextEx(GetFontDefault(), Option[3][i].name.c_str(), name, 35, 1, BLACK);
                    _itoa_s(Option[3][i].score, s, 10);
                    DrawTextEx(font, s, score, 35, 1, BLACK);
                    _itoa_s(Option[3][i].time, s, 10);
                    DrawTextEx(font, s, wtime, 35, 1, BLACK);
                    name.y += line;
                    score.y += line;
                    wtime.y += line;
                }
                name.y = 385;
                score.y = 385;
                wtime.y = 385;
            }
            else
            {
                char s[4];
                for (int i = 0; i < 7 && i < Advanced[3].size(); i++)
                {
                    DrawTextEx(GetFontDefault(), Advanced[3][i].name.c_str(), name, 35, 1, BLACK);
                    _itoa_s(Advanced[3][i].score, s, 10);
                    DrawTextEx(font, s, score, 35, 1, BLACK);
                    _itoa_s(Advanced[3][i].time, s, 10);
                    DrawTextEx(font, s, wtime, 35, 1, BLACK);
                    name.y += line;
                    score.y += line;
                    wtime.y += line;
                }
                name.y = 385;
                score.y = 385;
                wtime.y = 385;
            }
        }

        // Tournament
        if (type == TOURNAMENT)
        {
            if (mode == MODE_NORMAL)
            {
                char s[4];
                for (int i = 0; i < 7 && i < Tournament.size(); i++)
                {
                    DrawTextEx(GetFontDefault(), Tournament[i].name.c_str(), name, 35, 1, BLACK);
                    _itoa_s(Tournament[i].score, s, 10);
                    DrawTextEx(font, s, score, 35, 1, BLACK);
                    _itoa_s(Tournament[i].time, s, 10);
                    DrawTextEx(font, s, wtime, 35, 1, BLACK);
                    name.y += line;
                    score.y += line;
                    wtime.y += line;
                }
                name.y = 385;
                score.y = 385;
                wtime.y = 385;
            }
            else
            {
                char s[4];
                for (int i = 0; i < 7 && i < TournamentAdvanced.size(); i++)
                {
                    DrawTextEx(GetFontDefault(), TournamentAdvanced[i].name.c_str(), name, 35, 1, BLACK);
                    _itoa_s(TournamentAdvanced[i].score, s, 10);
                    DrawTextEx(font, s, score, 35, 1, BLACK);
                    _itoa_s(TournamentAdvanced[i].time, s, 10);
                    DrawTextEx(font, s, wtime, 35, 1, BLACK);
                    name.y += line;
                    score.y += line;
                    wtime.y += line;
                }
                name.y = 385;
                score.y = 385;
                wtime.y = 385;
            }
        }
        EndDrawing();
        if (type == RCO_EXIT)
        {
            break;
        }
    }

}