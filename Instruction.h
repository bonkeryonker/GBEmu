#ifndef INSTRUCT_H
#define INSTRUCT_H
#include <string>
#include <functional>
#include <vector>
#include "Globals.h"

enum Mnemonic
{
	NOP = 0x00,
	LD_BC_u16, // Load two bytes of immediate data into BC
	LD_ptrBC_A, // Store contents of A to the memory location specified by BC
	INC_BC, // Increment BC register. (TODO: Why aren't alu flags needed for this?)
	INC_B, // Increment B register.
	DEC_B, // Decrement B register.
	LD_B_u8, // Load one byte of immediate data into B
	RLCA, // Bitshift left, bit A7 wrapping around to A0.
	LD_a16_SP, // Load the value of the stack pointer to the memory location specified by the u16 immediate
	ADD_HL_BC, // Add the values of the BC and HL registers together and store the result into the HL register
	LD_A_ptrBC, // Load the 8bit contents of memory specified by BC into register A
	DEC_BC, // Decrement BC register.
	INC_C, // Increment C register.
	DEC_C, // Decrement C register.
	LD_C_u8, // Load one byte of immediate data into C
	RRCA, // Bitshift right, bit A0 wrapping around to A7.
};

class Instruction
{
public:
	Instruction(Mnemonic opcode, unsigned short size, unsigned short timing) : opcode(opcode), size(size), timing(timing) {}
	Instruction() = delete;

	static const Instruction opcodeLookup[];

	// Mnemonic (u8) representing this instruction
	Mnemonic opcode;

	// The size of the instruction in bytes.
	// IE: a size of 2 denotes a 1-byte mnemonic followed by a 1-byte u8 immediate
	unsigned short size;

	// The amount of clock cycles (t) this Instruction takes to execute. (4t = 1M)
	unsigned short timing;
};

#endif