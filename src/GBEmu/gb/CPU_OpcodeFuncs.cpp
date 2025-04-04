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

void CPU::f_ADDSP(const int8_t signedInt)
{
	u16& spRef = this->registers.sp;
	
	// reg & 0x0F extracts lower nibble of byte
	// Check if 8bit half carry
	bool halfcarry = ((spRef & 0x0F) + (signedInt & 0x0F)) > 0x0F;
	bool carry = ((spRef & 0xFF) + (signedInt & 0xFF) > 0xFF);

	this->registers.sp += signedInt;

	this->registers.setFlag(Z | N, false);
	this->registers.setFlag(H, halfcarry);
	this->registers.setFlag(C, carry);
}

void CPU::f_ADDSP(const int8_t signedInt, u16& destReg)
{
	u16& spRef = this->registers.sp;

	// reg & 0x0F extracts lower nibble of byte
	// Check if 8bit half carry
	bool halfcarry = ((spRef & 0x0F) + (signedInt & 0x0F)) > 0x0F;
	bool carry = ((spRef & 0xFF) + (signedInt & 0xFF) > 0xFF);

	destReg = this->registers.sp + signedInt;

	this->registers.setFlag(Z | N, false);
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

void CPU::f_SUB(const u8 srcReg)
{
	bool halfCarry = (this->registers.a & 0x0F) < (srcReg & 0x0F); // Half carry if lower nibble of a < lower nibble of srcReg
	bool carry = this->registers.a < srcReg; // Carry if a is less than srcReg
	bool isZeroFlag = this->registers.a == srcReg; // Sub will equal zero
	this->registers.a -= srcReg;

	this->registers.setFlag(Z, isZeroFlag);
	this->registers.setFlag(N, true);
	this->registers.setFlag(H, halfCarry);
	this->registers.setFlag(C, carry);
}

void CPU::f_SBC(const u8 srcReg)
{
	u8 carryVal = (this->registers.isFlagSet(C)) ? 0x01 : 0x00;
	bool halfCarry = (this->registers.a & 0x0F) < ((srcReg & 0x0F) + carryVal);
	bool carry = (this->registers.a < (srcReg + carryVal));
	bool isZeroFlag = (this->registers.a - srcReg - carryVal) == 0;
	this->registers.a -= (srcReg + carryVal);

	this->registers.setFlag(Z, isZeroFlag);
	this->registers.setFlag(N, true);
	this->registers.setFlag(H, halfCarry);
	this->registers.setFlag(C, carry);
}

void CPU::f_AND(const u8 srcReg)
{
	this->registers.a &= srcReg;
	bool isZeroFlag = this->registers.a == 0;

	this->registers.setFlag(H, true);
	this->registers.setFlag(Z, isZeroFlag);
	this->registers.setFlag(N | C, false);
}

void CPU::f_XOR(const u8 srcReg)
{
	this->registers.a ^= srcReg;
	bool isZeroFlag = this->registers.a == 0;

	this->registers.setFlag(Z, isZeroFlag);
	this->registers.setFlag(N | H | C, false);
}

void CPU::f_OR(const u8 srcReg)
{
	this->registers.a |= srcReg;
	bool isZeroFlag = this->registers.a == 0;

	this->registers.setFlag(Z, isZeroFlag);
	this->registers.setFlag(N | H | C, false);
}

void CPU::f_CP(const u8 srcReg)
{
	bool halfCarry = (this->registers.a & 0x0F) < (srcReg & 0x0F); // Half carry if lower nibble of a < lower nibble of srcReg
	bool carry = this->registers.a < srcReg; // Carry if a is less than srcReg
	bool isZeroFlag = this->registers.a == srcReg; // Sub will equal zero

	this->registers.setFlag(Z, isZeroFlag);
	this->registers.setFlag(N, true);
	this->registers.setFlag(H, halfCarry);
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
	this->registers.setFlag(CPU_FLAGS::H, halfCarryFlag);
	this->registers.setFlag(CPU_FLAGS::Z, isZeroFlag);
	this->registers.setFlag(CPU_FLAGS::N, false);
}

void CPU::f_INC_ptr(const u16& reg)
{
	u8 originalVal = this->m_ram_ptr->getItem(reg);
	bool halfCarryFlag = ((originalVal & 0x0F) + 1) & 0x10;
	originalVal++;
	bool isZeroFlag = (reg == 0);
	this->m_ram_ptr->setItem(reg, originalVal);

	this->registers.setFlag(CPU_FLAGS::H, halfCarryFlag);
	this->registers.setFlag(CPU_FLAGS::Z, isZeroFlag);
	this->registers.setFlag(CPU_FLAGS::N, false);
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
	this->registers.setFlag(CPU_FLAGS::H, halfCarryFlag);
	this->registers.setFlag(CPU_FLAGS::Z, isZeroFlag);
	this->registers.setFlag(CPU_FLAGS::N, true);
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

void CPU::f_JR_s8(int8_t steps)
{
	// The getU8Immediate() command used to fetch the steps variable increments PC by 1
	// so we'll have to decrement it before we actually jump that amount. I'm not sure if
	// this is how it works in hardware, so we may need to delete this line if it doesn't
	// work with actual ROMs.
	//steps--;
	this->registers.pc += steps;
}

void CPU::f_JR_flag(int8_t steps, u8 FLAG, bool jumpIfFlag)
{
	if ((jumpIfFlag == this->registers.isFlagSet(FLAG)))
		this->f_JR_s8(steps);
	else //do nothing. PC will be incremented upon next fetch()
	{
#ifdef _DEBUG
		printf("Didn't jump to %04X because of flag value.\n", this->registers.pc + steps);
#endif
	}
}

void CPU::f_JP(u16 destAddr)
{
	this->registers.pc = destAddr;
}

void CPU::f_JP_flag(u16 destAddr, u8 FLAG, bool jumpIfFlag)
{
	if (this->registers.isFlagSet(FLAG) == jumpIfFlag)
		this->f_JP(destAddr);
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

void CPU::f_RET()
{
	// Subtract one to account for extra fetch() incrementing PC
	this->registers.pc--;
	this->f_POP(this->registers.pc);
}

void CPU::f_RET_flag(u8 FLAG, bool retIfFlag)
{
	if (this->registers.isFlagSet(FLAG) == retIfFlag)
		this->f_RET();
	// else do nothing. PC will be incremented upon next fetch()
}

void CPU::f_PUSH(const u16 srcReg)
{
	this->m_ram_ptr->setItem(this->registers.sp - 1, (srcReg & 0xFF00) >> 8); // Push high byte of srcReg
	this->m_ram_ptr->setItem(this->registers.sp - 2, srcReg & 0x00FF); // Push low byte of srcReg
	this->registers.sp -= 2; // Decrement SP by two
#ifdef _DEBUG
	this->m_stackSizeCounter++;
	printf("Pushed %02X%02X to stack.\nStack size: %u, SP: %04X\n", (srcReg & 0xFF00) >> 8, (srcReg & 0x00FF), (this->m_stackSizeCounter), (this->registers.sp));
#endif
}

void CPU::f_POP(u16& destReg)
{
	u8 lowByte = this->m_ram_ptr->getItem(this->registers.sp);
	u8 highByte = this->m_ram_ptr->getItem(this->registers.sp + 1);
	destReg = lowByte;
	destReg |= (highByte) << 8;
	this->registers.sp += 2;

#ifdef _DEBUG
	this->m_stackSizeCounter--;
	printf("Popped %04X from stack.\nStack size: %u, SP: %04X\n", destReg, (this->m_stackSizeCounter), (this->registers.sp));
#endif
}

void CPU::f_CALL(const u16 callAddr)
{
	this->f_PUSH(this->registers.pc);
	this->registers.pc = callAddr;
}

void CPU::f_CALL_flag(const u16 callAddr, u8 FLAG, bool callIfFlag)
{
	if (this->registers.isFlagSet(FLAG) == callIfFlag)
		this->f_CALL(callAddr);
	// else do nothing. PC will be incremented upon next fetch()
}

void CPU::f_RST_n(u8 n)
{
	this->f_PUSH(this->registers.pc);
	switch (n)
	{
	case 0:
		this->registers.pc = 0x0000;
		break;
	case 1:
		this->registers.pc = 0x0008;
		break;
	case 2:
		this->registers.pc = 0x0010;
		break;
	case 3:
		this->registers.pc = 0x0018;
		break;
	case 4:
		this->registers.pc = 0x0020;
		break;
	case 5:
		this->registers.pc = 0x0028;
		break;
	case 6:
		this->registers.pc = 0x0030;
		break;
	case 7:
		this->registers.pc = 0x0038;
		break;
	default:
		this->registers.pc = 0x0000;
		this->m_isHalted = true;
#ifdef _DEBUG
		printf("Invalid reset code %d. Halting.\n", n);
#endif
		break;

	}
}

void CPU::f_ILLEGAL_OP(const u8 opcode)
{
	printf("Illegal opcode %02X encountered at memory address %04X\n Halting.\n", opcode, this->registers.pc - 1);
	this->m_isHalted = true;
}