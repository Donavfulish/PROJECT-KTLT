#include <iostream>
#include "soundlib.h"
#include "struct.h"

#define NORMAL_MODE 0
#define ADVANCED_MODE 1
#define OPTION_NEXT_LEVEL 1
#define OPTION_PLAY_AGAIN 2
#define OPTION_BACK_TO_MENU 3

// Hàm tạo chế độ chơi Tournament
void Play_TOURNAMENT(int mode)
{
	if (mode == NORMAL_MODE)
	{
		while (!WindowShouldClose())
		{
			float playTime = 600;
			float currenttime = playTime;
			int lives = 10;
			int lives_left = lives;
			int score = 0;
			int endgame_option;
			if ((endgame_option = Play_TOURNAMENT_NORMAL(playTime, currenttime, score, lives, lives_left, 4, 4)) == OPTION_NEXT_LEVEL)
			{
				if ((endgame_option = Play_TOURNAMENT_NORMAL(playTime, currenttime, score, lives, lives_left, 6, 6)) == OPTION_NEXT_LEVEL)
				{
					if ((endgame_option = Play_TOURNAMENT_NORMAL(playTime, currenttime, score, lives, lives_left, 8, 8)) == OPTION_NEXT_LEVEL)
					{
						endgame_option = Play_TOURNAMENT_NORMAL(playTime, currenttime, score, lives, lives_left, 10, 10);
					}
				}
			}
			if (endgame_option == OPTION_PLAY_AGAIN) continue;
			if (endgame_option == OPTION_BACK_TO_MENU) break;
		}
	}
	else if (mode == ADVANCED_MODE)
	{
		while (!WindowShouldClose())
		{
			float playTime = 600;
			float currenttime = playTime;
			int lives = 10;
			int lives_left = lives;
			int score = 0;
			int endgame_option;
			if ((endgame_option = Play_TOURNAMENT_ADVANCED(playTime, currenttime, score, lives, lives_left, 4, 4)) == OPTION_NEXT_LEVEL)
			{
				if ((endgame_option = Play_TOURNAMENT_ADVANCED(playTime, currenttime, score, lives, lives_left, 6, 6)) == OPTION_NEXT_LEVEL)
				{
					if ((endgame_option = Play_TOURNAMENT_ADVANCED(playTime, currenttime, score, lives, lives_left, 8, 8)) == OPTION_NEXT_LEVEL)
					{
						endgame_option = Play_TOURNAMENT_ADVANCED(playTime, currenttime, score, lives, lives_left, 10, 10);
					}
				}
			}
			if (endgame_option == OPTION_PLAY_AGAIN) continue;
			if (endgame_option == OPTION_BACK_TO_MENU) break;
		}
	}
}