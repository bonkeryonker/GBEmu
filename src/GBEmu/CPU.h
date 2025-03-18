#ifndef CPU_H
#define CPU_H
#include <stdio.h>
#include <memory>
#include "Registers.h"
#include "Memory.h"
#include "Instruction.h"
class CPU
{
	// We may need to rework the CPU class to better emulate real hardware when we implement interrupts.
	// Let's hope we don't need to, but if so this will prove an invaluable resource:
	// https://gist.github.com/SonoSooS/c0055300670d678b5ae8433e20bea595#fetch-and-stuff
public:
	// Sets all register values to default values
	// Program counter set to 0
	CPU(std::shared_ptr<Memory>& ram);
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
	// Set to true if STOP or HALT operation is executed.
	bool m_isHalted;

	// A counter to keep track of the current count of objects on the stack.
	// Used for debugging purposes.
	u8 m_stackSizeCounter;

	// Shared pointer to RAM object
	std::shared_ptr<Memory> m_ram_ptr;

	// Call the correct function for this specific opcode
	void executeInstruction(Mnemonic opcode);

	// Returns: u8 pointed at by PC. Increments PC
	u8 getU8Immediate();

	// Returns: u16 pointed at by PC. Increments PC by 2
	u16 getU16Immediate();


	/* Opcode Functions implemented in CPU_OpcodeFuncs.cpp */
	
	// No operation, do nothing.
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

	// Load one byte of immediate data to the address specified by the value of the passed register.
	void f_LD_ptr_r16_u8(const u16& addrSrcReg, u8 data);

	// Add the value of the passed signed 8-bit integer to the SP. Store result in SP.
	// Flags: 0, 0, H, C
	void f_ADDSP(const int8_t signedInt);

	// Add the value of the passed signed 8-bit integer to the SP. Store result in destReg.
	// Flags: 0, 0, H, C
	void f_ADDSP(const int8_t signedInt, u16& destReg);

	// Add two 16-bit registers together, saving the result to destReg
	// Flags: -, 0, H, C
	void f_ADD_r16_r16(u16& destReg, u16& srcReg);

	// Add the value of srcReg to the value stored in the accumulator. Store the result in the accumulator.
	// Flags: Z, 0, H, C
	void f_ADD(const u8 srcReg);

	// Add the value of srcReg and the value of the CY flag to the value stored in the accumulator. Store the result in the accumulator.
	// Flags: Z, 0, H, C
	void f_ADDC(const u8 srcReg);

	// Subtract the value of srcReg from the value stored in the accumulator. Store the result in the accumulator.
	// Flags: Z, 1, H, C
	void f_SUB(const u8 srcReg);

	// Subtract the value of srcReg and the value of the CY flag from the value stored in the accumulator. Store the result in the accumulator.
	// Flags: Z, 1, H, CY
	void f_SBC(const u8 srcReg);

	// Perform logical AND with srcReg and accumulator. Store result in accumulator.
	// Flags: Z, 0, 1, 0
	void f_AND(const u8 srcReg);

	// Perform logical XOR with srcReg and accumulator. Store result in accumulator.
	// Flags: Z, 0, 0, 0
	void f_XOR(const u8 srcReg);

	// Perform logical OR with srcReg and accumulator. Store result in accumulator.
	// Flags: Z, 0, 0, 0
	void f_OR(const u8 srcReg);

	// Compare contents of srcReg and accumulator by calculating A-B. Update flags, but don't affect accumulator contents.
	// Flags: Z, 1, H, C
	void f_CP(const u8 srcReg);

	// Increment the value in passed register (reference)
	void f_INC_r16(u16& reg);

	// Increment the contents of memory pointed to by passed register.
	// Flags: Z, 0, H (8bit), -
	void f_INC_ptr(const u16& reg);

	// Decrement the contents of memory pointed to by passed register.
	// Flags: Z, 1, H (8bit), -
	void f_DEC_ptr(const u16& reg);

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
	// This operation apparently is weird as hell. See the pandocs for details (https://gbdev.io/pandocs/Reducing_Power_Consumption.html#using-the-stop-instruction)
	// TODO: Implement properly according to pandoc spec. For now, just HALT
	void f_STOP(const u8 nextByte);

	// Halts the System Clock and LCD.
	// See pandoc for details (https://gbdev.io/pandocs/Reducing_Power_Consumption.html#using-the-stop-instruction)
	void f_HALT();

	// Read 1 byte of immediate data, and jump that many memory addresses forward.
	// (PC += steps)
	void f_JR_u8(u8 steps);

	// Read 1 byte of immediate data, and jump that many memory addresses forward if the flag matches jumpIfFlag boolean
	// (PC += steps)
	void f_JR_flag(u8 steps, u8 FLAG, bool jumpIfFlag = true);

	// Read two bytes of immediate data, and jump to that memory address.
	void f_JP(u16 destAddr);

	// Read two bytes of immediate data, and jump to that memory address if FLAG equals the jumpIfFlag value.
	void f_JP_flag(u16 destAddr, u8 FLAG, bool jumpIfFlag = true);

	// Adjust the accumulator (A) to a BCD number after BCD addition/subtraction operations
	// Flags: Z, -, 0, C
	void f_DAA();

	// Get the 1's complement (flip all bits) of register A
	// Flags: -, 1, 1, - (Set N, set H)
	void f_CPL();

	// Pop from stack the PC value pushed when CALL was executed. Little endian.
	// This is identical to a POP PC instruction (if one existed).
	// For example, if the stack looks like this:
	// 0x8000: 0xef <-- SP
	// 0x8001: 0xbe
	// then RET will result in the following values:
	// PC: 0xbeef, SP: 0x8002
	// Program execution continues at 0xbeef. 
	void f_RET();

	// Perform a RET if FLAG matches the retIfFlag value.
	void f_RET_flag(u8 FLAG, bool retIfFlag = true);

	// Push the contents of passed register onto memory stack.
	// [SP-1] = srcReg high byte
	// [SP-2] = srcReg low byte
	// SP ends at [SP-2]
	void f_PUSH(const u16 srcReg);

	// Pop the contents from the memory stack into passed register.
	// [SP] = destReg low byte
	// [SP+1] = destReg high byte
	// SP ends at [SP+2]
	void f_POP(u16& destReg);

	// Read two bytes of immediate data. Push the PC to the stack, then jump to the address specified by callAddr.
	void f_CALL(const u16 callAddr);

	// Perform a CALL if FLAG matches the retIfFlag value.
	void f_CALL_flag(const u16 callAddr, u8 FLAG, bool callIfFlag = true);

	// Push the current PC to the memory stack and load address corresponding to passed
	// variable to the PC. If an invalid value for n (not 0-7) is passed into this function, it will load value 0x0000 to PC and halt the CPU.
	// Table is as such below:
	// RST 0 : Load 0x0000 to PC
	// RST 1 : Load 0x0008 to PC
	// RST 2 : Load 0x0010 to PC
	// RST 3 : Load 0x0018 to PC
	// RST 4 : Load 0x0020 to PC
	// RST 5 : Load 0x0028 to PC
	// RST 6 : Load 0x0030 to PC
	// RST 7 : Load 0x0038 to PC
	void f_RST_n(u8 n);

	// Attempted to execute invalid CPU opcode.
	// Halt the CPU and print the current opcode. Dump memory.
	void f_ILLEGAL_OP(const u8 opcode);
};
#endif