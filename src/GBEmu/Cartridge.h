#ifndef CART_H
#define CART_H
#include <memory>
#include <fstream>
#include "RAM.h"
#include "Globals.h"

#define MAX_CARTSIZE 0x7FFF

static const u16 CHECKSUM_ADDRESS = 0x014D;

//TODO: Support for switchable ROM banks
class Cartridge
{
public:
	static bool loadFromFile(std::shared_ptr<RAM>& ram_ptr, const std::string& filepath);
	static u8 calculateChecksum(std::shared_ptr<RAM>& ram_ptr);
	static bool validateChecksum(std::shared_ptr<RAM>& ram_ptr);

	// Modify the checksum value at runtime to the correct value
	static void overrideChecksum(std::shared_ptr<RAM>& ram_ptr);
};
#endif

