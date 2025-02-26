#include "RAM.h"

RAM::RAM()
{
	this->ramBuf = new u8[RAM_SIZE + 1];
	memset(this->ramBuf, 0x00, RAM_SIZE);
}

RAM::~RAM()
{
#ifdef _DEBUG
	printf("Ram buffer deleted.\n");
#endif
	delete[] this->ramBuf;
}

u8 RAM::getItem(u16 address)
{
	return this->ramBuf[address];
}

void RAM::setItem(u16 address, u8 value)
{
	this->ramBuf[address] = value;
}

bool RAM::writeStringASCII(u16 address, std::string value)
{
	//TODO: Fix writeStringsASCII writing single character values to singular byte locations (for now use RAM::setItem)
	// Check length of string to ensure this is a valid write
	if (address + value.length() - 1 > RAM_SIZE)
	{
#ifdef _DEBUG
		printf("WriteStringsASCII failed. Attempted to over write buffer.\n");
		printf("String: %s, size: %zd bytes\n", value.c_str(), value.length());
		printf("Starting address: %04X (Maximum %d bytes possible)\n", address, (RAM_SIZE - address));
#endif
		return false;
	}
	
	// If write is valid, then write
	for (auto i = 0; i < value.length(); i++)
		this->ramBuf[address + i] = value[i];
	return true;
}

void RAM::setDebugValues()
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

bool RAM::dumpMemoryToFile(const std::string& filename)
{
	std::ofstream outFile(filename, std::ios::binary);
	if (!outFile)
	{
		printf("Unable to open file for writing\n");
		return false;
	}
	outFile.write(reinterpret_cast<const char*>(this->ramBuf), RAM_SIZE + 1);
	outFile.close();
#ifdef _DEBUG
	printf("RAM contents dumped to %s\n", filename.c_str());
#endif
	return true;
}