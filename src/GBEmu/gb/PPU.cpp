#include "PPU.h"

namespace PPU
{
	PPU::PPU(std::shared_ptr<Memory> ram_ptr, std::shared_ptr<Window> drawWindow)
	{
		m_ram_ptr = ram_ptr;
		m_drawWindow = drawWindow;
		m_regArr = new u8* [REGISTER_COUNT]; // There are 11 PPU registers
		initRegArray();
	}

	PPU::~PPU()
	{
		GB_WARN("PPU register watch buffer deleted.");
		delete[] this->m_regArr;
	}

	void PPU::tick()
	{
		this->updateState();
		switch (m_currentState)
		{
		case PPU_STATES::STATE::BLIT:
			this->doBlit();
			break;
		default:
			break;
		}
	}

	const u8 PPU::getRegister(const Register r)
	{
		u8 retVal;
		int retIndex;
		if (!isValidRegister(r))
		{
			GB_ERROR("Invalid register index {} (Address: {:04X})", r.index, r.address);
			GB_WARN("Returning value of LCDC");
			retVal = *(m_regArr[Registers::LCDC.index]);
			retIndex = Registers::LCDC.index;
		}
		else
		{
			retIndex = r.index;
			retVal = *(m_regArr[r.index]);
		}
		return retVal;
	}
	
	void PPU::initRegArray()
	{
		GB_WARN("Initializing PPU Register array");
		for (int i = 0; i < REGISTER_COUNT; i++)
			m_regArr[i] = m_ram_ptr->getRaw(Registers::getByIndex(i).address);
	}

	void PPU::updateState()
	{
		const PPU_STATES::STATE prevState = m_currentState;
		const PPU_STATES::STATE state = (PPU_STATES::STATE)(getRegister(Registers::STAT) & Registers::STAT_FLAG::PPU_STATE);
		switch (state)
		{
		case PPU_STATES::HBLANK:
			m_currentState = PPU_STATES::HBLANK;
			break;
		case PPU_STATES::VBLANK:
			m_currentState = PPU_STATES::VBLANK;
			break;
		case PPU_STATES::OAM_SCAN:
			m_currentState = PPU_STATES::OAM_SCAN;
			break;
		case PPU_STATES::BLIT:
			m_currentState = PPU_STATES::BLIT;
			break;
		default:
			GB_ERROR("Unkown PPU state {:01X}. Maintaining state: {:01X}", (u8)state, (u8)(this->m_currentState));
			return; // Return early if an unknown state was encountered so we don't relog it below
		}

		// Do logging if the state has changed since last tick
		if (state != prevState)
		{
			const char* stateStr = PPU_STATES::toString(state);
			const char* prevStateStr = PPU_STATES::toString(prevState);
			GB_INFO("PPU State: {} (was {})", stateStr, prevStateStr);
		}
	}

	void PPU::doBlit()
	{
		bool isHighTilemapAddress = (bool)(getRegister(Registers::LCDC) & Registers::CONTROL_FLAGS::BG_TILEMAP);
		u16 tilemapStartAddress = (isHighTilemapAddress) ? 0x9C00 : 0x9800;
		auto tilemapIndex = 0;
		for (auto tilemapIndex = 0; tilemapIndex < TILEMAP_SIZE_BYTE; tilemapIndex++)
		{
			u8 tileDataAddr = m_ram_ptr->getItem(tilemapStartAddress + tilemapIndex);
			Tile currentTile = getTile(tileDataAddr);
			auto [high, low] = currentTile.toHex();
			//GB_INFO("Tilemap[{}]: {:016X}{:016X}", tilemapIndex, low, high);
			drawTile(currentTile, tilemapIndex);
		}
	}

	Tile PPU::getTile(u8 address)
	{
		// if TRUE: use $8000 as base pointer, and unsigned addressing
		// if FALSE: use $9000 as base pointer, and signed addressing
		bool isHighTiledatAddress = (bool)(getRegister(Registers::LCDC) & Registers::CONTROL_FLAGS::BGWIN_TILEDAT);
		u16 basePointer = (isHighTiledatAddress) ? 0x8000 : 0x9000;
		u16 tileAddress;
		Tile retVal;

		if (!isHighTiledatAddress)
			tileAddress = (int8_t)address + basePointer; // Signed addressing mode
		else
			tileAddress = address + basePointer; // Unsigned addressing mode

		for (auto i = 0; i < TILE_SIZE_BYTE; i++)
		{
			retVal.bytes[i] = m_ram_ptr->getItem(tileAddress + i);
		}

		return retVal;
	}

	bool PPU::drawTile(Tile& tile, int tilemapIndex)
	{
		//Calculate x and y coords of top-left tile pixel based on tilemapIndex
		int windowY = (tilemapIndex % TILEMAP_TILECOUNT);
		int windowX = 0;
		bool retVal;
		for (TileRow row : tile.rows)
		{	
			windowX = 0;
			for (u8 i = 0x80; i > 0; i >>= 1)
			{
				bool lowColor = row.low & i;
				bool hiColor = row.high & i;
				Color_RGBA pxColor = DMGColors::getColor(hiColor, lowColor);
				m_drawWindow->setDrawColor(pxColor);
				retVal = m_drawWindow->drawPoint(windowX, windowY);
				//GB_INFO("Window ({},{}): {}", windowX, windowY, DMGColors::toString(pxColor));
				windowX++;
			}
			windowY++;
		}
		return retVal;
	}
}
