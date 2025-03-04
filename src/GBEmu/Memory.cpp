#include "Memory.h"

Memory::Memory(std::shared_ptr<Cartridge>& cart_ptr)
{
	this->cart_ptr = cart_ptr;
	this->ramBuf = new u8[RAM_SIZE + 1];
	for (auto i = 0; i <= RAM_SIZE; i++)
		this->ramBuf[i] = 0x00;
}

Memory::~Memory()
{
#ifdef _DEBUG
	printf("Ram buffer deleted.\n");
#endif
	delete[] this->ramBuf;
}

u8 Memory::getItem(u16 address)
{
	if (Memory::isRomAddress(address)) // Lower address than VRAM, must be on cart ROM
		return this->cart_ptr->getItem(address);
	else
		return this->ramBuf[normalizeAddress(address)];
}

bool Memory::setItem(u16 address, u8 value)
{
	if (Memory::isRomAddress(address))
		return false;

	this->ramBuf[normalizeAddress(address)] = value;
	return true;
}

void Memory::setDebugValues()
{
	this->writeStringASCII(ROMBANK00, "ROMBANK00");
	this->writeStringASCII(ROMBANK01_N, "ROMBANK01_N");
	this->writeStringASCII(VRAM, "VRAM");
	this->writeStringASCII(EXTERNALRAM, "EXTERNALRAM");
	this->writeStringASCII(WRAM0, "WRAM0");
	this->writeStringASCII(WRAM1, "WRAM1");
	this->writeStringASCII(ECHO, "ECHO");
	this->writeStringASCII(OAM, "OAM");
	this->writeStringASCII(FORBIDDEN, "FORBIDDEN");
	this->writeStringASCII(IO, "IO");
	this->writeStringASCII(HRAM, "HRAM");
	this->writeStringASCII(IE, "I");
}

bool Memory::dumpMemoryToFile(const std::string& filename, bool dumpCartridge)
{
	if(dumpCartridge)
		this->cart_ptr->dumpRomToFile(filename);

	// If we're dumping the cart too, then binary | append. Otherwise, just binary ofstream flag.
	auto streamFlags = (dumpCartridge) ? (std::ios::binary | std::ios::app) : (std::ios::binary);

	std::ofstream outFile(filename, streamFlags);
	if (!outFile)
	{
		printf("Unable to open file for writing\n");
		return false;
	}
	outFile.write(reinterpret_cast<const char*>(this->ramBuf), RAM_SIZE);
	outFile.close();
#ifdef _DEBUG
	printf("RAM contents dumped to %s\n", filename.c_str());
#endif
	return true;
}

u16 Memory::normalizeAddress(u16 address)
{
	return address - VRAM; // VRAM, offset 0x8000, maps to [0] of ramBuf. Lower values reside on cart
}