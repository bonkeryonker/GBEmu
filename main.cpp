#include <stdio.h>
#include <memory>
#include <functional>
#include "Clock.h"
#include "Registers.h"
#include "CPU.h"
#include "RAM.h"

void ramTestLD1(std::shared_ptr<RAM>& ram_ptr, CPU& c);
void testIncDec(std::shared_ptr<RAM>& ram_ptr, CPU& c);
void testRotateLeft(std::shared_ptr<RAM>& ram_ptr, CPU& c);

int main()
{
	std::shared_ptr<RAM> ram_ptr = std::make_shared<RAM>();
	CPU c(ram_ptr);
	ram_ptr->setItem(0x00, LD_a16_SP);
	ram_ptr->setItem(0x01, 0x00);
	ram_ptr->setItem(0x02, 0x80);
	c.registers.sp = 0xbeef;
	c.tick();
	ram_ptr->dumpMemoryToFile();
	return 0;
}

void ramTestLD1(std::shared_ptr<RAM>& ram_ptr, CPU& c)
{
	ram_ptr->setItem(ROMBANK00, LD_BC_u16);
	ram_ptr->setItem(ROMBANK00 + 1, 0x00);
	ram_ptr->setItem(ROMBANK00 + 2, 0x80);
	ram_ptr->setItem(ROMBANK00 + 3, LD_ptrBC_A);
	c.registers.a = 0xA1;

	// Run
	c.tick();
	c.tick();
}

void testIncDec(std::shared_ptr<RAM>& ram_ptr, CPU& c)
{
	ram_ptr->setItem(ROMBANK00, INC_B);
	bool testResult;

	//Increment test
	c.registers.b = 0x0F;
	c.tick();
	testResult = (c.registers.f == 0x20); //true flags: H
	printf("Flags: %02X\nExpected: 20\n\n", c.registers.f);
	if (!testResult)
	{
		printf("Failed!\n\n");
		return;
	}
	else
		printf("Success!\n\n");
	
	//reset pc
	c.registers.pc = 0;
	c.registers.b = 0xFF;
	c.tick();
	testResult = (c.registers.f == 0xA0); //true flags: Z, H
	printf("Flags: %02X\nExpected: A0\n\n", c.registers.f);
	if (!testResult)
	{
		printf("Failed!\n\n");
		return;
	}
	else
		printf("Success!\n\n");

	//Decrement test
	//reset pc
	ram_ptr->setItem(ROMBANK00, DEC_B);
	c.registers.pc = 0;
	c.registers.b = 0x10;
	c.tick();
	testResult = (c.registers.f == 0x60); //true flags: N, H
	printf("Flags: %02X\nExpected: 60\n\n", c.registers.f);
	if (!testResult)
	{
		printf("Failed!\n\n");
		return;
	}
	else
		printf("Success!\n\n");

	c.registers.pc = 0;
	c.registers.b = 0x01;
	c.tick();
	testResult = (c.registers.f == 0xC0); //true flags: Z, N
	printf("Flags: %02X\nExpected: C0\n\n", c.registers.f);
	if (!testResult)
	{
		printf("Failed!\n\n");
		return;
	}
	else
		printf("Success!\n\n");

	c.registers.pc = 0;
	c.registers.b = 0x00;
	c.tick();
	testResult = (c.registers.f == 0x60); //true flags: N, H
	printf("Flags: %02X\nExpected: 60\n\n", c.registers.f);
	if (!testResult)
	{
		printf("Failed!\n\n");
		return;
	}
	else
		printf("Success!\n\n");

}

void testRotateLeft(std::shared_ptr<RAM>& ram_ptr, CPU& c)
{
	bool testResult;
	ram_ptr->setItem(ROMBANK00, RLCA);
	c.registers.pc = 0;
	c.registers.a = 0x81;
	c.tick();
	testResult = (c.registers.f == 0x10); // set flags: C
	printf("Flags: %02X\nExpected: 10\n\n", c.registers.f);
	if (!testResult)
	{
		printf("Failed!\n\n");
		return;
	}
	else
		printf("Success!\n\n");

	c.registers.pc = 0;
	c.registers.a = 0x01;
	c.tick();
	testResult = (c.registers.f == 0x00);
	printf("Flags: %02X\nExpected: 00\n\n", c.registers.f);
	if (!testResult)
	{
		printf("Failed!\n\n");
		return;
	}
	else
		printf("Success!\n\n");
}