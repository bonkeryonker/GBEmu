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
	RAM::setDebugValues();
	RAM::dumpMemoryToFile("ram_dump.bin");
}