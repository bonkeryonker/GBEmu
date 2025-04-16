#ifndef PPU_H
#define PPU_H
#include <memory> // shared_ptr
#include "Globals.h"
#include "Memory.h"

namespace PPU
{
	// Dots per M-Cycle (Total no. of pixels drawn in 1 equivalent CPU M-Cycle)
	constexpr int DPM = 4;
	// Dots per frame (Total no. of pixels in a one "frame" render)
	constexpr int DPF = 70224;
	// Total count of PPU Registers
	// (PPU Registers are addresses in memory)
	constexpr int REGISTER_COUNT = 11;

	struct Register 
	{
		u16 address;
		int index;

		constexpr Register(uint16_t addr, int i) : address(addr), index(i) {}
	};

	namespace Registers
	{
		constexpr Register LCDC{ 0xFF40, 0 };
		constexpr Register STAT{ 0xFF41, 1 };
		constexpr Register SCY{ 0xFF42, 2 };
		constexpr Register SCX{ 0xFF43, 3 };
		constexpr Register LY{ 0xFF44, 4 };
		constexpr Register LYC{ 0xFF45, 5 };
		constexpr Register BGP{ 0xFF47, 6 };
		constexpr Register OBP0{ 0xFF48, 7 };
		constexpr Register OBP1{ 0xFF49, 8 };
		constexpr Register WY{ 0xFF4A, 9 };
		constexpr Register WX{ 0xFF4B, 10 };

		// Enum containing bitmasks for LCDC
		typedef enum CONTROL_FLAGS
		{
			// Master enable for PPU and LCD
			// (0: off, 1: on)
			LCD_ENABLE = 0b10000000,

			// Area in RAM PPU looks for the window's tilemap.
			// (0: 0x9800-0x9BFF, 1: 0x9C00-0x9FFF)
			WIN_TILEMAP = 0b01000000, 

			// Enable for if the window should be displayed.
			// Overridden by bit 0 (BGWIN_PRIORITY)
			// (0: off, 1: on)
			WINDOW_ENABLE = 0b00100000,

			// Area in RAM PPU looks for window/bg's tilemap data.
			// (0: 0x8800-97FF, 1: 0x8000-0x8FFF)
			BGWIN_TILEDAT = 0b00010000,

			// Area in RAM PPU looks for bg's tilemap.
			// (0: 0x9800-0x9BFF, 1: 0x9C00-0x9FFF)
			BG_TILEMAP = 0b00001000,

			// Size of sprites (in pixels)
			// (0: 8x8, 1: 8x16)
			OBJ_SIZE = 0b000000100,

			// Enable for if sprites should be rendered or not
			// (0: off, 1: on)
			OBJ_ENABLE = 0b00000010,

			// When off, both BG and Window become blank.
			// This behaves differently on CGBs, but we're only
			// targetting DMG emulation.
			// (0: off, 1: on)
			BGWIN_PRIORITY = 0b00000001
			
		}LCDC_FLAG;

		// Enum containing bitmasks for LCDSTAT
		typedef enum STATUS_FLAGS
		{
			// When enabled, will trigger STAT interrupt on LYC==LY
			LYC_INT = 0b01000000,

			// When enabled, will trigger STAT interrupt on OAM_SCAN
			OAMSCAN_INT = 0b00100000,

			// When enabled, will trigger STAT interrupt on VBLANK
			VBLANK_INT = 0b00010000,

			// When enabled, will trigger STAT interrupt on HBLANK
			HBLANK_INT = 0b00001000,

			// Enabled when LY == the value of LYC. Read-only.
			LYC_LY = 0b00000100,

			// Read-only value representing the current STATE of the PPU
			// This value is between 0-3, and occupies 2 bits.
			PPU_STATE = 0b00000011

		}STAT_FLAG;

		// Returns: PPU register constexpr based on its index in the PPU register buffer
		inline Register getByIndex(int i)
		{
			switch (i)
			{
			case 0:
				return LCDC;
			case 1:
				return STAT;
			case 2:
				return SCY;
			case 3:
				return SCX;
			case 4:
				return LY;
			case 5:
				return LYC;
			case 6:
				return BGP;
			case 7:
				return OBP0;
			case 8:
				return OBP1;
			case 9:
				return WY;
			case 10:
				return WX;
			default:
				GB_ERROR("Invalid PPU Register index ({})", i);
				GB_WARN("Returning LCDC (index: 0)");
				return LCDC;
			}
		}
	}

	struct PPU_STATES
	{
		enum STATE
		{
			HBLANK = 0b00,
			VBLANK = 0b01,
			OAM_SCAN = 0b10,
			BLIT = 0b11 // Copy contents of VRAM to the screen
		};

		static inline const char* toString(STATE state)
		{
			switch (state)
			{
			case HBLANK:
				return "HBLANK";
			case VBLANK:
				return "VBLANK";
			case OAM_SCAN:
				return "OAM_SCAN";
			case BLIT:
				return "BLIT";
			default:
				return "INVALID";
			}
		}
	};
	

	class PPU
	{
	public:
		PPU(std::shared_ptr<Memory> ram_ptr);
		~PPU();

		void tick();

		// Return the value stored in the passed register
		const u8 getRegister(const Register r);
	private:
		std::shared_ptr<Memory> m_ram_ptr;
		PPU_STATES::STATE m_currentState;
		u8** m_regArr;
	private:
		void initRegArray();

		// Updates the value of m_currentState to accurately represent the value shown in the STAT register
		void updateState();
		inline bool isValidRegister(const Register& r){ return (r.index >= 0 && r.index < REGISTER_COUNT); }
	};
}
#endif

