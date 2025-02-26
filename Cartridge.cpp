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