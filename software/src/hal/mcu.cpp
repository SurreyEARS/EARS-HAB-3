/*
 * mcu.cpp
 *
 *  Created on: Nov 19, 2015
 *      Author: James
 */

#include <hal/generics.hpp>
#include <hal/gio.hpp>
#include <mal/stm32f303vc.hpp>

#include <stm32f3xx_hal_rcc.h>

/* Overflow time at 1ms approximately 49 years */
static uint32_t systemTicksMs = 0;

/* Cannot delay for more than this many ms.
 * If this is more than half the watchdog period,
 * everything will break. */
static const uint32_t maxDelay = 100;

static const HAL::GIO::Port statusPinPort = HAL::GIO::Port::PORTE;
static const uint32_t statusPin = 13U;

namespace HAL {
namespace MCU {

void init()
{
	using namespace MAL::CM4;
	using namespace HAL::GIO;

	SYSTICK.RELOAD.B.reload = HAL_RCC_GetHCLKFreq()/1000 - 1;
	SYSTICK.VAL = 0U;

	NVIC_SetPriority (SysTick_IRQn, (1<<__NVIC_PRIO_BITS) - 1);  /* set Priority for Systick Interrupt */

	SYSTICK.CTRL.B.clockSource = 1U;
	SYSTICK.CTRL.B.interrupt = 1U;
	SYSTICK.CTRL.B.enable = 1U;

	configurePin(statusPinPort, statusPin, Mode::OUTPUT, Pullups::PULL_UP, Type::PUSH_PULL, Speed::FAST, 0);
	configurePin(statusPinPort, statusPin + 1, Mode::OUTPUT, Pullups::PULL_UP, Type::PUSH_PULL, Speed::FAST, 0);
}

uint32_t getTicks(void) {
	return systemTicksMs;
}

void delayTicks(uint32_t delay) {
	uint32_t start = getTicks();
	uint32_t elapsed;

	if (delay > maxDelay) {
		delay = maxDelay;
	}

	do {
		elapsed = getTicks() - start;
	} while (elapsed < delay);
}

void SuspendTick(void) {
	MAL::CM4::SYSTICK.CTRL.B.interrupt = 0U;
}

void ResumeTick(void) {
	MAL::CM4::SYSTICK.CTRL.B.interrupt = 1U;
}

}
}

extern "C" {
void HAL_MCU_IncrementTicks(void)
{
	systemTicksMs++;

	if (0U == (systemTicksMs % 1000U))
	{
		HAL::GIO::toggle(statusPinPort, statusPin);
	}
}
}
