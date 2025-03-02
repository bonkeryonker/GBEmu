#include "Cartridge.h"
 
bool Cartridge::loadFromFile(std::shared_ptr<RAM>& ram_ptr, const std::string& filepath)
{
	u16 writeAddress = 0;
	u16 bytesWritten = 0;
	std::ifstream romFile(filepath, std::ios::binary);
	if (!romFile.is_open())
	{
		printf("Unable to open rom: %s for reading.\n", filepath.c_str());
		return false;
	}
	
	while (!romFile.eof() && writeAddress < MemoryMap::VRAM)
	{
		ram_ptr->setItem(writeAddress, romFile.get());
		writeAddress++;
		bytesWritten++;
	}
#ifdef _DEBUG
	printf("%d bytes written to ram.\n", bytesWritten);
#endif
		romFile.close();
}

bool Cartridge::validateChecksums(std::shared_ptr<RAM>& ram_ptr)
{
	return Cartridge::validateHeaderChecksum(ram_ptr) && Cartridge::validateGlobalChecksum(ram_ptr);
}

u8 Cartridge::calculateHeaderChecksum(std::shared_ptr<RAM>& ram_ptr)
{
	u8 checksum = 0;
	for (u16 addr = 0x0134; addr <= 0x014C; addr++)
		checksum = checksum - ram_ptr->getItem(addr) - 1;

	return checksum;
}

u16 Cartridge::calculateGlobalChecksum(std::shared_ptr<RAM>& ram_ptr)
{
	u16 checksum = 0;
	for (u16 addr = 0; addr <= MAX_CARTSIZE; addr++)
	{
		// Don't add the two checksum bytes to the checksum
		if (!(addr == 0x014E || addr == 0x014F))
		{
			checksum += ram_ptr->getItem(addr);
		}
	}
	return checksum;
}

void Cartridge::overrideChecksums(std::shared_ptr<RAM>& ram_ptr)
{
	u16 globalChecksum = Cartridge::calculateGlobalChecksum(ram_ptr);
	ram_ptr->setItem(HEADER_CHECKSUM_ADDRESS, Cartridge::calculateHeaderChecksum(ram_ptr));
	ram_ptr->setItem(GLOBAL_CHECKSUM_ADDRESS, (globalChecksum & 0xff00) >> 8);
	ram_ptr->setItem(GLOBAL_CHECKSUM_ADDRESS + 1, globalChecksum & 0x00ff);
}

bool Cartridge::validateHeaderChecksum(std::shared_ptr<RAM>& ram_ptr)
{
	return ram_ptr->getItem(HEADER_CHECKSUM_ADDRESS) == Cartridge::calculateHeaderChecksum(ram_ptr);
}

bool Cartridge::validateGlobalChecksum(std::shared_ptr<RAM>& ram_ptr)
{
	u16 checksum = (ram_ptr->getItem(GLOBAL_CHECKSUM_ADDRESS) << 8);
	checksum |= ram_ptr->getItem(GLOBAL_CHECKSUM_ADDRESS + 1);
	return checksum == Cartridge::calculateGlobalChecksum(ram_ptr);
}