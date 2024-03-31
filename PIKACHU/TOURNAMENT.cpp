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
			float runningtime = playTime;
			int lives = 10;
			int lives_left = lives;
			int score = 0;
			int endgame_option;
			if ((endgame_option = Play_TOURNAMENT_NORMAL(playTime, runningtime, score, lives, lives_left, 4)) == OPTION_NEXT_LEVEL)
			{
				if ((endgame_option = Play_TOURNAMENT_NORMAL(playTime, runningtime, score, lives, lives_left, 6)) == OPTION_NEXT_LEVEL)
				{
					if ((endgame_option = Play_TOURNAMENT_NORMAL(playTime, runningtime, score, lives, lives_left, 8)) == OPTION_NEXT_LEVEL)
					{
						endgame_option = Play_TOURNAMENT_NORMAL(playTime, runningtime, score, lives, lives_left, 10);
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
			float runningtime = playTime;
			int lives = 10;
			int lives_left = lives;
			int score = 0;
			int endgame_option;
			if ((endgame_option = Play_TOURNAMENT_ADVANCED(playTime, runningtime, score, lives, lives_left, 4)) == OPTION_NEXT_LEVEL)
			{
				if ((endgame_option = Play_TOURNAMENT_ADVANCED(playTime, runningtime, score, lives, lives_left, 6)) == OPTION_NEXT_LEVEL)
				{
					if ((endgame_option = Play_TOURNAMENT_ADVANCED(playTime, runningtime, score, lives, lives_left, 8)) == OPTION_NEXT_LEVEL)
					{
						endgame_option = Play_TOURNAMENT_ADVANCED(playTime, runningtime, score, lives, lives_left, 10);
					}
				}
			}
			if (endgame_option == OPTION_PLAY_AGAIN) continue;
			if (endgame_option == OPTION_BACK_TO_MENU) break;
		}
	}
}

void resumeGame_Tournament(int mode, int** c, matrix Matrix, float playTime, float& currenttime, int& score, int lives, int& lives_left)
{
	if (mode == 3) mode = NORMAL_MODE;
	else if (mode == 4) mode = ADVANCED_MODE;

	int currentLevel = Matrix.size + 2;
	int endgame_option = OPTION_PLAY_AGAIN;
	endgame_option = Save_Mode3(c, Matrix, playTime, currenttime, score, lives, lives_left);
	if (endgame_option == OPTION_BACK_TO_MENU) return;

	if (mode == NORMAL_MODE)
	{
		while (!WindowShouldClose())
		{
			if (currentLevel == 0)
			{
				playTime = 600;
				currenttime = 600;
				score = 0;
				lives = 10;
				lives_left = 10;
			}
			if (currentLevel > 4 || (endgame_option = Play_TOURNAMENT_NORMAL(playTime, currenttime, score, lives, lives_left, 4)) == OPTION_NEXT_LEVEL)
			{
				if (currentLevel == 4) currentLevel = 0;
				if (currentLevel > 6 || (endgame_option = Play_TOURNAMENT_NORMAL(playTime, currenttime, score, lives, lives_left, 6)) == OPTION_NEXT_LEVEL)
				{
					if (currentLevel == 6) currentLevel = 0;
					if (currentLevel > 8 || (endgame_option = Play_TOURNAMENT_NORMAL(playTime, currenttime, score, lives, lives_left, 8)) == OPTION_NEXT_LEVEL)
					{
						if (currentLevel == 8) currentLevel = 0;
						if (currentLevel > 10 || (endgame_option = Play_TOURNAMENT_NORMAL(playTime, currenttime, score, lives, lives_left, 10) == OPTION_NEXT_LEVEL))
						{
							currentLevel = 0;
						}
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
			if (currentLevel == 0)
			{
				playTime = 600;
				currenttime = 600;
				score = 0;
				lives = 10;
				lives_left = 10;
			}
			if (currentLevel > 4 || (endgame_option = Play_TOURNAMENT_ADVANCED(playTime, currenttime, score, lives, lives_left, 4)) == OPTION_NEXT_LEVEL)
			{
				if (currentLevel == 4) currentLevel = 0;
				if (currentLevel > 6 || (endgame_option = Play_TOURNAMENT_ADVANCED(playTime, currenttime, score, lives, lives_left, 6)) == OPTION_NEXT_LEVEL)
				{
					if (currentLevel == 6) currentLevel = 0;
					if (currentLevel > 8 || (endgame_option = Play_TOURNAMENT_ADVANCED(playTime, currenttime, score, lives, lives_left, 8)) == OPTION_NEXT_LEVEL)
					{
						if (currentLevel == 8) currentLevel = 0;
						if (currentLevel > 10 || (endgame_option = Play_TOURNAMENT_ADVANCED(playTime, currenttime, score, lives, lives_left, 10) == OPTION_NEXT_LEVEL))
						{
							currentLevel = 0;
						}
					}
				}
			}
			if (endgame_option == OPTION_PLAY_AGAIN) continue;
			if (endgame_option == OPTION_BACK_TO_MENU) break;
		}
	}
}