#ifndef REGISTERS_H
#define REGISTERS_H
#include <cstdint>
#include <stdio.h>
#include "Globals.h"

/*
	TODO: Account for Big Endian machines

		This implementation assumes a little-endian system (such as Windows).
		All x86 machines SHOULD be little-endian, but eventually we should use some precompiler
		macros to modify the structs below to represent the system.
*/

enum FLAGS
{
	Z = 0x80, // Zero Flag
	N = 0x40, // Subtract Flag	
	H = 0x20, // Half-Carry Flag
	C = 0x10, // Carry Flag
};

// Struct containing u8/u16 unions representing each gameboy register.
struct REGISTERS {
	union {
		struct {
			u8 f; // Flags register (Low byte)
			u8 a; // Accumulator (Hi byte)
		};
		u16 af; // Combined 16-bit AF register
	};

	union {
		struct {
			u8 c; //Low
			u8 b; // Hi
		};
		u16 bc; // Combined
	};

	union {
		struct {
			u8 e; // Low
			u8 d; // Hi
		};
		u16 de; // Combined
	};

	union {
		struct {
			u8 l; // Low
			u8 h; // Hi
		};
		u16 hl; // Combined
	};

	u16 sp; // Stack Pointer
	u16 pc; // Program Counter

	// Set the flags passed in as arguments to the passed boolean value.
	// Multiple flags may be passed by means of bitwise OR operation
	// IE: setFlag(Z | N | H | C) sets all flags high
	void setFlag(u8 flag, bool setTrue = true)
	{
		if (setTrue)
			this->f |= flag;
		else
			this->f &= ~flag; // bitwise and with the complement of the flag
	}

	// Returns: TRUE if passed flag is set
	bool isFlagSet(u8 flag)
	{
		return this->f & flag;
	}

	void printAsHex()
	{
		printf("Registers:\n");
		printf("\tBC: $%02X%02X\n", b, c);
		printf("\tDE: $%02X%02X\n", d, e);
		printf("\tHL: $%02X%02X\n", h, l);
		printf("\tAF: $%02X%02X\n", a, f);
		printf("\tSP: $%04X\n", sp);
		printf("\tPC: $%04X\n", pc);
		printf("\tFlags: %c %c %c %c\n",
			isFlagSet(Z) ? 'Z' : '-',
			isFlagSet(N) ? 'N' : '-',
			isFlagSet(H) ? 'H' : '-',
			isFlagSet(C) ? 'C' : '-');
	}

	void setDefaultValues()
	{
		af = 0x0000;
		bc = 0x0000;
		de = 0x0000;
		hl = 0x0000;
		sp = 0xFFFE; // Typically where the SP begins
		pc = 0x0100; // Skip bootrom, start execution at beginning of header
	}
};

#endif