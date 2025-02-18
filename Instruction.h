#ifndef INSTRUCT_H
#define INSTRUCT_H
#include <string>
#include <functional>
#include <vector>
#include "Globals.h"

enum Mnemonic
{
	NOP = 0x00,
	LD_BC_u16, //Load two bytes of immediate data into BC
	LD_ptrBC_A, //Store contents of A to the memory location specified by BC
};

class Instruction
{
public:
	Instruction(Mnemonic opcode, unsigned short size, unsigned short timing) : opcode(opcode), size(size), timing(timing) {}
	Instruction() = delete;

	// Mnemonic (u8) representing this instruction
	Mnemonic opcode;

	// The size of the instruction in bytes.
	// IE: a size of 2 denotes a 1-byte mnemonic followed by a 1-byte u8 immediate
	unsigned short size;

	// The amount of clock cycles (t) this Instruction takes to execute. (4t = 1M)
	unsigned short timing;
};

#endif