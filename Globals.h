#ifndef GLOBALS_H
#define GLOBALS_H
#include <cstdint>
#include <memory>
#include "Instruction.h"

typedef uint8_t u8;
typedef uint16_t u16;

const Instruction opcodeLookup[] =
{
	Instruction(NOP, 1, 4),
	Instruction(LD_BC_u16, 3, 12),
	Instruction(LD_ptrBC_A, 1, 8)
};
#endif