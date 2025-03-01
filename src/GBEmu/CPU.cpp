#include "CPU.h"

CPU::CPU(std::shared_ptr<RAM>& ram)
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
		this->f_JR_NZ(this->getU8Immediate());
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
		//this->f_DAA();
		break;
	default:
		printf("Unknown opcode: %02X. Stopping.\n", opcode);
		this->m_isHalted = true;
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

/* Opcode Functions */
void CPU::f_NOP()
{
	return;
}

void CPU::f_LD(u16& destReg, const u16 data)
{
	destReg = data;
}

void CPU::f_LD(u8& destReg, const u8 data)
{
	destReg = data;
}

void CPU::f_LD_ptr(u16& ramAddrReg, u8& dataReg)
{
	this->m_ram_ptr->setItem(ramAddrReg, dataReg);
}

void CPU::f_LD_r8_ptr(u8& destReg, u16& dataReg)
{
	destReg = this->m_ram_ptr->getItem(dataReg);
}

void CPU::f_LD_u16_SP(u16 dest)
{
	u8 sp_lo = (this->registers.sp >> 8);
	u8 sp_hi = (this->registers.sp & 0xff);
	this->m_ram_ptr->setItem(dest, sp_lo);
	this->m_ram_ptr->setItem(dest + 1, sp_hi);
}

void CPU::f_ADD_r16_r16(u16& destReg, u16& srcReg)
{
	// reg & 0x0FFF extracts lower 12 bits of register
	// & 0x1000 checks if bit 12 is set. If so, then half carry.
	bool halfcarry = (((destReg & 0xFFF) + (srcReg & 0xFFF)) & 0x1000) == 0x1000;

	// Cast to u32 to ensure we check for overflow beyond 16 bits
	// & 0x10000 detects if 16th bit is set after addition
	bool carry = (((uint32_t)destReg + (uint32_t)srcReg) & 0x10000) == 0x10000;

	destReg += srcReg;

	this->registers.setFlag(N, false);
	this->registers.setFlag(H, halfcarry);
	this->registers.setFlag(C, carry);
}

void CPU::f_INC_r16(u16& reg)
{
	reg++;
}

void CPU::f_INC_r8(u8& reg)
{
	// reg & 0x0F extracts the lower nibble of the byte
	// & 0x10 checks if there was a carry from bit 3-4
	bool halfCarryFlag = ((reg & 0x0F) + 1) & 0x10;
	reg++;
	bool isZeroFlag = (reg == 0);
	this->registers.setFlag(FLAGS::H, halfCarryFlag);
	this->registers.setFlag(FLAGS::Z, isZeroFlag);
	this->registers.setFlag(FLAGS::N, false);
}

void CPU::f_DEC_r16(u16& reg)
{
	reg--;
}

void CPU::f_DEC_r8(u8& reg)
{
	// reg & 0x0F extracts the lower nibble of the byte
	// Check lower nibble == 0 to see if there's a decrement
	bool halfCarryFlag = (reg & 0x0F) == 0;
	reg--;
	bool isZeroFlag = (reg == 0);
	this->registers.setFlag(FLAGS::H, halfCarryFlag);
	this->registers.setFlag(FLAGS::Z, isZeroFlag);
	this->registers.setFlag(FLAGS::N, true);
}

void CPU::f_RLCA()
{
	bool a7BitIsHigh = (this->registers.a & 0x80) == 0x80; // Save the value of the A7 bit
	this->registers.a <<= 1; // Bitshift left
	this->registers.a |= (a7BitIsHigh) ? 0x01 : 0x00; // Wrap the preshift A7 bit around to A0
	this->registers.setFlag(Z | N | H, false); // Unset all relevant flags
	this->registers.setFlag(C, a7BitIsHigh); // Set the CY flag to the preshift value of A7
}

void CPU::f_RRCA()
{
	bool a0BitIsHigh = (this->registers.a & 0x01) == 0x01; // Save the value of the A0 bit
	this->registers.a >>= 1; // Bitshift right
	this->registers.a |= (a0BitIsHigh) ? 0x80 : 0x00; // Wrap the preshift A0 bit around to A7
	this->registers.setFlag(Z | N | H, false); // Unset all relevant flags
	this->registers.setFlag(C, a0BitIsHigh); // Set the CY flag to the preshift value of A0
}

void CPU::f_RLA()
{
	bool a7BitIsHigh = (this->registers.a & 0x80) == 0x80; 	// Save the value of the A7 bit
	bool carryFlagValue = (this->registers.f & C) == C; // Extract the value of the carry flag
	this->registers.a <<= 1; // Bitshift left
	this->registers.a |= (carryFlagValue) ? 0x01 : 0x00; // Set A0 to the value of CY
	this->registers.setFlag(Z | N | H, false); // Unset all relevant flags
	this->registers.setFlag(C, a7BitIsHigh); // Set the CY flag to the preshift value of A7
}

void CPU::f_RRA()
{
	bool a0BitIsHigh = (this->registers.a & 0x01) == 0x01; // Save the value of the A0 bit
	bool carryFlagValue = (this->registers.f & C) == C; // Extract the value of the carry flag
	this->registers.a >>= 1; // Bitshift right
	this->registers.a |= (carryFlagValue) ? 0x80 : 0x00; // Set A7 to the value of CY
	this->registers.setFlag(Z | N | H, false); // Unset all relevant flags
	this->registers.setFlag(C, a0BitIsHigh); // Set the CY flag to the preshift value of A0

}

void CPU::f_STOP(const u8 nextByte)
{
	if (nextByte == 0)
	{
		this->m_isHalted = true;
	}
}

void CPU::f_JR_u8(u8 steps)
{
	// The getU8Immediate() command used to fetch the steps variable increments PC by 1
	// so we'll have to decrement it before we actually jump that amount. I'm not sure if
	// this is how it works in hardware, so we may need to delete this line if it doesn't
	// work with actual ROMs.
	steps--;
	this->registers.pc += steps;
#ifdef _DEBUG
	printf("Jumped to %04X\n", this->registers.pc);
#endif
}

void CPU::f_JR_NZ(u8 steps)
{
	if (!this->registers.isFlagSet(Z))
		this->f_JR_u8(steps);
	//else do nothing. PC will be incremented upon next fetch()
}