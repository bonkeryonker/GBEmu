#include "PPU.h"

namespace PPU
{
	PPU::PPU(std::shared_ptr<Memory> ram_ptr)
	{
		m_ram_ptr = ram_ptr;
		m_regArr = new u8* [11]; // There are 11 PPU registers
		initRegArray();
	}

	PPU::~PPU()
	{
		GB_INFO("Deallocating PPU register memory watches");
		delete[] this->m_regArr;
	}
	
	void PPU::initRegArray()
	{
		for (int i = 0; i < 11; i++)
			m_regArr[i] = m_ram_ptr->getRaw(Registers::getByIndex(i).address);
	}
}
