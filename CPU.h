#ifndef CPU_H
#define CPU_H
#include <stdio.h>
#include "Registers.h"
namespace CPU
{
	// Initializes program counter to 0x00
	void init();
	void tick();
}
#endif
