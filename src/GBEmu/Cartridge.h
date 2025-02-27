#ifndef CART_H
#define CART_H
#include <memory>
#include <fstream>
#include "RAM.h"

#define MAX_CARTSIZE 0x7FFF
//TODO: Support for switchable ROM banks

class Cartridge
{
public:
	static bool loadFromFile(std::shared_ptr<RAM>& ram_ptr, const std::string& filepath);
};
#endif

