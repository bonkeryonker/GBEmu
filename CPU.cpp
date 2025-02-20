#include "CPU.h"

CPU::CPU(std::shared_ptr<RAM>& ram)
{
	this->registers.setDefaultValues();
	this->ram_ptr = ram;
}

unsigned short CPU::tick()
{	
	Instruction currentOp = opcodeLookup[this->fetch()];
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