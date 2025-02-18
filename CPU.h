#ifndef CPU_H
#define CPU_H
#include <stdio.h>
#include <memory>
#include "Registers.h"
#include "RAM.h"
#include "Instruction.h"
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

	// Fetch the opcode at PC, identical to getU8Immediate(registers.pc) 
	u8 fetch();

private:
	// Shared pointer to RAM object
	std::shared_ptr<RAM> ram_ptr;

	// Returns: u8 pointed at by PC. Increments PC
	u8 getU8Immediate();

	// Returns: u16 pointed at by PC. Increments PC by 2
	u16 getU16Immediate();

	/* Opcode Functions */
	
	void f_NOP();

	void f_LD_BC_u16(u16 data);

	void f_LD_ptrBC_A();
};
#endif