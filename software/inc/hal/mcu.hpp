/*
 * mcu.hpp
 *
 *  Created on: Nov 19, 2015
 *      Author: James
 */

#pragma once

#include <hal/generics.hpp>

namespace HAL {
namespace MCU {

void init();
uint32_t getTicks(void);

bool delayWhile(bool(*func)());
bool delayUntil(bool(*func)());
void delayTicks(uint32_t delay);

void SuspendTick(void);
void ResumeTick(void);

}
}
