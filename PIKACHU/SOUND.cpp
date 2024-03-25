#include <iostream>
#include <raylib.h>
#include "soundlib.h"

using namespace std;

void LoadAllSound()
{
	sound_BackgroundMenu = LoadSound("Sound\\BackgroundMusic_Menu.wav");
	sound_BackgroundPlay = LoadSound("Sound\\BackgroundMusic_Play.mp3");
	sound_Correct = LoadSound("Sound\\Correct.mp3");
	sound_Wrong = LoadSound("Sound\\Wrong.mp3");
	sound_ClickOnButton = LoadSound("Sound\\ClickOnButton.mp3");
	sound_ClickOnCell = LoadSound("Sound\\ClickOnCell.mp3");
}

void SetAllSoundVolume()
{
	SetSoundVolume(sound_BackgroundMenu, 0.3);
	SetSoundVolume(sound_BackgroundPlay, 0.3);
	SetSoundVolume(sound_Correct, 0.8);
	SetSoundVolume(sound_Wrong, 1.0);
	SetSoundVolume(sound_ClickOnButton, 1.0);
	SetSoundVolume(sound_ClickOnCell, 0.8);
}

void UnloadAllSound()
{
	UnloadSound(sound_BackgroundMenu);
	UnloadSound(sound_BackgroundPlay);
	UnloadSound(sound_ClickOnButton);
	UnloadSound(sound_ClickOnCell);
	UnloadSound(sound_Correct);
	UnloadSound(sound_Wrong);
}