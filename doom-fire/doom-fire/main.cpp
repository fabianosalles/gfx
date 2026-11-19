#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include <raygui.h>
#include <algorithm>
#include "fx.h"


void HaneldInput(FX::DoomFire& fire)
{
	if (IsKeyPressed(KEY_V)) 
		fire.Vanish();

	if (IsKeyPressed(KEY_B)) 
		fire.Burn();	
	
	if (IsKeyPressed(KEY_KP_ADD)) {
		fire.max_heat++;
		if (fire.max_heat > 255) {
			fire.max_heat = 1;
		}
	}		

	if (IsKeyPressed(KEY_KP_SUBTRACT)) {
		fire.max_heat--;
		if (fire.max_heat < 1) {
			fire.max_heat = 255;
		}
	}

	if (IsKeyPressed(KEY_F)) {
		ToggleFullscreen();		
	}
}

void DrawFireControls(FX::DoomFire& fire, bool& active)
{
	const int panel_w = 300;
	
	
	Rectangle panel = { 
		GetScreenWidth() - panel_w - 20, 
		20.0f, panel_w, 130.0f };
	DrawRectangleRec(panel, Fade(BLACK, 0.75f));
	
	GuiGroupBox(panel, "FIRE CONTROLS");
	float max_heat = static_cast<float>(fire.max_heat);
	const int previous_max_heat = fire.max_heat;
	GuiSlider(
		{ panel.x + 120.0f, panel.y + 35.0f, 155.0f, 24.0f },
		"1", "255", &max_heat, 1.0f, 255.0f);
	fire.max_heat = std::clamp(int(max_heat + 0.5f), 1, 255);
	if (fire.max_heat != previous_max_heat && active)
		fire.Burn();
	GuiLabel({ panel.x + 15.0f, panel.y + 35.0f, 100.0f, 24.0f },
		TextFormat("Max heat: %i", fire.max_heat));

	bool is_burning = (fire.GetState() == FX::DoomFire::BURNING);
	bool previous_state = is_burning;
	GuiCheckBox({ panel.x + 15.0f, panel.y + 75.0f, 24.0f, 24.0f }, "Active", &is_burning);
	if (is_burning != previous_state) {
		if (is_burning) {
			fire.Burn();
		} else {
			fire.Vanish();
		}
		active = is_burning;
	}
}

int main()
{	
	
	SetConfigFlags(FLAG_VSYNC_HINT);
	InitWindow(1280, 720, "Doom Fire");
	SetTargetFPS(60);		
	{
		auto arcade_font = LoadFontEx("assets/font/arcade.ttf", 120, 0, 0);
		if (!IsFontValid(arcade_font)) {
			TraceLog(LOG_ERROR, "Failed to load arcade font");		
			return -1;
		}

		FX::DoomFire fire(320, 180);
		bool active = true;
		fire.Burn();
		while (!WindowShouldClose())
		{
			HaneldInput(fire);
			fire.Update();
			fire.DrawToBuffer();

			BeginDrawing();
				ClearBackground(BLACK);
								
				DrawText(TextFormat("%i FPS - max heat: %i - B burn, V vanish ", GetFPS(), fire.max_heat), 5, 5, 20, RED);

				
				DrawTextEx(arcade_font, TextFormat("DOOM fire fx"),
					{ 50.0f, 300.0f },
					220.0f, 1.0f,
					RED);

				fire.RenderTo({ 0, 0, float(GetScreenWidth()), float(GetScreenHeight()) });
				DrawFireControls(fire, active);
								


			EndDrawing();
		}
		UnloadFont(arcade_font);
	}

	CloseWindow();
	return 0;
}
