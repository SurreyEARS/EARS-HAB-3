/*
 * nvc_phy.cpp
 *
 *  Created on: Dec 24, 2015
 *      Author: James
 */

#include <hal/nvc.hpp>

#include <mal/device.hpp>
#include <hal/mcu.hpp>

namespace HAL
{
namespace NVC
{
namespace PHY
{

/** Is the flash ready to perform a new operation?
 * @return false if the controller is busy or locked.
 */
static bool isReady()
{
	return (0U == MAL::F3C::FLASH.SR.B.BSY) && (0U == MAL::F3C::FLASH.CR.B.LOCK);
}

/** Is the flash in the middle of an operation?
 * Use this to loop until an operation completes.
 * @see HAL::MCU::delayWhile
 * @return false if the controller is busy or locked.
 */
bool isBusy()
{
	return 1U == MAL::F3C::FLASH.SR.B.BSY;
}

/** Release the flash lock bit, allowing further writes/erases.
 * @see lock
 */
void unlock()
{
	using MAL::F3C::FLASH;

	if (1U == MAL::F3C::FLASH.CR.B.LOCK)
	{
		FLASH.KEYR = 0x45670123U;
		FLASH.KEYR = 0xCDEF89ABU;
	}
}

/** Set the flash lock bit, preventing further writes/erases.
 * @see unlock
 */
void lock()
{
	using MAL::F3C::FLASH;

	if (0U == MAL::F3C::FLASH.CR.B.LOCK)
	{
		FLASH.CR.B.LOCK = 1U;
	}
}

/** Write a single 16-bit value to a flash location.
 * Location must previously have been erased.
 * @param address location of the data to write
 * @param val data to program
 * @return true if the operation was started and flash indicates EOP.
 */
bool program(void* address, uint16_t val)
{
	using MAL::F3C::FLASH;

	if (!isReady())
	{
		return false;
	}

	FLASH.CR.B.PG = 1U;
	*((uint16_t*)address) = val;

	if (!HAL::MCU::delayWhile(&isBusy))
	{
		return false;
	}

	if (1U == FLASH.SR.B.EOP)
	{
		FLASH.SR.B.EOP = 0U;
		return true;
	}
	return false;
}

/** Compare a single 16-bit value with a passed value.
 * @param address location of the data to verify
 * @param val data to compare with
 * @see verifyBlock
 * @return true if the flash and passed values match
 */
bool verify(void* address, uint16_t val)
{
	return (*((uint16_t*)address) = val);
}

/** Compare a block of 16-bit values with a passed block.
 * @param start location of the data to verify
 * @param checkBuffer data to compare with
 * @param size the number of 16-bit values to compare
 * @return true if the flash and passed values match
 */
bool verifyBlock(void* start, void* checkBuffer, uint32_t size)
{
	uint16_t* check16 = (uint16_t*) checkBuffer;
	uint16_t* start16 = (uint16_t*) start;

	for (uint16_t* addr = start16; addr < start16 + size; ++addr, ++check16)
	{
		if ((*addr) != (*check16))
		{
			return false;
		}
	}
	return true;
}

/** Erase the page starting at the passed address.
 * @return true if the flash indicates EOP.
 */
bool erasePage(void* pageStartAddress)
{
	using MAL::F3C::FLASH;

	if (!isReady())
	{
		return false;
	}

	if (0U != (uint32_t(pageStartAddress) % 2048U))
	{
		return false;
	}

	if ((HAL::NVC::allowableEraseAreaStart > uint32_t(pageStartAddress))
			|| (HAL::NVC::allowableEraseAreaEnd < uint32_t(pageStartAddress)))
	{
		return false;
	}

	FLASH.CR.B.PER = 1U;
	FLASH.AR = uint32_t(pageStartAddress);
	FLASH.CR.B.STRT = 1U;

	if (!HAL::MCU::delayWhile(&isBusy))
	{
		return false;
	}

	if (1U == FLASH.SR.B.EOP)
	{
		FLASH.SR.B.EOP = 0U;
		FLASH.CR.B.PER = 0U;
		return true;
	}

	FLASH.CR.B.PER = 0U;
	return false;
}

}
}
}
