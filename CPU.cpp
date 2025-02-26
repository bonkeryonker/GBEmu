#include "CPU.h"

CPU::CPU(std::shared_ptr<RAM>& ram)
{
	this->registers.setDefaultValues();
	this->ram_ptr = ram;
}

unsigned short CPU::tick()
{	
	Instruction currentOp = Instruction::opcodeLookup[this->fetch()];
	switch (currentOp.opcode)
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
		//f_RRCA
		break;
	}

	return currentOp.timing;
}

u8 CPU::fetch()
{
	return this->getU8Immediate();
}

u8 CPU::getU8Immediate()
{
	u8 retVal = this->ram_ptr->getItem(this->registers.pc);
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

void CPU::f_LD(u16& destReg, u16 data)
{
	destReg = data;
}

void CPU::f_LD(u8& destReg, u8 data)
{
	destReg = data;
}

void CPU::f_LD_ptr(u16& ramAddrReg, u8& dataReg)
{
	this->ram_ptr->setItem(ramAddrReg, dataReg);
}

void CPU::f_LD_r8_ptr(u8& destReg, u16& dataReg)
{
	destReg = this->ram_ptr->getItem(dataReg);
}

void CPU::f_LD_u16_SP(u16 dest)
{
	u8 sp_lo = (this->registers.sp >> 8);
	u8 sp_hi = (this->registers.sp & 0xff);
	this->ram_ptr->setItem(dest, sp_lo);
	this->ram_ptr->setItem(dest + 1, sp_hi);
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
	bool a7BitIsHigh = (this->registers.a & 0x80) == 0x80;
	this->registers.a <<= 1;
	this->registers.a |= (a7BitIsHigh) ? 0x01 : 0x00;
	this->registers.setFlag(Z | N | H, false);
	this->registers.setFlag(C, a7BitIsHigh);
}

void CPU::f_RRCA()
{
	bool a0BitIsHigh = (this->registers.a & 0x01) == 0x01;
	this->registers.a >>= 1;
	this->registers.a |= (a0BitIsHigh) ? 0x80 : 0x00;
	this->registers.setFlag(Z | N | H, false);
	this->registers.setFlag(C, a0BitIsHigh);
}