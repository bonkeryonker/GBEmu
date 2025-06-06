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
	Instruction(LD_DE_u16, 3, 12),
	Instruction(LD_ptrDE_A, 1, 8),
	Instruction(INC_DE, 1, 8),
	Instruction(INC_D, 1, 4),
	Instruction(DEC_D, 1, 4),
	Instruction(LD_D_u8, 2, 8),
	Instruction(RLA, 1, 4),
	Instruction(JR_s8, 2, 12),
	Instruction(ADD_HL_DE, 1, 8),
	Instruction(LD_A_ptrDE, 1, 8),
	Instruction(DEC_DE, 1, 8),
	Instruction(INC_E, 1, 4),
	Instruction(DEC_E, 1, 4),
	Instruction(LD_E_u8, 2, 8),
	Instruction(RRA, 1, 4),
	Instruction(JR_NZ, 2, 12), //Worst case scenario for timing (12 ticks if it must make the jump. 8 ticks if not). We'll have to manually override the timing if jump is made (f_JR_NZ returns bool?)
	Instruction(LD_HL_u16, 3, 12),
	Instruction(LD_ptrHLinc_A, 1, 8),
	Instruction(INC_HL, 1, 8),
	Instruction(INC_H, 1, 4),
	Instruction(DEC_H, 1, 4),
	Instruction(LD_H_u8, 2, 8),
	Instruction(DAA, 1, 4),
	Instruction(JR_Z, 2, 12), //Worst case scenario for timing (12 ticks if it must make the jump. 8 ticks if not). We'll have to manually override the timing if jump is made (f_JR_Z returns bool?)
	Instruction(ADD_HL_HL, 1, 8),
	Instruction(LD_A_ptrHLinc, 1, 8),
	Instruction(DEC_HL, 1, 8),
	Instruction(INC_L, 1, 4),
	Instruction(DEC_L, 1, 4),
	Instruction(LD_L_u8, 2, 8),
	Instruction(CPL, 1, 4),
	Instruction(JR_NC, 2, 12), //Worst case scenario for timing (12 ticks if it must make the jump. 8 ticks if not). We'll have to manually override the timing if jump is made (f_JR_NC returns bool?)
	Instruction(LD_SP_u16, 3, 12),
	Instruction(LD_ptrHLdec_A, 1, 8),
	Instruction(INC_SP, 1, 8),
	Instruction(INC_ptrHL, 1, 12),
	Instruction(DEC_ptrHL, 1, 12),
	Instruction(LD_ptrHL_u8, 2, 12),
	Instruction(SCF, 1, 4),
	Instruction(JR_C, 2, 12), //Worst case scenario for timing (12 ticks if it must make the jump. 8 ticks if not). We'll have to manually override the timing if jump is made (f_JR_C returns bool?)
	Instruction(ADD_HL_SP, 1, 8),
	Instruction(LD_A_ptrHLdec, 1, 8),
	Instruction(DEC_SP, 1, 8),
	Instruction(INC_A, 1, 4),
	Instruction(DEC_A, 1, 4),
	Instruction(LD_A_u8, 2, 8),
	Instruction(CCF, 1, 4),
	Instruction(LD_B_B, 1, 4),
	Instruction(LD_B_C, 1, 4),
	Instruction(LD_B_D, 1, 4),
	Instruction(LD_B_E, 1, 4),
	Instruction(LD_B_H, 1, 4),
	Instruction(LD_B_L, 1, 4),
	Instruction(LD_B_ptrHL, 1, 8),
	Instruction(LD_B_A, 1, 4),
	Instruction(LD_C_B, 1, 4),
	Instruction(LD_C_C, 1, 4),
	Instruction(LD_C_D, 1, 4),
	Instruction(LD_C_E, 1, 4),
	Instruction(LD_C_H, 1, 4),
	Instruction(LD_C_L, 1, 4),
	Instruction(LD_C_ptrHL, 1, 8),
	Instruction(LD_C_A, 1, 4),
	Instruction(LD_D_B, 1, 4),
	Instruction(LD_D_C, 1, 4),
	Instruction(LD_D_D, 1, 4),
	Instruction(LD_D_E, 1, 4),
	Instruction(LD_D_H, 1, 4),
	Instruction(LD_D_L, 1, 4),
	Instruction(LD_D_ptrHL, 1, 8),
	Instruction(LD_D_A, 1, 4),
	Instruction(LD_E_B, 1, 4),
	Instruction(LD_E_C, 1, 4),
	Instruction(LD_E_D, 1, 4),
	Instruction(LD_E_E, 1, 4),
	Instruction(LD_E_H, 1, 4),
	Instruction(LD_E_L, 1, 4),
	Instruction(LD_E_ptrHL, 1, 8),
	Instruction(LD_E_A, 1, 4),
	Instruction(LD_H_B, 1, 4),
	Instruction(LD_H_C, 1, 4),
	Instruction(LD_H_D, 1, 4),
	Instruction(LD_H_E, 1, 4),
	Instruction(LD_H_H, 1, 4),
	Instruction(LD_H_L, 1, 4),
	Instruction(LD_H_ptrHL, 1, 8),
	Instruction(LD_H_A, 1, 4),
	Instruction(LD_L_B, 1, 4),
	Instruction(LD_L_C, 1, 4),
	Instruction(LD_L_D, 1, 4),
	Instruction(LD_L_E, 1, 4),
	Instruction(LD_L_H, 1, 4),
	Instruction(LD_L_L, 1, 4),
	Instruction(LD_L_ptrHL, 1, 8),
	Instruction(LD_L_A, 1, 4),
	Instruction(LD_ptrHL_B, 1, 8),
	Instruction(LD_ptrHL_C, 1, 8),
	Instruction(LD_ptrHL_D, 1, 8),
	Instruction(LD_ptrHL_E, 1, 8),
	Instruction(LD_ptrHL_H, 1, 8),
	Instruction(LD_ptrHL_L, 1, 8),
	Instruction(HALT, 1, 4),
	Instruction(LD_ptrHL_A, 1, 8),
	Instruction(LD_A_B, 1, 4),
	Instruction(LD_A_C, 1, 4),
	Instruction(LD_A_D, 1, 4),
	Instruction(LD_A_E, 1, 4),
	Instruction(LD_A_H, 1, 4),
	Instruction(LD_A_L, 1, 4),
	Instruction(LD_A_ptrHL, 1, 8),
	Instruction(LD_A_A, 1, 4),
	Instruction(ADD_A_B, 1, 4),
	Instruction(ADD_A_C, 1, 4),
	Instruction(ADD_A_D, 1, 4),
	Instruction(ADD_A_E, 1, 4),
	Instruction(ADD_A_H, 1, 4),
	Instruction(ADD_A_L, 1, 4),
	Instruction(ADD_A_ptrHL, 1, 8),
	Instruction(ADD_A_A, 1, 4),
	Instruction(ADC_A_B, 1, 4),
	Instruction(ADC_A_C, 1, 4),
	Instruction(ADC_A_D, 1, 4),
	Instruction(ADC_A_E, 1, 4),
	Instruction(ADC_A_H, 1, 4),
	Instruction(ADC_A_L, 1, 4),
	Instruction(ADC_A_ptrHL, 1, 8),
	Instruction(ADC_A_A, 1, 4),
	Instruction(SUB_B, 1, 4),
	Instruction(SUB_C, 1, 4),
	Instruction(SUB_D, 1, 4),
	Instruction(SUB_E, 1, 4),
	Instruction(SUB_H, 1, 4),
	Instruction(SUB_L, 1, 4),
	Instruction(SUB_ptrHL, 1, 8),
	Instruction(SUB_A, 1, 4),
	Instruction(SBC_A_B, 1, 4),
	Instruction(SBC_A_C, 1, 4),
	Instruction(SBC_A_D, 1, 4),
	Instruction(SBC_A_E, 1, 4),
	Instruction(SBC_A_H, 1, 4),
	Instruction(SBC_A_L, 1, 4),
	Instruction(SBC_A_ptrHL, 1, 8),
	Instruction(SBC_A_A, 1, 4),
	Instruction(AND_B, 1, 4),
	Instruction(AND_C, 1, 4),
	Instruction(AND_D, 1, 4),
	Instruction(AND_E, 1, 4),
	Instruction(AND_H, 1, 4),
	Instruction(AND_L, 1, 4),
	Instruction(AND_ptrHL, 1, 8),
	Instruction(AND_A, 1, 4),
	Instruction(XOR_B, 1, 4),
	Instruction(XOR_C, 1, 4),
	Instruction(XOR_D, 1, 4),
	Instruction(XOR_E, 1, 4),
	Instruction(XOR_H, 1, 4),
	Instruction(XOR_L, 1, 4),
	Instruction(XOR_ptrHL, 1, 8),
	Instruction(XOR_A, 1, 4),
	Instruction(OR_B, 1, 4),
	Instruction(OR_C, 1, 4),
	Instruction(OR_D, 1, 4),
	Instruction(OR_E, 1, 4),
	Instruction(OR_H, 1, 4),
	Instruction(OR_L, 1, 4),
	Instruction(OR_ptrHL, 1, 8),
	Instruction(OR_A, 1, 4),
	Instruction(CP_B, 1, 4),
	Instruction(CP_C, 1, 4),
	Instruction(CP_D, 1, 4),
	Instruction(CP_E, 1, 4),
	Instruction(CP_H, 1, 4),
	Instruction(CP_L, 1, 4),
	Instruction(CP_ptrHL, 1, 8),
	Instruction(CP_A, 1, 4),
	Instruction(RET_NZ, 1, 20), // Worst case scenario for timing (20 ticks if it must make the jump. 8 ticks if not). We'll have to manually override the timing if jump is made (f_RET_flag returns bool?) 
	Instruction(POP_BC, 1, 12),
	Instruction(JP_NZ_u16, 3, 16), // Worst case scenario for timing (16 ticks if it must make the jump. 12 ticks if not). We'll have to manually override the timing if jump is made (f_JP_flag returns bool?)
	Instruction(JP_u16, 3, 16),
	Instruction(CALL_NZ_u16, 3, 24), // Worst case scenario for timing (24 ticks if it must make the jump, 12 ticks if not). We'll have to manually override the timing if jump is made (f_CALL_flag returns bool?)
	Instruction(PUSH_BC, 1, 16),
	Instruction(ADD_A_u8, 2, 8),
	Instruction(RST_0, 1, 16),
	Instruction(RET_Z, 1, 20), // Worst case scenario for timing (20 ticks if it must make the jump. 12 ticks if not). We'll have to manually override the timing if jump is made (f_RET_flag returns bool?)
	Instruction(RET, 1, 16),
	Instruction(JP_Z_u16, 3, 16), // Worst case scenario for timing (16 ticks if it must make the jump. 12 ticks if not). We'll have to manually override the timing if jump is made (f_JP_flag returns bool?)
	Instruction(CB_OFFSET, 0, 0),
	Instruction(CALL_Z_u16, 3, 24), // Worst case scenario for timing (24 ticks if it must make the jump. 12 ticks if not). We'll have to manually override the timing if jump is made (f_CALL_flag returns bool?)
	Instruction(CALL_u16, 3, 24),
	Instruction(ADC_A_u8, 2, 8),
	Instruction(RST_1, 1, 16),
	Instruction(RET_NC, 1, 20), // Worst case scenario for timing(20 ticks if it must make the jump. 12 ticks if not). We'll have to manually override the timing if jump is made (f_RET_flag returns bool?)
	Instruction(POP_DE, 1, 12),
	Instruction(JP_NC_u16, 3, 16), // Worst case scenario for timing (16 ticks if it must make the jump. 12 ticks if not). We'll have to manually override the timing if jump is made (f_JP_flag returns bool?)
	Instruction(ILLEGAL_0, 0, 0), // Illegal operation
	Instruction(CALL_NC_u16, 3, 24), // Worst case scenario for timing (24 ticks if it must make the jump. 12 ticks if not). We'll have to manually override the timing if jump is made (f_CALL_flag returns bool?)
	Instruction(PUSH_DE, 1, 16),
	Instruction(SUB_u8, 2, 8),
	Instruction(RST_2, 1, 16),
	Instruction(RET_C, 1, 20), // Worst case scenario for timing(20 ticks if it must make the jump. 12 ticks if not). We'll have to manually override the timing if jump is made (f_RET_flag returns bool?)
	Instruction(RETI, 1, 20),
	Instruction(JP_C_u16, 3, 16),
	Instruction(ILLEGAL_1, 0, 0),
	Instruction(CALL_C_u16, 3, 24), // Worst case scenario for timing (24 ticks if it must make the jump. 12 ticks if not). We'll have to manually override the timing if jump is made (f_CALL_flag returns bool?)
	Instruction(ILLEGAL_2, 0, 0),
	Instruction(SBC_A_u8, 2, 8),
	Instruction(RST_3, 1, 16),

	Instruction(LD_ptrU8_A, 2, 12),
	Instruction(POP_HL, 1, 12),
	Instruction(LD_ptrC_A, 1, 8),
	Instruction(ILLEGAL_3, 0, 0),
	Instruction(ILLEGAL_4, 0, 0),
	Instruction(PUSH_HL, 1, 16),
	Instruction(AND_u8, 2, 8),
	Instruction(RST_4, 1, 16),
	Instruction(ADD_SP_s8, 2, 16),
	Instruction(JP_HL, 1, 4),
	Instruction(LD_ptrU16_A, 3, 16),
	Instruction(ILLEGAL_5, 0, 0),
	Instruction(ILLEGAL_6, 0, 0),
	Instruction(ILLEGAL_7, 0, 0),
	Instruction(XOR_u8, 2, 8),
	Instruction(RST_5, 1, 16),

	Instruction(LD_A_ptrU8, 2, 12),
	Instruction(POP_AF, 1, 12),
	Instruction(LD_A_ptrC, 1, 8),
	Instruction(DI, 1, 4),
	Instruction(ILLEGAL_8, 0, 0),
	Instruction(PUSH_AF, 1, 16),
	Instruction(OR_u8, 2, 8),
	Instruction(RST_6, 1, 16),
	Instruction(LD_HL_SPaddU8, 2, 12),
	Instruction(LD_SP_HL, 1, 8),
	Instruction(LD_A_ptrU16, 3, 16),
	Instruction(EI, 1, 4),
	Instruction(ILLEGAL_9, 0, 0),
	Instruction(ILLEGAL_10, 0, 0),
	Instruction(RST_7, 1, 16)
};