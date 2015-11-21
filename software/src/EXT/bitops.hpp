/*
 * bitops.hpp
 *
 *  Created on: Nov 20, 2015
 *      Author: James
 */

#pragma once

#include <HAL/generics.hpp>

/* remove this to disable bounds and size checking on bitops */
#define DEBUG_BITOPS

void set_bit(volatile uint32_t& target, uint32_t bit, uint32_t val)
{
#ifdef DEBUG_BITOPS
	if (bit > 31) { while(1); }
	if (val > 1) { while(1); }
#endif
	if (val)
	{
		target |= 1 << bit;
	}
	else
	{
		target &= ~(1 << bit);
	}
}
void set_bit(volatile uint16_t& target, uint32_t bit, uint32_t val)
{
#ifdef DEBUG_BITOPS
	if (bit > 15) { while(1); }
	if (val > 1) { while(1); }
#endif
	if (val)
	{
		target |= 1 << bit;
	}
	else
	{
		target &= ~(1 << bit);
	}
}

void set_bit2(volatile uint32_t& target, uint32_t field, uint32_t val)
{
#ifdef DEBUG_BITOPS
	if (val > 3) { while(1); }
	if (field > 15) { while(1); }
#endif

	target &= ~(0x3 << 2*field);
	target |= val << 2*field;
}

void set_bit2(volatile uint16_t& target, uint32_t field, uint32_t val)
{
#ifdef DEBUG_BITOPS
	if (val > 3) { while(1); }
	if (field > 7) { while(1); }
#endif

	target &= ~(0x3 << 2*field);
	target |= val << 2*field;
}
