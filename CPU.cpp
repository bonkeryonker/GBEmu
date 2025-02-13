#include "CPU.h"

void CPU::init()
{
	// Initialize program counter to 0
	CPU::REGISTERS.pc = 0x0000;
}
void CPU::tick()
{
	printf("Tock!\n");
}