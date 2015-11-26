/*
 * mcu.cpp
 *
 *  Created on: Nov 19, 2015
 *      Author: James
 */

#include <hal/mcu.hpp>

#include <hal/generics.hpp>
#include <mal/stm32f303vc.hpp>

#include <hal/gio.hpp>
#include <hal/rcc.hpp>

/* Overflow time at 1ms approximately 49 years */
static uint32_t systemTicksMs = 0;

/* Cannot delay for more than this many ms.
 * If this is more than half the watchdog period,
 * everything will break. */
//TODO revert this value to 10ms
static const uint32_t maxDelay = 99999U;

static const HAL::GIO::Port statusPinPort = HAL::GIO::Port::PORTE;
static const uint32_t statusPin = 13U;

namespace HAL {
namespace MCU {

void init()
{
	using namespace MAL::CM4;
	using namespace HAL::GIO;

	SYSTICK.RELOAD.B.reload = HAL::RCCM::getSystemClock()/1000U - 1U;
	SYSTICK.VAL = 0U;

	SYSTICK.CTRL.B.clockSource = 1U;
	SYSTICK.CTRL.B.interrupt = 1U;
	SYSTICK.CTRL.B.enable = 1U;

	configurePin(statusPinPort, statusPin, Mode::OUTPUT, Pullups::PULL_UP, Type::PUSH_PULL, Speed::FAST, 0);
}

uint32_t getTicks(void) {
	return systemTicksMs;
}

bool delayWhile(bool(*func)())
{
	uint32_t start = getTicks();
	uint32_t elapsed;

	do {
		elapsed = getTicks() - start;
	} while (func() && elapsed < maxDelay);

	return elapsed < maxDelay;
}

bool delayUntil(bool(*func)())
{
	uint32_t start = getTicks();
	uint32_t elapsed;

	do {
		elapsed = getTicks() - start;
	} while (!func() && elapsed < maxDelay);

	return elapsed < maxDelay;
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

void SystemInit(void)
{
	/* Enable FPU access */
	MAL::CM4::SCB_CPA.CPACR.B.CP10 = 0x3U;
	MAL::CM4::SCB_CPA.CPACR.B.CP11 = 0x3U;

	/* Set the exception priority grouping - this splits exception handler priority into
	 * four bits of priority and four bits of sub-priority. Exceptions in the same priority
	 * group will not override each other; sub-priorities only order the exception queue. */
	MAL::CM4::SCB.AIRCR.B.PRIGROUP = 0x3U;

	/* Enable prefetching of code from flash. */
	MAL::F3C::FLASH.ACR.B.PRFTB_E = 1U;

	/* This line will need revisiting if we want to relocate vectors to RAM. For now, flash at offset 0 is fine.
	 * If you must modify the offset you must also do so in the stm32f30_flash.ld linker description file. */
	MAL::CM4::SCB.VTOR.R = 0x08000000 | 0x0; /* Flash base address and offset within flash */
}
}

