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

	// Load data into destination register (reference)
	void f_LD(u16& destReg, u16 data);
	void f_LD(u8& destReg, u8 data);

	// Load data from dataReg to ram address saved in ramAddrReg
	void f_LD_ptr(u16& ramAddrReg, u8& dataReg);
};
#endif