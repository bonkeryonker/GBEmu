#include <stdio.h>
#include "Registers.h"

int main()
{
	CPU::REGISTERS.af = 0xdead;
	CPU::REGISTERS.bc = 0xbeef;
	CPU::REGISTERS.de = 0xbabe;
	CPU::REGISTERS.hl = 0xface;
	CPU::REGISTERS.sp = 0xfeed;
	CPU::REGISTERS.pc = 0x0000;

	CPU::REGISTERS.printAsHex();
	return 0;
}