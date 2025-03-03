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
	INC_BC, // Increment BC register. (No ALU flags need to be set for 16-bit alu operations).
	INC_B, // Increment B register.
	DEC_B, // Decrement B register.
	LD_B_u8, // Load one byte of immediate data into B
	RLCA, // Bitshift left, bit A7 wrapping around to A0. Store the value of A7 to carry flag.
	LD_a16_SP, // Load the value of the stack pointer to the memory location specified by the u16 immediate
	ADD_HL_BC, // Add the values of the BC and HL registers together and store the result into the HL register
	LD_A_ptrBC, // Load the 8bit contents of memory specified by BC into register A
	DEC_BC, // Decrement BC register.
	INC_C, // Increment C register.
	DEC_C, // Decrement C register.
	LD_C_u8, // Load one byte of immediate data into C
	RRCA, // Bitshift right, bit A0 wrapping around to A7.
	STOP, // Stop cpu, stop LCD controller.(TODO: Until button pushed? See CPU manual: http://marc.rawer.de/Gameboy/Docs/GBCPUman.pdf)
	LD_DE_u16, // Load two bytes of immediate data into DE
	LD_ptrDE_A, // Store contents of A to the memory location specified by DE
	INC_DE, // Increment DE register. (No ALU flags need to be set for 16-bit alu operations).
	INC_D, // Increment D register.
	DEC_D, // Decrement D register.
	LD_D_u8, // Load one byte of immediate data into D
	RLA, // Bitshift left, A0 gaining the value of whatever's in the carry flag. A7 saved to CY flag.
	JR_u8, // Read one byte of immediate data, add its value to the PC (Jump n steps forward).
	ADD_HL_DE, // Add the values of the HL and DE registers together and store the result into the HL register	
	LD_A_ptrDE, // Load the 8bit contents of memory specified by DE into register A
	DEC_DE, // Decrement DE register.
	INC_E, // Increment E register.
	DEC_E, // Decremennt E register.
	LD_E_u8, // Load one byte of immediate data into E
	RRA, // Bitshift right, A7 gaining the value of whatever's in the carry flag. A0 saved to CY flag.
	JR_NZ, // Read one byte of immediate data, add its value to the PC if the Z flag is 0
	LD_HL_u16, // Load two bytes of immediate data into HL
	LD_ptrHLinc_A, // Store contents of A into memory address specified by HL and increment contents of HL
	INC_HL, // Increment HL register.
	INC_H, // Increment H register.
	DEC_H, // Decrement H register.
	LD_H_u8, // Load one byte of immediate data into H
	DAA, // Adjust A to a BCD number after BCD addition/subtraction operations
	JR_Z, // Read one byte of immediate data, add its value to the PC if the Z flag is 1
	ADD_HL_HL, // Add contents of HL to the contents of HL. Store result in HL
	LD_A_ptrHLinc, // Load contents of memory specified by HL into A and increment contents of HL
	DEC_HL, // Decrement HL register.
	INC_L, // Increment L register.
	DEC_L, // Decrement L register.
	LD_L_u8, // Load one byte of immediate data into L
	CPL, // Take the 1's Complement (flip all bits) of the contents of register A
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