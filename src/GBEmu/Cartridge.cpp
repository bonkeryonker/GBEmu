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

u8 Cartridge::calculateChecksum(std::shared_ptr<RAM>& ram_ptr)
{
	u8 checksum = 0;
	for (u16 addr = 0x0134; addr <= 0x014C; addr++)
		checksum = checksum - ram_ptr->getItem(addr) - 1;

	return checksum;
}

void Cartridge::overrideChecksum(std::shared_ptr<RAM>& ram_ptr)
{
	ram_ptr->setItem(CHECKSUM_ADDRESS, Cartridge::calculateChecksum(ram_ptr));
}

bool Cartridge::validateChecksum(std::shared_ptr<RAM>& ram_ptr)
{
	return ram_ptr->getItem(CHECKSUM_ADDRESS) == Cartridge::calculateChecksum(ram_ptr);
}