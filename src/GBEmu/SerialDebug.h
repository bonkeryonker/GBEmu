#ifndef SERIALDEBUG_H
#define SERIALDEBUG_H
#include <memory>
#include "Globals.h"
#include "Memory.h"

class SerialDebug
{
public:
	SerialDebug(std::shared_ptr<Memory>& ram_ptr);
	SerialDebug() = delete; // will never be generated, default constructor forbidden

	u8 readByte();
	bool serialTransferComplete();
private:
	u8 prevByte;
	std::shared_ptr<Memory> m_ram_ptr;
};
#endif
