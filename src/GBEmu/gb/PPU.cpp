#include "PPU.h"

namespace PPU
{
	PPU::PPU(std::shared_ptr<Memory> ram_ptr)
	{
		m_ram_ptr = ram_ptr;
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
}
