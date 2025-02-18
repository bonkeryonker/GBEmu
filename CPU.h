#ifndef CPU_H
#define CPU_H
#include <stdio.h>
#include <memory>
#include "Registers.h"
#include "RAM.h"
class CPU
{
public:
	// Sets all register values to default values
	// Program counter set to 0
	CPU(std::shared_ptr<RAM>& ram);
	CPU() = delete; // will never be generated, default constructor forbidden

	// Public struct holding register data
	REGISTERS registers;

	// Do something
	void tick();

private:
	std::shared_ptr<RAM> ram_ptr;
};
#endif