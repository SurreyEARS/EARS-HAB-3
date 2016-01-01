/*
 * mcu.hpp
 *
 *  Created on: Nov 19, 2015
 *      Author: James
 */

#pragma once

#include <hal/generics.hpp>

namespace HAL
{
namespace MCU
{

void init();
uint64_t getTicks(void);
uint64_t getMicroseconds(void);

bool delayWhile(bool (*func)());
bool delayUntil(bool (*func)());
void delayTicks(uint32_t delay);
void delayMicroseconds(uint32_t delay);

void SuspendTick(void);
void ResumeTick(void);

}
}
