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

Account User;

int main()
{
    InitAudioDevice();
    LoadAllSound();
    SetAllSoundVolume();
    PlaySound(sound_BackgroundMenu);
    PlaySound(sound_Correct);

    LoginWindow();
    UnloadAllSound();
    CloseAudioDevice();
    return 0;
}