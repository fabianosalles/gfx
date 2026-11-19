#include "fx.h"
#include <print>
#include <limits>

FX::DoomFire::DoomFire(int width, int height)
	: width(width), height(height), state(IDLE)
{	
	InitFire();	
}

void FX::DoomFire::InitFire() {	

	render_target = LoadRenderTexture(width, height);
	SetTextureFilter(render_target.texture, TEXTURE_FILTER_POINT);

	//buffer all black
	heat_buffer.assign(static_cast<std::size_t>(width) * height, 0);

	//set bottom row to max heat
	Burn();
}

FX::DoomFire::~DoomFire()
{
	UnloadRenderTexture(render_target);
}

void FX::DoomFire::DrawToBuffer() {

	BeginTextureMode(render_target);
	ClearBackground(BLANK);

		//DrawRectangleLines(0, 0, width, height, RED);

		for (auto y = 0; y < height; y++) {
			for (auto x = 0; x < width; x++) {
				uint8_t heat = heat_buffer[(y * width) + x];
				float intensity = static_cast<float>(heat) / max_heat;
				Color color = {
					std::min(255.0f, heat * 7 * intensity),
					std::min(255.0f, heat * 2 * intensity),
					std::min(255.0f, heat / 2 * intensity),
					std::min(255.0f, (heat * 255 / max_heat) * intensity)
				};

				DrawPixel(x, y, color);
			}
		}	
		EndTextureMode();
}

void FX::DoomFire::RenderTo(Rectangle target)
{
	Rectangle source = {
		0.0f,
		0.0f,
		static_cast<float>(width),
		-static_cast<float>(height)
	};
		
	DrawTexturePro(render_target.texture, 
		source, 
		target, { 0.0f, 0.0f }, 0.0f, 
		WHITE);
}


void FX::DoomFire::Update() {
	for (auto y = 1; y < height; y++) {
		for (auto x = 0; x < width; x++) {
			uint8_t heat = heat_buffer[(y * width) + x];
			int random = GetRandomValue(0, 3);
			//int cooling = random == 0 ? 1 : 0;
			//int cooling = random & 1;
			int cooling = GetRandomValue(0, 3) == 0 ? 1 : 0;
			int targetX = x + 1 - random;
						
			targetX = (targetX + width) % width;
			int nextHeat = heat - cooling;
			heat_buffer[((y - 1) * width) + targetX] = (uint8_t)(nextHeat > 0 ? nextHeat : 0);
		}
	}
}

void FX::DoomFire::Vanish()
{
	for (auto x = 0; x < width; x++) {
		heat_buffer[(height - 1) * width + x] = 0;
	}
	state = IDLE;
}

void FX::DoomFire::Burn() {
	for (auto x = 0; x < width; x++) {
		heat_buffer[(height - 1) * width + x] = max_heat;
	}
	state = BURNING;
}
