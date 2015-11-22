#pragma once
/*
 * rcc.hpp
 *
 *  Created on: Nov 21, 2015
 *      Author: James
 */

#include <hal/generics.hpp>

namespace HAL
{
namespace RCCM
{

bool initClocks();
uint32_t getSystemClock();
uint32_t getHardwareClock();

}
}
