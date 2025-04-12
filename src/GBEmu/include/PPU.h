#ifndef PPU_H
#define PPU_H
#include <memory> // shared_ptr
#include "Globals.h"
#include "Memory.h"

namespace PPU
{
	struct Register
	{
		u16 address;
		int index;

		constexpr Register(uint16_t addr, int i) : address(addr), index(i) {}
	};

	enum STATE
	{
		HBLANK = 0x00,
		VBLANK = 0x01,
		OAM_ACCESS = 0x10,
		BLIT = 0x11 // Copy contents of VRAM to the screen
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

		Register getByIndex(int i)
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

	class PPU
	{
	public:
		PPU(std::shared_ptr<Memory> ram_ptr);
		~PPU();
	private:
		std::shared_ptr<Memory> m_ram_ptr;
		STATE m_currentState;
		u8** m_regArr;
	private:
		void initRegArray();
	};
}
#endif

