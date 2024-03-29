#include <iostream>
#include "struct.h"
#include "soundlib.h"
#include "raylib.h"
#include <algorithm>
#include <vector>
#include <random>

using namespace std;
const int Width = 1200;
const int Height = 900;

Sound sound_BackgroundMenu;
Sound sound_BackgroundPlay;
Sound sound_Correct;
Sound sound_Wrong;
Sound sound_ClickOnButton;
Sound sound_ClickOnCell;

int main()
{
    InitAudioDevice();
    LoadAllSound();
    SetAllSoundVolume();
    PlaySound(sound_BackgroundMenu);
    PlaySound(sound_Correct);

    LoginWindow();
    /* Những phần Hà code Âu đã chuyển vào hàm void Play_OPTION(int boardWidth, int boardLength) trong PLAY.cpp nha
    * Trong hàm Âu có để 2 tham số boardWidth với boardLength là kích thước ma trận, có gì Hà chỉnh code để ma trận linh hoạt thay đổi kích thước
    * Với cái int c[][12] Hà chỉnh lại thành int** c rồi cấp phát kích thước nha do thầy kêu đồ án này quan trọng con trỏ
    */
    UnloadAllSound();
    CloseAudioDevice();
    return 0;
}

// Au sua 123