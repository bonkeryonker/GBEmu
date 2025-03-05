#include "CPU.h"

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
	u8 sp_lo = (this->registers.sp >> 8); // Low byte of SP
	u8 sp_hi = (this->registers.sp & 0xff); // High byte of SP
	this->m_ram_ptr->setItem(dest, sp_lo);
	this->m_ram_ptr->setItem(dest + 1, sp_hi);
}

void CPU::f_LD_ptr_r16_u8(const u16& addrSrcreg, u8 data)
{
	this->m_ram_ptr->setItem(addrSrcreg, data);
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

void CPU::f_ADD(const u8 srcReg)
{
	u8& regA = this->registers.a; // reference to accumulator register

	// reg 0x0F extracts lower nibble of byte
	// Add just the lower nibbles, and if it's bigger than 0x0F then a halfcarry occurred
	bool halfcarry = ((regA & 0x0F) + (srcReg & 0x0F)) > 0x0F;

	// Cast to u16 to check for overflow beyond 8 bits
	// Add the two bytes and if they're bigger than 0xFF then a carry occurred
	bool carry = ((u16)regA + (u16)srcReg) > 0xFF;

	// Perform the addition
	regA += srcReg;

	// Check if we should set the Z flag
	bool isZero = (regA == 0);

	// Set flags
	this->registers.setFlag(Z, isZero);
	this->registers.setFlag(N, false);
	this->registers.setFlag(H, halfcarry);
	this->registers.setFlag(C, carry);
}

void CPU::f_ADDC(const u8 srcReg)
{
	u8& regA = this->registers.a; // reference to accumulator register
	u8 carryFlagVal = (registers.isFlagSet(C)) ? 0x01 : 0x00;

	// reg 0x0F extracts lower nibble of byte
	// Add just the lower nibbles and the carry flag value, and if it's bigger than 0x0F then a halfcarry occurred
	bool halfcarry = ((regA & 0x0F) + (srcReg & 0x0F) + carryFlagVal) > 0x0F;

	// Cast to u16 to check for overflow beyond 8 bits
	// Add the two bytes and the carry flag value, and if they're bigger than 0xFF then a carry occurred
	bool carry = ((u16)regA + (u16)srcReg + carryFlagVal) > 0xFF;

	// Perform the addition
	regA += srcReg + carryFlagVal;

	// Check if we should set the Z flag
	bool isZero = (regA == 0);

	// Set flags
	this->registers.setFlag(Z, isZero);
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

void CPU::f_INC_ptr(const u16& reg)
{
	u8 originalVal = this->m_ram_ptr->getItem(reg);
	bool halfCarryFlag = ((originalVal & 0x0F) + 1) & 0x10;
	originalVal++;
	bool isZeroFlag = (reg == 0);
	this->m_ram_ptr->setItem(reg, originalVal);

	this->registers.setFlag(FLAGS::H, halfCarryFlag);
	this->registers.setFlag(FLAGS::Z, isZeroFlag);
	this->registers.setFlag(FLAGS::N, false);
}

void CPU::f_DEC_ptr(const u16& reg)
{
	u8 originalVal = this->m_ram_ptr->getItem(reg);
	bool halfCarryFlag = (originalVal & 0x0F) == 0;
	originalVal--;
	bool isZeroFlag = (reg == 0);
	this->registers.setFlag(H, halfCarryFlag);
	this->registers.setFlag(Z, isZeroFlag);
	this->registers.setFlag(N, true);
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

void CPU::f_HALT()
{
	this->m_isHalted = true;
	this->registers.pc++; // The system is halted at the operation after the halt instruction
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

void CPU::f_JR_flag(u8 steps, u8 FLAG, bool jumpIfFlag)
{
	if ((jumpIfFlag == this->registers.isFlagSet(FLAG)))
		this->f_JR_u8(steps);
	//else do nothing. PC will be incremented upon next fetch()
}

void CPU::f_DAA()
{
	if (!this->registers.isFlagSet(N)) // An addition occurred
	{
		if (this->registers.isFlagSet(C) || this->registers.a > 0x99) // If a carry occurred, or if a is greater than 0x99 (not BCD)
		{
			this->registers.a += 0x60;
			this->registers.setFlag(C);
		}
		if (this->registers.isFlagSet(H) || (this->registers.a & 0x0f) > 0x09) // If a halfcarry occurred, or if lower nibble is greater than 0x09
		{
			this->registers.a += 0x06;
		}
	}
	else // A subtraction occurred
	{
		if (this->registers.isFlagSet(C))
			this->registers.a -= 0x60;
		if (this->registers.isFlagSet(H))
			this->registers.a -= 0x06;
	}

	// Always update these flags with DAA
	this->registers.setFlag(H, false);
	this->registers.setFlag(Z, this->registers.a == 0x00);
}

void CPU::f_CPL()
{
	this->registers.a = ~(this->registers.a);
	this->registers.setFlag(N | H);
}