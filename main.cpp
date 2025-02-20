#include <stdio.h>
#include <memory>
#include <functional>
#include "Clock.h"
#include "Registers.h"
#include "CPU.h"
#include "RAM.h"

int main()
{
	std::shared_ptr<RAM> ram_ptr = std::make_shared<RAM>();
	ram_ptr->setItem(ROMBANK00, LD_BC_u16);
	ram_ptr->setItem(ROMBANK00 + 1, 0x00);
	ram_ptr->setItem(ROMBANK00 + 2, 0x80);
	ram_ptr->setItem(ROMBANK00 + 3, LD_ptrBC_A);
	CPU c(ram_ptr);
	c.registers.a = 0xa1;
	Clock::tick(c);
	Clock::tick(c);
	c.registers.printAsHex();
	ram_ptr->dumpMemoryToFile();
	return 0;
}