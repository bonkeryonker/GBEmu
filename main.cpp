#include <stdio.h>
#include <functional>
#include "Registers.h"
#include "CPU.h"
#include "RAM.h"

void testRegisters();
void testRAM();

int main()
{
	CPU::init();
	RAM::init();
#ifdef _DEBUG
	//testRegisters();
	testRAM();
#endif
	return 0;
}

void testRegisters()
{
	CPU::REGISTERS.setDebugValues();
	CPU::REGISTERS.printAsHex();
}

void testRAM()
{
	if (RAM::setItem(RAM::MemoryMap::ROMBANK00, 'L'))
	{
		printf("Test failed. Was able to write to cartridge ROM.\n");
		return;
	}
	if (RAM::setItem(RAM::MemoryMap::ECHO, 'L'))
	{
		printf("Test failed. Was able to write to Echo RAM.\n");
		return;
	}
	if (RAM::setItem(RAM::MemoryMap::FORBIDDEN, 'L'))
	{
		printf("Test failed. Was able to write to Forbidden RAM.\n");
		return;
	}
	RAM::setDebugValues();
	RAM::dumpMemoryToFile("ram_dump.bin");
}