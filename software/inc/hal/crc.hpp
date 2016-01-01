/*
 * crc.hpp
 *
 *  Created on: Dec 22, 2015
 *      Author: James
 */

#pragma once

#include <hal/generics.hpp>

namespace HAL
{
namespace CRC
{

enum class PolynomialSize
	: uint8_t
	{
		BITS_7 = 0x3U, BITS_8 = 0x2U, BITS_16 = 0x1U, BITS_32 = 0x0U
};

enum class DefaultPolynomial
	: uint8_t
	{
		CRC16_CCITT, CRC32C, NUM_VALUES
};

struct InitStruct
{
	struct
	{
		DefaultPolynomial type;
		uint32_t polynomial;
		uint32_t initValue;
		PolynomialSize polynomialSize;
		PolynomialSize dataSize;
	} defaults[uint8_t(DefaultPolynomial::NUM_VALUES)];
};

void configure(const InitStruct& config);
bool test();

uint32_t crc(DefaultPolynomial settings, const void* data, uint32_t numBytes);

}
}

