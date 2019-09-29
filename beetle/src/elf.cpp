#include "../elf.hpp"

BEETLE::ELFHelper::ELFHelper(const uint8_t* const elfDataBuffer)
{
	setElfDataBuffer(elfDataBuffer);
}

void BEETLE::ELFHelper::setElfDataBuffer(const uint8_t* newElfDataBuffer)
{
	m_elfDataBuffer = newElfDataBuffer;
	reinitElfHeader();
}

void BEETLE::ELFHelper::reinitElfHeader()
{

}