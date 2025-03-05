#include "CPU.h"

CPU::CPU(std::shared_ptr<Memory>& ram)
{
	this->m_isHalted = false;
	this->registers.setDefaultValues();
	this->m_ram_ptr = ram;
}

unsigned short CPU::tick()
{	
	Instruction currentOp = Instruction::opcodeLookup[this->fetch()];
	this->executeInstruction(currentOp.opcode);
	return currentOp.timing;
}

void CPU::executeInstruction(Mnemonic opcode)
{
	//printf("OP@%04X: %02X\n", this->registers.pc, opcode);
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