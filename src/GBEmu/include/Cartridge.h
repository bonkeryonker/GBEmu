#ifndef CART_H
#define CART_H
#include <memory>
#include <fstream>
#include "Globals.h"

//TODO: Support for switchable ROM banks
//TODO: reimplement header checksum functions
class Cartridge
{
public:

	// Allocates MAX_CARTSIZE bytes on the heap, and sets them all to 0x00
	Cartridge();

	// Delete[]'s the rom buffer
	~Cartridge();

	// Open the ROM at pathToRom and load it into romBuf
	bool loadROM(const std::string& pathToRom);

	// Returns the byte at the specified address in memory
	u8 getItem(u16 address);

	// Outputs the full contents of RAM to a binary file
	bool dumpRomToFile(const std::string& filename = "../../bin/memdumps/rom_dump.bin");

private:
	u8* romBuf;
};
#endif

