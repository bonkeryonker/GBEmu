#include "CPU.h"

CPU::CPU(std::shared_ptr<RAM>& ram)
{
	this->registers.setDefaultValues();
	this->ram_ptr = ram;	
}

void CPU::tick()
{
	printf("Tock!\n");
}