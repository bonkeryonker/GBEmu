#ifndef INSTRUCT_H
#define INSTRUCT_H
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
	JR_NC, // Read one byte of immediate data, add its value to PC if the C flag is 0
	LD_SP_u16, // Load two bytes of immediate data into SP
	LD_ptrHLdec_A, // Store contents of A into memory address specified by HL and decrement contents of HL
	INC_SP, // Increment SP register.
	INC_ptrHL, // Increment the value at memory address specified by contents of HL
	DEC_ptrHL, // Decrement the value at memory address specified by contents of HL
	LD_ptrHL_u8, // Read one byte of immediate data, and save its value to the memory address specified by HL
	SCF, // Set the carry flag
	JR_C, // Read one byte of immediate data, add its value to the PC if the C flag is 1
	ADD_HL_SP, // Add contents of SP to contents of HL, and store result in HL
	LD_A_ptrHLdec, // Load the values in memory specified by contents of HL into register A, and decrement HL
	DEC_SP, // Decrement SP register.
	INC_A, // Increment A register.
	DEC_A, // Decrement A register.
	LD_A_u8, // Load one byte of immediate data into A
	CCF, // Flip the carry flag

	/* General Load Instructions */
	LD_B_B, // Opcode 0x40
	LD_B_C,
	LD_B_D,
	LD_B_E,
	LD_B_H,
	LD_B_L,
	LD_B_ptrHL, // Load the contents of memory specified by the contents of HL into B register
	LD_B_A,
	LD_C_B,
	LD_C_C,
	LD_C_D,
	LD_C_E,
	LD_C_H,
	LD_C_L,
	LD_C_ptrHL, // Load the contents of memory specified by the contents of HL into C register
	LD_C_A,
	LD_D_B, // Opcode 0x50
	LD_D_C,
	LD_D_D,
	LD_D_E,
	LD_D_H,
	LD_D_L,
	LD_D_ptrHL,
	LD_D_A,
	LD_E_B,
	LD_E_C,
	LD_E_D,
	LD_E_E,
	LD_E_H,
	LD_E_L,
	LD_E_ptrHL,
	LD_E_A,
	LD_H_B, // Opcode 0x60
	LD_H_C,
	LD_H_D,
	LD_H_E,
	LD_H_H,
	LD_H_L,
	LD_H_ptrHL,
	LD_H_A,
	LD_L_B,
	LD_L_C,
	LD_L_D,
	LD_L_E,
	LD_L_H,
	LD_L_L,
	LD_L_ptrHL,
	LD_L_A,
	LD_ptrHL_B, // Opcode 0x70
	LD_ptrHL_C,
	LD_ptrHL_D,
	LD_ptrHL_E,
	LD_ptrHL_H,
	LD_ptrHL_L,
	HALT, // Stop system clock. Cancelled by interrupt or reset signal
	LD_ptrHL_A,
	LD_A_B,
	LD_A_C,
	LD_A_D,
	LD_A_E,
	LD_A_H,
	LD_A_L,
	LD_A_ptrHL,
	LD_A_A,
	/* ALU Operations */
	ADD_A_B,
	ADD_A_C,
	ADD_A_D,
	ADD_A_E,
	ADD_A_H,
	ADD_A_L,
	ADD_A_ptrHL,
	ADD_A_A,
	ADC_A_B,
	ADC_A_C,
	ADC_A_D,
	ADC_A_E,
	ADC_A_H,
	ADC_A_L,
	ADC_A_ptrHL,
	ADC_A_A,
	SUB_B,
	SUB_C,
	SUB_D,
	SUB_E,
	SUB_H,
	SUB_L,
	SUB_ptrHL,
	SUB_A,
	SBC_A_B,
	SBC_A_C,
	SBC_A_D,
	SBC_A_E,
	SBC_A_H,
	SBC_A_L,
	SBC_A_ptrHL,
	SBC_A_A,
	AND_B,
	AND_C,
	AND_D,
	AND_E,
	AND_H,
	AND_L,
	AND_ptrHL,
	AND_A,
	XOR_B,
	XOR_C,
	XOR_D,
	XOR_E,
	XOR_H,
	XOR_L,
	XOR_ptrHL,
	XOR_A,
	OR_B,
	OR_C,
	OR_D,
	OR_E,
	OR_H,
	OR_L,
	OR_ptrHL,
	OR_A,
	CP_B, // Perform a subtraction to compare value of B with A. Update flags, do not store result.
	CP_C, // Perform a subtraction to compare value of C with A. Update flags, do not store result.
	CP_D, // Perform a subtraction to compare value of D with A. Update flags, do not store result.
	CP_E, // Perform a subtraction to compare value of E with A. Update flags, do not store result.
	CP_H, // Perform a subtraction to compare value of H with A. Update flags, do not store result.
	CP_L, // Perform a subtraction to compare value of L with A. Update flags, do not store result.
	CP_ptrHL, // Perform a subtraction to compare value in ram pointed to by HL with A. Update flags, do not store result.
	CP_A, // Perform a subtraction to compare value of A with A. Update flags, do not store result.
	RET_NZ, // Perform a RET if the Z flag is not set.
	POP_BC, // Pop the contents from the memory stack into BC.
	JP_NZ_u16, // Jump to address specified by u16 immediate data if the Z flag is not set.
	JP_u16, // Jump to the address specified by u16 immediate data.
	CALL_NZ_u16, // If the Z flag is not set, Push the address of the following instruction to the stack, jump to the address specified by the passed u16 immediate data.
	PUSH_BC, // Push the value of BC to the memory stack. Decrement SP by 2.
	ADD_A_u8, // Read one byte of immediate data. Add its value to the accumulator. Store result in the accumulator
	RST_0, // Push PC to the stack, load address 0x0000 into PC
	RET_Z, // Perform a RET if the Z flag is set
	RET, // POP from the stack into the PC register
	JP_Z_u16, // Read two bytes of immediate data. If the Z flag is set, jump to the address represented by those data.
	CB_OFFSET, // Opcode 0xCB is the offset for the second opcode table.	
	CALL_Z_u16, // If the Z flag is set, Push the address of the following instruction to the stack, jump to the address specified by the passed u16 immediate data.
	CALL_u16, // Push the address of the following instruction to the stack, jump to the address specified by the passed u16 immediate data.
	ADC_A_u8, // Read one byte of immediate data. Perform an ADD with Carry with the value in the accumulator. Store result in accumulator.
	RST_1, // Push PC to the stack, load address 0x0008 into PC.

	RET_NC, // Perform a RET if the C flag is not set
	POP_DE, // POP from the stack into the DE register
	JP_NC_u16, // Jump to the address specified by u16 immediate data if the C flag is not set
	ILLEGAL, // Illegal operation
	CALL_NC_u16, // Push the address of the following instruction to the stack, jump to the address specified by the passed u16 immediate data if the C flag is not set.
	PUSH_DE, // Push the contents of DE onto the stack
	SUB_u8, // Read one byte of immediate data, and subtract its value from that of the accumulator. Store result in the accumulator.
	RST_2, // Push PC to the stack, load address 0x0010 into PC
	RET_C, // Perform a RET if the C flag is set
	RETI, // Used by interrupt-service routines. Resets the master interrupt enable flag
	JP_C_u16, // Jump to the address specified by u16 immediate data if the C flag is set
	ILLEGAL, // Illegal operation
	CALL_C_u16, // If the C flag is set, Push the address of the following instruction to the stack, jump to the address specified by the passed u16 immediate data.
	ILLEGAL,
	SBC_A_u8, // Read one byte of immediate data, subtract it (with carry) from the value in accumulator. Store result in accumulator.
	RST_3, // Push PC to the stack, load address 0x0018 into PC
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