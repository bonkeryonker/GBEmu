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

	void printAsHex()
	{
		printf("%02X %02X\n", a, f);
		printf("%02X %02X\n", b, c);
		printf("%02X %02X\n", d, e);
		printf("%02X %02X\n", h, l);
		printf("%04X\n", sp);
		printf("%04X\n", pc);
	}

	void setDefaultValues()
	{
		af = 0xdead;
		bc = 0xbeef;
		de = 0xbabe;
		hl = 0xface;
		sp = 0xfeed;
		pc = 0x0000;
	}
};

#endif