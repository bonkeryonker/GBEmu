#include "CPU.h"

CPU::CPU(std::shared_ptr<Memory>& ram)
{
	this->m_isHalted = false;
	this->m_IME = false; // IME begins unset
	this->m_stackSizeCounter = 0;
	// Initialize SP to high ram (0xFFFE) and PC to beginning of header (0x0100)
	this->registers.setDefaultValues();
	this->m_ram_ptr = ram;
}

unsigned short CPU::tick()
{	
	// TODO: Check and update interrupts
	// (https://www.reddit.com/r/EmuDev/comments/1hgupxq/gameboy_interrupts/)
	Instruction currentOp = Instruction::opcodeLookup[this->fetch()];
	printf("%04X : %02X\n", this->registers.pc - 1, currentOp.opcode);
	this->executeInstruction(currentOp.opcode);
	return currentOp.timing;
}

void CPU::executeInstruction(Mnemonic opcode)
{
	switch (opcode)
	{
	case NOP:
		this->f_NOP();
		break;
	case LD_BC_u16:
		this->f_LD(this->registers.bc, this->getU16Immediate());
		break;
	case LD_ptrBC_A:
		this->f_LD_ptr(this->registers.bc, this->registers.a);
		break;
	case INC_BC:
		this->f_INC_r16(this->registers.bc);
		break;
	case INC_B:
		this->f_INC_r8(this->registers.b);
		break;
	case DEC_B:
		this->f_DEC_r8(this->registers.b);
		break;
	case LD_B_u8:
		this->f_LD(this->registers.b, this->getU8Immediate());
		break;
	case RLCA:
		this->f_RLCA();
		break;
	case LD_a16_SP:
		this->f_LD_u16_SP(this->getU16Immediate());
		break;
	case ADD_HL_BC:
		this->f_ADD_r16_r16(this->registers.hl, this->registers.bc);
		break;
	case LD_A_ptrBC:
		this->f_LD_r8_ptr(this->registers.a, this->registers.bc);
		break;
	case DEC_BC:
		this->f_DEC_r16(this->registers.bc);
		break;
	case INC_C:
		this->f_INC_r8(this->registers.c);
		break;
	case DEC_C:
		this->f_DEC_r8(this->registers.c);
		break;
	case LD_C_u8:
		this->f_LD(this->registers.c, this->getU8Immediate());
		break;
	case RRCA:
		this->f_RRCA();
		break;
	case STOP:
		this->f_STOP(this->getU8Immediate());
		break;
	case LD_DE_u16:
		this->f_LD(this->registers.de, this->getU16Immediate());
		break;
	case LD_ptrDE_A:
		this->f_LD_ptr(this->registers.de, this->registers.a);
		break;
	case INC_DE:
		this->f_INC_r16(this->registers.de);
		break;
	case INC_D:
		this->f_INC_r8(this->registers.d);
		break;
	case DEC_D:
		this->f_DEC_r8(this->registers.d);
		break;
	case LD_D_u8:
		this->f_LD(this->registers.d, this->getU8Immediate());
		break;
	case RLA:
		this->f_RLA();
		break;
	case JR_u8:
		this->f_JR_u8(this->getU8Immediate());
		break;
	case ADD_HL_DE:
		this->f_ADD_r16_r16(this->registers.hl, this->registers.de);
		break;
	case LD_A_ptrDE:
		this->f_LD_r8_ptr(this->registers.a, this->registers.de);
		break;
	case DEC_DE:
		this->f_DEC_r16(this->registers.de);
		break;
	case INC_E:
		this->f_INC_r8(this->registers.e);
		break;
	case DEC_E:
		this->f_DEC_r8(this->registers.e);
		break;
	case LD_E_u8:
		this->f_LD(this->registers.e, this->getU8Immediate());
		break;
	case RRA:
		this->f_RRA();
		break;
	case JR_NZ:
		this->f_JR_flag(this->getU8Immediate(), Z, false);
		break;
	case LD_HL_u16:
		this->f_LD(this->registers.hl, this->getU16Immediate());
		break;
	case LD_ptrHLinc_A:
		this->f_LD_ptr(this->registers.hl, this->registers.a);
		this->f_INC_r16(this->registers.hl);
		break;
	case INC_HL:
		this->f_INC_r16(this->registers.hl);
		break;
	case INC_H:
		this->f_INC_r8(this->registers.h);
		break;
	case DEC_H:
		this->f_DEC_r8(this->registers.h);
		break;
	case LD_H_u8:
		this->f_LD(this->registers.h, this->getU8Immediate());
		break;
	case DAA:
		this->f_DAA();
		break;
	case JR_Z:
		this->f_JR_flag(this->getU8Immediate(), Z);
		break;
	case ADD_HL_HL:
		this->f_ADD_r16_r16(this->registers.hl, this->registers.hl);
		break;
	case LD_A_ptrHLinc:
		this->f_LD_r8_ptr(this->registers.a, this->registers.hl);
		this->f_INC_r16(this->registers.hl);
		break;
	case DEC_HL:
		this->f_DEC_r16(this->registers.hl);
		break;
	case INC_L:
		this->f_INC_r8(this->registers.l);
		break;
	case DEC_L:
		this->f_DEC_r8(this->registers.l);
		break;
	case LD_L_u8:
		this->f_LD(this->registers.l, this->getU8Immediate());
		break;
	case CPL:
		this->f_CPL();
		break;
	case JR_NC:
		this->f_JR_flag(this->getU8Immediate(), C, false);
		break;
	case LD_SP_u16:
		this->f_LD(this->registers.sp, this->getU16Immediate());
		break;
	case LD_ptrHLdec_A:
		this->f_LD_ptr(this->registers.hl, this->registers.a);
		this->f_DEC_r16(this->registers.hl);
		break;
	case INC_SP:
		this->f_INC_r16(this->registers.sp);
		break;
	case INC_ptrHL:
		this->f_INC_ptr(this->registers.hl);
		break;
	case DEC_ptrHL:
		this->f_DEC_ptr(this->registers.hl);
		break;
	case LD_ptrHL_u8:
		this->f_LD_ptr_r16_u8(this->registers.hl, this->getU8Immediate());
		break;
	case SCF:
		this->registers.setFlag(C);
		this->registers.setFlag(N | H, false);
		break;
	case JR_C:
		this->f_JR_flag(this->getU8Immediate(), C);
		break;
	case ADD_HL_SP:
		this->f_ADD_r16_r16(this->registers.hl, this->registers.sp);
		break;
	case LD_A_ptrHLdec:
		this->f_LD_r8_ptr(this->registers.a, this->registers.hl);
		this->f_DEC_r16(this->registers.hl);
		break;
	case DEC_SP:
		this->f_DEC_r16(this->registers.sp);
		break;
	case INC_A:
		this->f_INC_r8(this->registers.a);
		break;
	case DEC_A:
		this->f_DEC_r8(this->registers.a);
		break;
	case LD_A_u8:
		this->f_LD(this->registers.a, this->getU8Immediate());
		break;
	case CCF:
		this->registers.setFlag(C, !this->registers.isFlagSet(C));
		break;
	case LD_B_B:
		this->f_LD(this->registers.b, this->registers.b);
		break;
	case LD_B_C:
		this->f_LD(this->registers.b, this->registers.c);
		break;
	case LD_B_D:
		this->f_LD(this->registers.b, this->registers.d);
		break;
	case LD_B_E:
		this->f_LD(this->registers.b, this->registers.e);
		break;
	case LD_B_H:
		this->f_LD(this->registers.b, this->registers.h);
		break;
	case LD_B_L:
		this->f_LD(this->registers.b, this->registers.l);
		break;
	case LD_B_ptrHL:
		this->f_LD_r8_ptr(this->registers.b, this->registers.hl);
		break;
	case LD_B_A:
		this->f_LD(this->registers.b, this->registers.a);
		break;
	case LD_C_B:
		this->f_LD(this->registers.c, this->registers.b);
		break;
	case LD_C_C:
		this->f_LD(this->registers.c, this->registers.c);
		break;
	case LD_C_D:
		this->f_LD(this->registers.c, this->registers.d);
		break;
	case LD_C_E:
		this->f_LD(this->registers.c, this->registers.e);
		break;
	case LD_C_H:
		this->f_LD(this->registers.c, this->registers.h);
		break;
	case LD_C_L:
		this->f_LD(this->registers.c, this->registers.l);
		break;
	case LD_C_ptrHL:
		this->f_LD_r8_ptr(this->registers.c, this->registers.hl);
		break;
	case LD_C_A:
		this->f_LD(this->registers.c, this->registers.a);
		break;
	case LD_D_B:
		this->f_LD(this->registers.d, this->registers.b);
		break;
	case LD_D_C:
		this->f_LD(this->registers.d, this->registers.c);
		break;
	case LD_D_D:
		this->f_LD(this->registers.d, this->registers.d);
		break;
	case LD_D_E:
		this->f_LD(this->registers.d, this->registers.e);
		break;
	case LD_D_H:
		this->f_LD(this->registers.d, this->registers.h);
		break;
	case LD_D_L:
		this->f_LD(this->registers.d, this->registers.l);
		break;
	case LD_D_ptrHL:
		this->f_LD_r8_ptr(this->registers.d, this->registers.hl);
		break;
	case LD_D_A:
		this->f_LD(this->registers.d, this->registers.a);
		break;
	case LD_E_B:
		this->f_LD(this->registers.e, this->registers.b);
		break;
	case LD_E_C:
		this->f_LD(this->registers.e, this->registers.c);
		break;
	case LD_E_D:
		this->f_LD(this->registers.e, this->registers.d);
		break;
	case LD_E_E:
		this->f_LD(this->registers.e, this->registers.e);
		break;
	case LD_E_H:
		this->f_LD(this->registers.e, this->registers.h);
		break;
	case LD_E_L:
		this->f_LD(this->registers.e, this->registers.l);
		break;
	case LD_E_ptrHL:
		this->f_LD_r8_ptr(this->registers.e, this->registers.hl);
		break;
	case LD_E_A:
		this->f_LD(this->registers.e, this->registers.a);
		break;
	case LD_H_B:
		this->f_LD(this->registers.h, this->registers.b);
		break;
	case LD_H_C:
		this->f_LD(this->registers.h, this->registers.c);
		break;
	case LD_H_D:
		this->f_LD(this->registers.h, this->registers.d);
		break;
	case LD_H_E:
		this->f_LD(this->registers.h, this->registers.e);
		break;
	case LD_H_H:
		this->f_LD(this->registers.h, this->registers.h);
		break;
	case LD_H_L:
		this->f_LD(this->registers.h, this->registers.l);
		break;
	case LD_H_ptrHL:
		this->f_LD_r8_ptr(this->registers.h, this->registers.hl);
		break;
	case LD_H_A:
		this->f_LD(this->registers.h, this->registers.a);
		break;
	case LD_L_B:
		this->f_LD(this->registers.l, this->registers.b);
		break;
	case LD_L_C:
		this->f_LD(this->registers.l, this->registers.c);
		break;
	case LD_L_D:
		this->f_LD(this->registers.l, this->registers.d);
		break;
	case LD_L_E:
		this->f_LD(this->registers.l, this->registers.e);
		break;
	case LD_L_H:
		this->f_LD(this->registers.l, this->registers.h);
		break;
	case LD_L_L:
		this->f_LD(this->registers.l, this->registers.l);
		break;
	case LD_L_ptrHL:
		this->f_LD_r8_ptr(this->registers.l, this->registers.hl);
		break;
	case LD_L_A:
		this->f_LD(this->registers.l, this->registers.a);
		break;
	case LD_ptrHL_B:
		this->f_LD_ptr(this->registers.hl, this->registers.b);
		break;
	case LD_ptrHL_C:
		this->f_LD_ptr(this->registers.hl, this->registers.c);
		break;
	case LD_ptrHL_D:
		this->f_LD_ptr(this->registers.hl, this->registers.d);
		break;
	case LD_ptrHL_E:
		this->f_LD_ptr(this->registers.hl, this->registers.e);
		break;
	case LD_ptrHL_H:
		this->f_LD_ptr(this->registers.hl, this->registers.h);
		break;
	case LD_ptrHL_L:
		this->f_LD_ptr(this->registers.hl, this->registers.l);
		break;
	case HALT:
		this->f_HALT();
		break;
	case LD_ptrHL_A:
		this->f_LD_ptr(this->registers.hl, this->registers.a);
		break;
	case LD_A_B:
		this->f_LD(this->registers.a, this->registers.b);
		break;
	case LD_A_C:
		this->f_LD(this->registers.a, this->registers.c);
		break;
	case LD_A_D:
		this->f_LD(this->registers.a, this->registers.d);
		break;
	case LD_A_E:
		this->f_LD(this->registers.a, this->registers.e);
		break;
	case LD_A_H:
		this->f_LD(this->registers.a, this->registers.h);
		break;
	case LD_A_L:
		this->f_LD(this->registers.a, this->registers.l);
		break;
	case LD_A_ptrHL:
		this->f_LD_r8_ptr(this->registers.a, this->registers.hl);
		break;
	case LD_A_A:
		this->f_LD(this->registers.a, this->registers.a);
		break;
	case ADD_A_B:
		this->f_ADD(this->registers.b);
		break;
	case ADD_A_C:
		this->f_ADD(this->registers.c);
		break;
	case ADD_A_D:
		this->f_ADD(this->registers.d);
		break;
	case ADD_A_E:
		this->f_ADD(this->registers.e);
		break;
	case ADD_A_H:
		this->f_ADD(this->registers.h);
		break;
	case ADD_A_L:
		this->f_ADD(this->registers.l);
		break;
	case ADD_A_ptrHL:
		this->f_ADD(this->m_ram_ptr->getItem(this->registers.hl));
		break;
	case ADD_A_A:
		this->f_ADD(this->registers.a);
		break;
	case ADC_A_B:
		this->f_ADDC(this->registers.b);
		break;
	case ADC_A_C:
		this->f_ADDC(this->registers.c);
		break;
	case ADC_A_D:
		this->f_ADDC(this->registers.d);
		break;
	case ADC_A_E:
		this->f_ADDC(this->registers.e);
		break;
	case ADC_A_H:
		this->f_ADDC(this->registers.h);
		break;
	case ADC_A_L:
		this->f_ADDC(this->registers.l);
		break;
	case ADC_A_ptrHL:
		this->f_ADDC(this->m_ram_ptr->getItem(this->registers.hl));
		break;
	case ADC_A_A:
		this->f_ADDC(this->registers.a);
		break;
	case SUB_B:
		this->f_SUB(this->registers.b);
		break;
	case SUB_C:
		this->f_SUB(this->registers.c);
		break;
	case SUB_D:
		this->f_SUB(this->registers.d);
		break;
	case SUB_E:
		this->f_SUB(this->registers.e);
		break;
	case SUB_H:
		this->f_SUB(this->registers.h);
		break;
	case SUB_L:
		this->f_SUB(this->registers.l);
		break;
	case SUB_ptrHL:
		this->f_SUB(this->m_ram_ptr->getItem(this->registers.hl));
		break;
	case SUB_A:
		this->f_SUB(this->registers.a);
		break;
	case SBC_A_B:
		this->f_SBC(this->registers.b);
		break;
	case SBC_A_C:
		this->f_SBC(this->registers.c);
		break;
	case SBC_A_D:
		this->f_SBC(this->registers.d);
		break;
	case SBC_A_E:
		this->f_SBC(this->registers.e);
		break;
	case SBC_A_H:
		this->f_SBC(this->registers.h);
		break;
	case SBC_A_L:
		this->f_SBC(this->registers.l);
		break;
	case SBC_A_ptrHL:
		this->f_SBC(this->m_ram_ptr->getItem(this->registers.hl));
		break;
	case SBC_A_A:
		this->f_SBC(this->registers.a);
		break;
	case AND_B:
		this->f_AND(this->registers.b);
		break;
	case AND_C:
		this->f_AND(this->registers.c);
		break;
	case AND_D:
		this->f_AND(this->registers.d);
		break;
	case AND_E:
		this->f_AND(this->registers.e);
		break;
	case AND_H:
		this->f_AND(this->registers.h);
		break;
	case AND_L:
		this->f_AND(this->registers.l);
		break;
	case AND_ptrHL:
		this->f_AND(this->m_ram_ptr->getItem(this->registers.hl));
		break;
	case AND_A:
		this->f_AND(this->registers.a);
		break;
	case XOR_B:
		this->f_XOR(this->registers.b);
		break;
	case XOR_C:
		this->f_XOR(this->registers.c);
		break;
	case XOR_D:
		this->f_XOR(this->registers.d);
		break;
	case XOR_E:
		this->f_XOR(this->registers.e);
		break;
	case XOR_H:
		this->f_XOR(this->registers.h);
		break;
	case XOR_L:
		this->f_XOR(this->registers.l);
		break;
	case XOR_ptrHL:
		this->f_XOR(this->m_ram_ptr->getItem(this->registers.hl));
		break;
	case XOR_A:
		this->f_XOR(this->registers.a);
		break;
	case OR_B:
		this->f_OR(this->registers.b);
		break;
	case OR_C:
		this->f_OR(this->registers.c);
		break;
	case OR_D:
		this->f_OR(this->registers.d);
		break;
	case OR_E:
		this->f_OR(this->registers.e);
		break;
	case OR_H:
		this->f_OR(this->registers.h);
		break;
	case OR_L:
		this->f_OR(this->registers.l);
		break;
	case OR_ptrHL:
		this->f_OR(this->m_ram_ptr->getItem(this->registers.hl));
		break;
	case OR_A:
		this->f_OR(this->registers.a);
		break;
	case CP_B:
		this->f_CP(this->registers.b);
		break;
	case CP_C:
		this->f_CP(this->registers.c);
		break;
	case CP_D:
		this->f_CP(this->registers.d);
		break;
	case CP_E:
		this->f_CP(this->registers.e);
		break;
	case CP_H:
		this->f_CP(this->registers.h);
		break;
	case CP_L:
		this->f_CP(this->registers.l);
		break;
	case CP_ptrHL:
		this->f_CP(this->m_ram_ptr->getItem(this->registers.hl));
		break;
	case CP_A:
		this->f_CP(this->registers.a);
		break;
	case RET_NZ:
		this->f_RET_flag(Z, false);
		break;
	case POP_BC:
		this->f_POP(this->registers.bc);
		break;
	case JP_NZ_u16:
		this->f_JP_flag(this->getU16Immediate(), Z, false);
		break;
	case JP_u16:
		this->f_JP(this->getU16Immediate());
		break;
	case CALL_NZ_u16:
		this->f_CALL_flag(this->getU16Immediate(), Z, false);
		break;
	case PUSH_BC:
		this->f_PUSH(this->registers.bc);
		break;
	case ADD_A_u8:
		this->f_ADD(this->getU8Immediate());
		break;
	case RST_0:
		this->f_RST_n(0);
		break;
	case RET_Z:
		this->f_RET_flag(Z, true);
		break;
	case RET:
		this->f_RET();
		break;
	case JP_Z_u16:
		this->f_JP_flag(this->getU16Immediate(), Z, true);
		break;
	case CB_OFFSET:
		// offset opcode
		break;
	case CALL_Z_u16:
		this->f_CALL_flag(this->getU16Immediate(), Z, true);
		break;
	case CALL_u16:
		this->f_CALL(this->getU16Immediate());
		break;
	case ADC_A_u8:
		this->f_ADDC(this->getU8Immediate());
		break;
	case RST_1:
		this->f_RST_n(1);
		break;
	case RET_NC:
		this->f_RET_flag(C, false);
		break;
	case POP_DE:
		this->f_POP(this->registers.de);
		break;
	case JP_NC_u16:
		this->f_JP_flag(this->getU16Immediate(), C, false);
		break;
	case CALL_NC_u16:
		this->f_CALL_flag(this->getU16Immediate(), C, false);
		break;
	case PUSH_DE:
		this->f_PUSH(this->registers.de);
		break;
	case SUB_u8:
		this->f_SUB(this->getU8Immediate());
		break;
	case RST_2:
		this->f_RST_n(2);
		break;
	case RET_C:
		this->f_RET_flag(C, true);
		break;
	case RETI:
		this->setIME(true);
		this->f_RET();
		break;
	case JP_C_u16:
		this->f_JP_flag(this->getU16Immediate(), C, true);
		break;
	case CALL_C_u16:
		this->f_CALL_flag(this->getU16Immediate(), C, true);
		break;
	case SBC_A_u8:
		this->f_SBC(this->getU8Immediate());
		break;
	case RST_3:
		this->f_RST_n(3);
		break;
	case LD_ptrU8_A:
		this->m_ram_ptr->setItem((0xFF00 | this->getU8Immediate()), this->registers.a);
		break;
	case POP_HL:
		this->f_POP(this->registers.hl);
		break;
	case LD_ptrC_A:
		this->m_ram_ptr->setItem((0xFF00 | this->registers.c), this->registers.a);
		break;
	case PUSH_HL:
		this->f_PUSH(this->registers.hl);
		break;
	case AND_u8:
		this->f_AND(this->getU8Immediate());
		break;
	case RST_4:
		this->f_RST_n(4);
		break;
	case ADD_SP_s8:
		this->f_ADDSP((int8_t)this->getU8Immediate()); // Cast to signed integer
		break;
	case JP_HL:
		this->f_JP(this->registers.hl);
		break;
	case LD_ptrU16_A:
		this->m_ram_ptr->setItem(this->getU16Immediate(), this->registers.a);
		break;
	case XOR_u8:
		this->f_XOR(this->getU8Immediate());
		break;
	case RST_5:
		this->f_RST_n(5);
		break;
	case LD_A_ptrU8:
		this->f_LD(this->registers.a, this->m_ram_ptr->getItem(0xFF00 | this->getU8Immediate()));
		break;
	case POP_AF:
		this->f_POP(this->registers.af);
		break;
	case LD_A_ptrC:
		this->f_LD(this->registers.a, this->m_ram_ptr->getItem(0xFF00 | this->registers.c));
		break;
	case DI:
		this->setIME(false);
		break;
	case PUSH_AF:
		this->f_PUSH(this->registers.af);
		break;
	case OR_u8:
		this->f_OR(this->getU8Immediate());
		break;
	case RST_6:
		this->f_RST_n(6);
		break;
	case LD_HL_SPaddU8:
		this->f_ADDSP((int8_t)this->getU8Immediate(), this->registers.hl); // Cast to signed integer
		break;
	case LD_SP_HL:
		this->f_LD(this->registers.sp, this->registers.hl);
		break;
	case LD_A_ptrU16:
		this->f_LD(this->registers.a, this->m_ram_ptr->getItem(this->getU16Immediate()));
		break;
	case EI:
		this->setIME(true);
		break;
	case CP_u8:
		this->f_CP(this->getU8Immediate());
		break;
	case RST_7:
		this->f_RST_n(7);
		break;
	default: // Catch-all for any ILLEGAL_n opcodes
		this->f_ILLEGAL_OP(opcode);
		break;
	}
}

u8 CPU::fetch()
{
	return this->getU8Immediate();
}

u8 CPU::getU8Immediate()
{
	u8 retVal = this->m_ram_ptr->getItem(this->registers.pc);
	this->registers.pc++;
	return retVal;
}

u16 CPU::getU16Immediate()
{
	u8 low = this->getU8Immediate();
	u8 high = this->getU8Immediate();
	return ((u16)high << 8) | low;
}