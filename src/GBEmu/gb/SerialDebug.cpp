#include "SerialDebug.h"

SerialDebug::SerialDebug(std::shared_ptr<Memory>& ram_ptr)
{
	this->m_ram_ptr = ram_ptr;
	this->prevByte = this->readByte();
}

bool SerialDebug::serialTransferComplete()
{
	u8 scByte = this->m_ram_ptr->getItem(MemoryMap::SC);
	return scByte == 0x81;
}

u8 SerialDebug::readByte()
{
	u8 newbyte = this->m_ram_ptr->getItem(MemoryMap::SB);
	this->prevByte = newbyte; // copy
	this->m_ram_ptr->setItem(MemoryMap::SC, 0xFF); // Send control byte for disconnected link cable
	return newbyte;
}