/*
 * nvm.cpp
 *
 *  Created on: Dec 23, 2015
 *      Author: James
 */

#include <hal/nvc.hpp>

#include <hal/crc.hpp>

#include <cstring>

namespace HAL
{
namespace NVC
{

bool read(void* source, RecordHeader_t* destination, uint32_t size)
{
	uint32_t* dst = (uint32_t*)destination;
	uint32_t* src = (uint32_t*)source;

	if ((nullptr != source) && (nullptr != destination))
	{
		memcpy(dst, src, size);
		return true;
	}
	return false;
}

bool write(RecordHeader_t* source, void* destination)
{
	bool ret = true;

	/* We don't include the header in the CRC block, and we must also modify the expected record size accordingly */
	source->crc = HAL::CRC::crc(CRC::DefaultPolynomial::CRC16_CCITT, ((uint16_t*)source + recordHeaderDataOffset), source->size - recordHeaderDataOffset);

	PHY::unlock();

	if (0xFFFF != *((uint16_t*)destination))
	{
		/* TODO implement read-erase-write on full pages */
		uint32_t dest = (uint32_t)destination;
		void* pageAddress = (void*)(dest - (dest % 2048U));
		PHY::erasePage(pageAddress);
	}

	uint16_t* dst = (uint16_t*)destination;
	uint16_t* src = (uint16_t*)source;

	for (uint32_t i = 0; i < source->size; ++i, ++dst, ++src)
	{
		if (!PHY::program(dst, *src))
		{
			ret = false;
			break;
		}
	}

	uint16_t checksum = HAL::CRC::crc(CRC::DefaultPolynomial::CRC16_CCITT, ((uint16_t*)destination + recordHeaderDataOffset), source->size - recordHeaderDataOffset);

	if (ret && PHY::verifyBlock((uint16_t*)destination, (uint16_t*)source, source->size) && source->crc == checksum)
	{
		ret = true;
	}
	else
	{
		ret = false;
	}

	PHY::lock();
	return ret;
}

struct NVCTestStruct_t {
	RecordHeader_t header;
	uint8_t byte;
	uint16_t shrt;
	uint32_t uint;
	uint32_t sentinel;
};

bool test()
{
	NVCTestStruct_t testStruct = {
			{
					RecordId::NVC_TEST_RECORD,
					0U,
					sizeof(NVCTestStruct_t)
			},
			127U,
			0x2476U,
			0xFE6509AAU,
			0xDEADBEEFU
	};

	NVCTestStruct_t testStructRead;

	if (write((RecordHeader_t*)&testStruct, (void*)0x08035000U))
	{
		if (read((RecordHeader_t*)0x08035000U, (RecordHeader_t*)&testStructRead, sizeof(NVCTestStruct_t)))
		{
			if (memcmp(&testStruct, &testStructRead, sizeof(NVCTestStruct_t)) == 0)
			{
				return true;
			}
		}
	}

	return false;
}

}
}
