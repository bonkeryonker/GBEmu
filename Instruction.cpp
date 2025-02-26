#include "Instruction.h"

const Instruction Instruction::opcodeLookup[] =
{
	Instruction(NOP, 1, 4),
	Instruction(LD_BC_u16, 3, 12),
	Instruction(LD_ptrBC_A, 1, 8),

	Instruction(INC_BC, 1, 8),
	Instruction(INC_B, 1, 4),
	Instruction(DEC_B, 1, 4),
	Instruction(LD_B_u8, 2, 8),
	Instruction(RLCA, 1, 4),
	Instruction(LD_a16_SP, 3, 20),

	Instruction(ADD_HL_BC, 1, 8),
	Instruction(LD_A_ptrBC, 1, 8),
	Instruction(DEC_BC, 1, 8),
	Instruction(INC_C, 1, 4),
	Instruction(DEC_C, 1, 4),
	Instruction(LD_C_u8, 2, 8),
	Instruction(RRCA, 1, 4),
	Instruction(STOP, 2, 4),
};