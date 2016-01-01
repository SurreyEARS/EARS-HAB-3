#pragma once

/*
 * dac.hpp
 *
 *  Created on: Nov 25, 2015
 *      Author: James
 */

#include <hal/generics.hpp>

namespace HAL
{
namespace DAC
{

enum class Trigger
{
	HARDWARE, SOFTWARE, TIMER7
};

struct InitStruct
{

};

void configure(const InitStruct& config);
void configure(Trigger trig, bool dualMode, bool use12Bits) _deprec;

namespace SINGLE
{

void enable();
void disable();
void setData(uint16_t data);
void swTrigger();
void startDMA(uint16_t* sourceBuffer, uint16_t count);

}
}
}
