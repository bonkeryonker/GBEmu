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

	// Fetch and execute the opcode at PC
	// Returns: tCycleCount of executed operation (currentInstruction.timing)
	unsigned short tick();

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

	// Load data from ram address specified by 16bit register to 8bit destination register
	void f_LD_r8_ptr(u8& destReg, u16& dataReg);

	// Load the stack pointer to the specified destination in ram
	void f_LD_u16_SP(u16 dest);

	// Add two 16-bit registers together, saving the result to destReg
	// Flags: -, 0, H, C
	void f_ADD_r16_r16(u16& destReg, u16& srcReg);

	// Increment the value in passed register (reference)
	void f_INC_r16(u16& reg);

	// Increment the value in passed register (reference)
	// Flags: Z, 0, H, -
	void f_INC_r8(u8& reg);

	// Decrement the value in passed register (reference)
	void f_DEC_r16(u16& reg);

	// Decrement the value in passed register (reference)
	// Flags: Z, 1, H, -
	void f_DEC_r8(u8& reg);

	// Rotate contents of A to the left, wrapping A7 bit around to A0.
	// Flags: 0, 0, 0, A7
	void f_RLCA();

	// Rotate the contents of A to the right, wrapping A0 bit around to A7.
	// Flags: 0, 0, 0, A0
	void f_RRCA();
};
#endif