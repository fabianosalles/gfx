#include <raylib.h>
#include <cinttypes>

#define FIRE_WIDTH 160
#define FIRE_HEIGHT 140
#define MAX_HEAT 36

uint8_t fire[FIRE_HEIGHT][FIRE_WIDTH] = { 0 };
float titleY;
const int titleFontSize = 80;
const float titleSpeed = 60.0f; // Pixels por segundo.


void InitFire()
{
	for (auto x = 0; x < FIRE_WIDTH; x++) {
		fire[FIRE_HEIGHT - 1][x] = MAX_HEAT;
	}
	
}

void InitTitle()
{
	titleY = (float)GetScreenHeight();
}

void UpdateFire()
{
	for (int y = 1; y < FIRE_HEIGHT; y++) {
		for (int x = 0; x < FIRE_WIDTH; x++) {
			int heat = fire[y][x];

			int random = GetRandomValue(0, 3);
			int cooling = random & 1;
			int targetX = x + 1 - random;

			// Faz as bordas horizontais se conectarem.
			targetX = (targetX + FIRE_WIDTH) % FIRE_WIDTH;

			int nextHeat = heat - cooling;

			fire[y - 1][targetX] = (uint8_t)(nextHeat > 0 ? nextHeat : 0);
		}
	}
}

void DrawFire()
{
	int scale = GetScreenWidth() / FIRE_WIDTH;
	int offsetY = GetScreenHeight() - FIRE_HEIGHT * scale;
	for (auto y = 0; y < FIRE_HEIGHT; y++) {
		for (auto x = 0; x < FIRE_WIDTH; x++) {
			uint8_t heat = fire[y][x];
			Color color = { 
				heat * 7, 
				heat * 2, 
				heat / 2, 
				(heat * 255 / MAX_HEAT) 
			};

			DrawRectangle(
				x * scale, 
				offsetY + y * scale,
				scale,
				scale,
				color);
		}
	}
}

void UpdateTitle()
{
	float targetY = (GetScreenHeight() - titleFontSize) / 2.0f;

	if (titleY > targetY) {
		titleY -= titleSpeed * GetFrameTime();

		// Impede que ultrapasse o centro.
		if (titleY < targetY) {
			titleY = targetY;
		}
	}
}

void DrawTitle()
{
	const char* text = "DOOM FIRE FX";
	int textWidth = MeasureText(text, titleFontSize);
	int textX = (GetScreenWidth() - textWidth) / 2;

	DrawText(text, textX, (int)titleY, titleFontSize, RED);
}

int main()
{	
	InitWindow(800, 600, "Doom Fire");
	SetTargetFPS(60);	
	InitFire();
	InitTitle();
	while (!WindowShouldClose())
	{
		UpdateFire();
		UpdateTitle();
		BeginDrawing();
		ClearBackground(BLACK);
		
		DrawTitle();
		DrawFire();					
		DrawText(TextFormat("%i FPS", GetFPS()), 5, 5, 20, RED);
		EndDrawing();
	}

	CloseWindow();
	return 0;
}
