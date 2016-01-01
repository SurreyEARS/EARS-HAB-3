/*
 * crc.cpp
 *
 *  Created on: Dec 22, 2015
 *      Author: James
 */

#include <hal/crc.hpp>
#include <mal/device.hpp>

#include <cstring>

namespace HAL {
namespace CRC {

using MAL::F3C::CRC;

constexpr const static uint32_t resetTimeout = 0x128U;
static const InitStruct* config = nullptr;

uint32_t crc (DefaultPolynomial poly, const void* data, uint32_t bytes)
{
	/* Shortcuts for byte and half-word access to the data register */
	static uint8_t* const dr8 = (uint8_t*)&CRC.DR;
	static uint16_t* const dr16 = (uint16_t*)&CRC.DR;
	static uint32_t* const dr32 = (uint32_t*)&CRC.DR;

	if (nullptr == config)
	{
		return 0xDEADBEEF;
	}

	CRC.INIT = config->defaults[uint8_t(poly)].initValue;
	CRC.POL = config->defaults[uint8_t(poly)].polynomial;
	CRC.CR.B.POLYSIZE = uint8_t(config->defaults[uint8_t(poly)].polynomialSize);

	CRC.CR.B.RESET = 1U;
	uint32_t timeout = resetTimeout;
	while (--timeout && (1U == CRC.CR.B.RESET));

	/* Indicate the maximum allowable data width */
	bool allow16 = false, allow32 = false;

	/* Decide data width based on the value in the Independent Data Register */
	switch ((PolynomialSize)CRC.CR.B.POLYSIZE)
	{
	case PolynomialSize::BITS_7:
		/* Assume we can do 8-bit data sizes */
		break;
	case PolynomialSize::BITS_8:
		break;
	case PolynomialSize::BITS_16:
		allow16 = true;
		break;
	case PolynomialSize::BITS_32:
		allow16 = true;
		allow32 = true;
		break;
	}

	/* Keep track of bytes processed THIS LOOP */
	uint32_t bytesProcessed = 0U;

	/* A byte pointer is more useful than a void one */
	uint8_t* d = ((uint8_t*)data);

	while (bytes > 0)
	{
		if (allow32 && bytes >= 4)
		{
			/* Cast the pointer, then dereference, then byteswap,
			 * then assign to the data register. */
			*dr32 = __builtin_bswap32(*((uint32_t*)d));
			bytesProcessed = 4;
		}
		else if (allow16 && bytes >= 2)
		{
			/* As per 32-bit example */
			*dr16 = __builtin_bswap16(*((uint16_t*)d));
			bytesProcessed = 2;
		}
		else if (bytes >= 1)
		{
			/* No byteswap here for obvious reasons. */
			*dr8 = *((uint8_t*)d);
			bytesProcessed = 1;
		}

		d += bytesProcessed;
		bytes -= bytesProcessed;
		bytesProcessed = 0;
	}

	return CRC.DR;
}

void configure (const InitStruct& data)
{
	config = &data;
}

bool test()
{
	/* Test of 51 ASCII characters in UKHAS/spacenear.us format. Example and result taken
	 * from the UKHAS wiki and verified with an online calculator. */
	const char* crcData = "hadie,181,10:42:10,54.422829,-6.741293,27799.3,1:10";
	const uint16_t data = 0x0U;
	bool pass = true;

	pass = (HAL::CRC::crc(DefaultPolynomial::CRC16_CCITT, &data, 2) == 0x1D0F) && pass;
	pass = (HAL::CRC::crc(DefaultPolynomial::CRC16_CCITT, &data, 1) == 0xE1F0) && pass;
	pass = (HAL::CRC::crc(DefaultPolynomial::CRC16_CCITT, crcData, 51) == 0x002A) && pass;
	return pass;
}

}
}


