/*
 * nvc.cpp
 *
 *  Created on: Dec 23, 2015
 *      Author: James
 */

#pragma once
#include <hal/generics.hpp>

namespace HAL
{
namespace NVC
{

constexpr const uint32_t flashBaseAddress = 0x08000000U;
constexpr const uint32_t maxAddress = 0x08040000U;
constexpr const uint32_t pageSize = 0x800U;

constexpr const uint32_t allowableEraseAreaStart = 0x08030000U;
constexpr const uint32_t allowableEraseAreaEnd = 0x08040000U;

namespace PHY
{
bool isBusy();
void unlock();
void lock();
bool program(void* address, uint16_t val);
bool verify(void* address, uint16_t val);
bool verifyBlock(void* start, void* checkBuffer, uint32_t size);
bool erasePage(void* startAddress);
}

enum class RecordId
	: uint16_t
	{
		NO_RECORD = 0xFFFF, PAGE_HEADER = 0x0,

		GPS_POSITION, FAULT_LOG,

		NVC_TEST_RECORD = 0xFFFE
};

struct RecordHeader_t
{
	RecordId id;
	uint16_t crc;
	uint16_t size;
};

constexpr const uint32_t recordHeaderDataOffset = sizeof(RecordHeader_t) / 2U;

bool read(RecordHeader_t* record, uint32_t location);
bool write(RecordHeader_t* record, uint32_t location);

bool test();
}
}

