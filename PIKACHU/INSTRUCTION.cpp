#include <iostream>
#include "struct.h"
#include "soundlib.h"

using namespace std;
#define SECTION_GAME_RULE 0
#define SECTION_PLAY_MODE 1
#define SECTION_PLAY_OPTION 2
#define SECTION_PLAY_FUNCTIONALITIES 3
#define PREV_PAGE 1
#define NEXT_PAGE 2
// Khai báo mảng các textures cho các sections trong instruction (số lượng phần tử khai báo là số trang của từng section trong instruction)
Texture2D GameRule[4];
Texture2D PlayMode[3];
Texture2D PlayOption[4];
Texture2D Functionalities[5];

// Biến lưu số page của từng section
int sectionPage[] = { 4, 3, 4, 5 };

// Lưu tọa độ tâm của các nút tròn và bán kính nút tròn
Vector2 prevPage = { 410.15, 810 };
Vector2 nextPage = { 789.85, 810 };
float radius = 46.625f;

// Hàm lấy dữ liệu tất cả texture từ máy tính cho các sections
void Instruction_LoadAllTexture()
{
	// Load all textures cho section Game Rule
	GameRule[0] = LoadTexture("Instruction\\Instruction_1.1.png");
	GameRule[1] = LoadTexture("Instruction\\Instruction_1.2.png");
	GameRule[2] = LoadTexture("Instruction\\Instruction_1.3.png");
	GameRule[3] = LoadTexture("Instruction\\Instruction_1.4.png");

	// Load all textures cho section Play Mode
	PlayMode[0] = LoadTexture("Instruction\\Instruction_2.1.png");
	PlayMode[1] = LoadTexture("Instruction\\Instruction_2.2.png");
	PlayMode[2] = LoadTexture("Instruction\\Instruction_2.3.png");

	// Load all textures cho section Play Option
	PlayOption[0] = LoadTexture("Instruction\\Instruction_3.1.png");
	PlayOption[1] = LoadTexture("Instruction\\Instruction_3.2.png");
	PlayOption[2] = LoadTexture("Instruction\\Instruction_3.3.png");
	PlayOption[3] = LoadTexture("Instruction\\Instruction_3.4.png");

	// Load all textures cho section In-game Functionalities
	Functionalities[0] = LoadTexture("Instruction\\Instruction_4.1.png");
	Functionalities[1] = LoadTexture("Instruction\\Instruction_4.2.png");
	Functionalities[2] = LoadTexture("Instruction\\Instruction_4.3.png");
	Functionalities[3] = LoadTexture("Instruction\\Instruction_4.4.png");
	Functionalities[4] = LoadTexture("Instruction\\Instruction_4.5.png");
}

void Instruction_UnloadAllTexture()
{
	// Unload all textures cho section Game Rule
	for (int i = 0; i < sectionPage[SECTION_GAME_RULE]; i++)
		UnloadTexture(GameRule[i]);

	// Unload all textures cho section Play Mode
	for (int i = 0; i < sectionPage[SECTION_PLAY_MODE]; i++)
		UnloadTexture(PlayMode[i]);

	// Unload all textures cho section Play Mode
	for (int i = 0; i < sectionPage[SECTION_PLAY_OPTION]; i++)
		UnloadTexture(PlayOption[i]);

	// Unload all textures cho section Play Mode
	for (int i = 0; i < sectionPage[SECTION_PLAY_FUNCTIONALITIES]; i++)
		UnloadTexture(Functionalities[i]);
}

int pagebuttonPressed(int& page)
{
	if (CheckCollisionPointCircle(GetMousePosition(), prevPage, radius))
	{
		DrawCircleV(prevPage, radius, Fade(GREEN, 0.5f));
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{
			PlaySound(sound_ClickOnButton);
			page--;
			return PREV_PAGE;
		}
	}

	else if (CheckCollisionPointCircle(GetMousePosition(), nextPage, radius))
	{
		DrawCircleV(nextPage, radius, Fade(GREEN, 0.5f));
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{
			PlaySound(sound_ClickOnButton);
			page++;
			return NEXT_PAGE;
		}
	}

	return 0;
}

void change(int& section, int& page)
{
	if (page < 0)
	{
		if (section != 0) section--;
		else section = 3;
		page = sectionPage[section] - 1;
	}
	else if (page >= sectionPage[section])
	{
		if (section != 3) section++;
		else section = 0;
		page = 0;
	}
}

bool isBackButtonPressed()
{
	Rectangle rect = { 1064.4, 21.9, 112.1, 46.2 };
	if (CheckCollisionPointRec(GetMousePosition(), rect))
	{
		DrawRectangleRec(rect, Fade(GREEN, 0.5f));
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{
			PlaySound(sound_ClickOnButton);
			return true;
		}
	}

	return false;
}

void sectionSelect(int& section, int& page)
{
	// Khai báo vùng các nút section
	Rectangle rect_section[4] =
	{
		{164.4, 186.9, 192.8, 70.3},
		{353.3, 186.9, 192.8, 70.3},
		{542.1, 186.9, 192.8, 70.3},
		{730.9, 186.9, 304.6, 70.3}
	};

	for (int i = 0; i < 4; i++)
	{
		if (i == section) continue;
		if (CheckCollisionPointRec(GetMousePosition(), rect_section[i]))
		{
			DrawRectangleRec(rect_section[i], Fade(GREEN, 0.5f));
			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
			{
				PlaySound(sound_ClickOnButton);
				section = i;
				page = 0;
				return;
			}
		}
	}
}

void Instruction()
{
	Instruction_LoadAllTexture();
	SetWindowTitle("Pikachu - Instruction");

	int section = SECTION_GAME_RULE; // Biến lưu section hiện tại
	int page = 0; // Biến lưu số trang hiện tại

	// Vòng lặp chính
	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);
		// Nếu section hiện tại là Play Rule
		if (section == SECTION_GAME_RULE)
		{
			DrawTexture(GameRule[page], 0, 0, WHITE);
		}

		else if (section == SECTION_PLAY_MODE)
		{
			DrawTexture(PlayMode[page], 0, 0, WHITE);
		}

		else if (section == SECTION_PLAY_OPTION)
		{
			DrawTexture(PlayOption[page], 0, 0, WHITE);
		}

		else if (section == SECTION_PLAY_FUNCTIONALITIES)
		{
			DrawTexture(Functionalities[page], 0, 0, WHITE);
		}

		pagebuttonPressed(page);
		sectionSelect(section, page);
		bool shouldBack = isBackButtonPressed();

		EndDrawing();

		change(section, page);
		if (shouldBack) break;
	}
	Instruction_UnloadAllTexture();
}