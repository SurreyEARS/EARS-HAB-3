/*
 * mcu.cpp
 *
 *  Created on: Nov 19, 2015
 *      Author: James
 */

#include <hal/mcu.hpp>

#include <hal/generics.hpp>
#include <mal/device.hpp>

#include <hal/gio.hpp>
#include <hal/rcc.hpp>

static uint64_t systemTicksMs = 0;

/* Cannot delay for more than this many ms.
 * If this is more than half the watchdog period,
 * everything will break. */
//IMPROVE revert this value to 10ms
sconst uint32_t maxDelay = 99999U;

sconst HAL::GIO::Port statusPort = HAL::GIO::Port::PORTE;
sconst uint32_t statusPin = 13U;
sconst uint32_t errorPin = 9U;

namespace HAL
{
namespace MCU
{

void init()
{
	using namespace MAL::CM4;
	using namespace HAL::GIO;

	SYSTICK.RELOAD.B.reload = HAL::RCCM::getSystemClock() / 1000U - 1U;
	SYSTICK.VAL = 0U;

	SYSTICK.CTRL.B.clockSource = 1U;
	SYSTICK.CTRL.B.interrupt = 1U;
	SYSTICK.CTRL.B.enable = 1U;
}

uint64_t getTicks(void)
{
	return systemTicksMs;
}

uint64_t getMicroseconds(void)
{
	/* Justification:
	 * The current microseconds value is the current ticks in ms plus progress to the nex tick.
	 * Progress to the next tick is counted down, so ((RELOAD-VAL)/RELOAD)
	 * Equivalent to 1-VAL/RELOAD
	 * All multiplied by 1000
	 *
	 * To simplify logic, add one to systick - assume we have already ticked
	 * Then SUBTRACT the countdown/reload
	 */
	using namespace MAL::CM4;
	return (1000 * (systemTicksMs + 1) - (SYSTICK.VAL * 1000 / SYSTICK.RELOAD.B.reload));
}

bool delayWhile(bool (*func)())
{
	uint64_t start = getTicks();
	uint64_t elapsed;

	do
	{
		elapsed = getTicks() - start;
	} while (func() && elapsed < maxDelay);

	return elapsed < maxDelay;
}

bool delayUntil(bool (*func)())
{
	uint64_t start = getTicks();
	uint64_t elapsed;

	do
	{
		elapsed = getTicks() - start;
	} while (!func() && elapsed < maxDelay);

	return elapsed < maxDelay;
}

void delayTicks(uint32_t delay)
{
	uint64_t start = getTicks();
	uint64_t elapsed;

	if (delay > maxDelay)
	{
		delay = maxDelay;
	}

	do
	{
		elapsed = getTicks() - start;
	} while (elapsed < delay);
}

void delayMicroseconds(uint32_t delay)
{
	uint64_t start = getMicroseconds();
	uint64_t elapsed;

	if ((delay/1000U) > maxDelay)
	{
		delay = maxDelay*1000U;
	}

	do
	{
		elapsed = getMicroseconds() - start;
	} while (elapsed < delay);
}

void SuspendTick(void)
{
	MAL::CM4::SYSTICK.CTRL.B.enable = 0U;
}

void ResumeTick(void)
{
	MAL::CM4::SYSTICK.CTRL.B.enable = 1U;
}

}
}

extern "C"
{
void HAL_MCU_IncrementTicks(void)
{
	systemTicksMs++;

	if (0U == (systemTicksMs % 1000U))
	{
		HAL::GIO::toggle(statusPort, statusPin);
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

