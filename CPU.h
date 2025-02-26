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

	// Getter for current CPU control status.
	// Returns: Value of m_isHalted
	inline const bool isHalted() {
		return this->m_isHalted;
	};

	// Fetch the opcode at PC, identical to getU8Immediate(registers.pc) 
	u8 fetch();

private:

	// Current status of CPU.
	// Set to true if STOP operation is executed.
	bool m_isHalted;

	// Shared pointer to RAM object
	std::shared_ptr<RAM> m_ram_ptr;

	// Returns: u8 pointed at by PC. Increments PC
	u8 getU8Immediate();

	// Returns: u16 pointed at by PC. Increments PC by 2
	u16 getU16Immediate();

	/* Opcode Functions */
	
	void f_NOP();

	// Load data into destination register (reference)
	void f_LD(u16& destReg, const u16 data);
	void f_LD(u8& destReg, const u8 data);

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

	// Rotate contents of A to the left, A0 being set to the CY flag value. A7 overwrites CY flag value.
	// Flags: 0, 0, 0, A7
	void f_RLA();

	// Rotate contents of A to the right, A7 being set to the CY flag value. A0 overwrites CY flag value.
	// Flags: 0, 0, 0, A0
	void f_RRA();

	// Halts the CPU oscillator and the LCD.
	// Opcode is 0x1000, though I'm not sure if the value of nextByte matters
	// TODO: Continue operation when any button is pushed (http://marc.rawer.de/Gameboy/Docs/GBCPUman.pdf)
	void f_STOP(const u8 nextByte);

	// Read 1 byte of immediate data, and jump that many memory addresses forward.
	// (PC += steps)
	void f_JR_u8(const u8 steps);
};
#endif