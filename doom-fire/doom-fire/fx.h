#include <cinttypes>
#include <cstddef>
#include <vector>
#include <raylib.h>

namespace FX {
		
	/*
	typedef struct {		
		std::vector<Color> colors;
	} Pallete;
	*/

	class DoomFire {		
	public:		
		int width;
		int height;
		int max_heat = 36;

		DoomFire(int width, int height);		
		~DoomFire();		
		void DrawToBuffer();
		void RenderTo(Rectangle r);
		void Update();

		void Burn();
		void Vanish();
	private:		
		std::vector<uint8_t> heat_buffer;		
		RenderTexture2D render_target{};		

		void InitFire();
	};
}

