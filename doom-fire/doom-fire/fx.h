#include <cinttypes>
#include <cstddef>
#include <vector>
#include <raylib.h>

namespace FX {

	class DoomFire {		
	public:
		enum State { IDLE, BURNING};
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
		[[nodiscard]] bool IsActive() const noexcept{ return state == BURNING;}
		[[nodiscard]] State GetState() const noexcept{ return state; }
	private:
		DoomFire::State state = IDLE;
		std::vector<uint8_t> heat_buffer;
		RenderTexture2D render_target{};		

		void InitFire();
	};
}

