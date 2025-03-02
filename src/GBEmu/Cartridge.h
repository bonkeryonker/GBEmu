#ifndef CART_H
#define CART_H
#include <memory>
#include <fstream>
#include "RAM.h"
#include "Globals.h"

static const u16 MAX_CARTSIZE = 0x7FFF;
static const u16 HEADER_CHECKSUM_ADDRESS = 0x014D;
static const u16 GLOBAL_CHECKSUM_ADDRESS = 0x014E; // Big endian, 0x014E is high byte

//TODO: Support for switchable ROM banks
class Cartridge
{
public:
	static bool loadFromFile(std::shared_ptr<RAM>& ram_ptr, const std::string& filepath);
	static bool validateChecksums(std::shared_ptr<RAM>& ram_ptr);

	// Modify the checksum value at runtime to the correct value
	static void overrideChecksums(std::shared_ptr<RAM>& ram_ptr);

private:
	// Calculate header checksum
	// Header checksum is the sum of all bytes from 0x0134 - 0x014C
	static u8 calculateHeaderChecksum(std::shared_ptr<RAM>& ram_ptr);

	// Calculate the global checksum
	// Global Checksum is the big endian sum of all bytes in ROM (not including checksum itself)
	static u16 calculateGlobalChecksum(std::shared_ptr<RAM>& ram_ptr);

	// Returns: TRUE if byte at CHECKSUM_ADDRESS == calculateChecksum()
	static bool validateHeaderChecksum(std::shared_ptr<RAM>& ram_ptr);

	static bool validateGlobalChecksum(std::shared_ptr<RAM>& ram_ptr);

};
#endif

