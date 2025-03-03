#include <stdio.h>
#include <iostream>
#include <memory>
#include <functional>
#include "Clock.h"
#include "Registers.h"
#include "CPU.h"
#include "RAM.h"
#include "Cartridge.h"

void ramTestLD1(std::shared_ptr<RAM>& ram_ptr, CPU& c);
void testIncDec(std::shared_ptr<RAM>& ram_ptr, CPU& c);
void testRotateLeft(std::shared_ptr<RAM>& ram_ptr, CPU& c);
void testAddR16R16(std::shared_ptr<RAM>& ram_ptr, CPU& c);

int main()
{
	std::shared_ptr<RAM> ram_ptr = std::make_shared<RAM>();
	CPU c(ram_ptr);

	// Load ROM
	Cartridge::loadFromFile(ram_ptr, "../../bin/testROMs/testCPL.gb");
	if (!Cartridge::validateChecksums(ram_ptr))
	{
		printf("Invalid ROM checksum(s). Overriding...\n");
		Cartridge::overrideChecksums(ram_ptr);
		//return 1;
	}
	printf("ROM checksums good!\n");

	// Begin ROM execution
	while (!c.isHalted())
	{
		Clock::tick(c);
	}

	// Finish up
	c.registers.printAsHex();
	printf("Halted: %s\n", c.isHalted() ? "TRUE" : "FALSE");
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

void testAddR16R16(std::shared_ptr<RAM>& ram_ptr, CPU& c)
{
	int casesPassed = 0;
	ram_ptr->setItem(0x00, ADD_HL_BC);
	uint16_t hlTestCases[] = {      0x0FFF, 0x7FFF, 0x8FFF, 0x8FFF, 0xFFFF, 0x1234, 0x1FFF, 0xF000 };
	uint16_t bcTestCases[] = {      0x0001, 0x0001, 0x1000, 0x2000, 0x0001, 0x5678, 0x0001, 0x1000 };
	uint16_t testCaseResult[] = {   0x1000, 0x8000, 0x9FFF, 0xAFFF, 0x0000, 0x68AC, 0x2000, 0x0000 };
	uint8_t expectedFRegister[] = { 0x20,   0x20,   0x00,   0x00,   0x30,   0x00,   0x20,   0x10 };

	for (int i = 0; i < 8; i++)
	{
		c.registers.pc = 0;
		c.registers.hl = hlTestCases[i];
		c.registers.bc = bcTestCases[i];
		c.tick();
		if (c.registers.f == expectedFRegister[i])
		{
			printf("Test (%d/8): success!\n", i + 1);
			casesPassed++;
		}
		else
		{
			printf("Test (%d/8): Failed!\n\n", i + 1);
			printf("%04X + %04X = %04X\n", hlTestCases[i], bcTestCases[i], c.registers.hl);
			printf("Flags: %02X\nExpected: %02X\n", c.registers.f, expectedFRegister[i]);
			break;
		}
	}
	
}