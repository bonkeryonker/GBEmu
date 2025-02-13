#ifndef REGISTERS_H
#define REGISTERS_H
#include <cstdint>
#include <stdio.h>

/*
	TODO: Account for Big Endian machines
		
		This implementation assumes a little-endian system (such as Windows).
		All x86 machines SHOULD be little-endian, but eventually we should use some precompiler
		macros to modify the structs below to represent the system.
*/
namespace CPU
{
	struct {
		union {
			struct {
				uint8_t f; // Flags register (Low byte)
				uint8_t a; // Accumulator (Hi byte)
			};
			uint16_t af; // Combined 16-bit AF register
		};

		union {
			struct {
				uint8_t c; //Low
				uint8_t b; // Hi
			};
			uint16_t bc; // Combined
		};

		union {
			struct {
				uint8_t e; // Low
				uint8_t d; // Hi
			};
			uint16_t de; // Combined
		};

		union {
			struct {
				uint8_t l; // Low
				uint8_t h; // Hi
			};
			uint16_t hl; // Combined
		};

		uint16_t sp; // Stack Pointer
		uint16_t pc; // Program Counter

		void printAsHex()
		{
			printf("%02X %02X\n", a, f);
			printf("%02X %02X\n", b, c);
			printf("%02X %02X\n", d, e);
			printf("%02X %02X\n", h, l);
			printf("%04X\n", sp);
			printf("%04X\n", pc);
		}
	}REGISTERS;
}

#endif