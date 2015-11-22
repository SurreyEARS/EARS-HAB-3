/*
 * rcc.cpp
 *
 *  Created on: Nov 21, 2015
 *      Author: James
 */

#include <hal/rcc.hpp>

#include <mal/stm32f303vc.hpp>
#include <hal/mcu.hpp>

#define MRCC (MAL::F3C::RCCMOD)

namespace HAL
{
namespace RCCM
{

static const bool HSE_EN = false;
static const uint32_t HSE_FREQ = 8000000U;

static const bool LSE_EN = false;
static const uint32_t LSE_FREQ = 32768U;

static bool isPLLRDY()
{
	return MRCC.CR.B.PLLRDY == 1U;
}

static bool isHSERDY()
{
	return MRCC.CR.B.HSERDY == 1U;
}

static bool isPLLSYSCLK()
{
	return MRCC.CFGR.B.SWS == 2U;
}

uint32_t getSystemClock()
{
	if (isPLLSYSCLK() && MRCC.CFGR.B.PLLSRC == 1U)
	{
		return HSE_FREQ * (MRCC.CFGR.B.PLLMUL + 2);
	}
}

uint32_t getHardwareClock()
{
	return getSystemClock();
}

bool initClocks(void)
{

	/* Clock settings are detailed below.

	 No external LS

	 HSE-> PLL x16 -> SYSCLK

	 This gives a 64MHz SYSCLK.

	 AHB PS = /1 - for a 64MHz bus
	 APB1 PS = /2 - for a 32MHz PCLK1
	 APB2 PS = /1

	 Peripherals clocked (in addition to system defaults):
	 GPIO*
	 DMA1, DMA2
	 */

	/* It is assumed that this function will only be called once; it assumes
	 * that the current values of the registers are the same as those defined
	 * in the reference manual.
	 */

	if (1U == MRCC.CR.B.PLLON)
	{
		return false;
	}

	/*
	 * We should probably check before destroying ALL THE CLOCKS, so if the PLL
	 * is activated (a side effect of this method), fail. PLL should never be
	 * set on reset unless someone is really messing around in startup.s.
	 */

	/* This is critical. Tells the processor to insert wait states
	 * when talking to the flash memory. Two is the appropriate number
	 * of wait states for 48MHz < SYSCLK < 72MHz. */
	MAL::F3C::FLASH.ACR.B.LATENCY = 2;

	/* HSE starts disabled, so these steps are relatively safe.
	 * We'll be using an 8MHz external and pumping the core bus to 72MHz. */
	MRCC.CR.B.HSEBYP = 1U;
	MRCC.CR.B.HSEON = 1U;
	/* Wait for stable clock */
	if (!HAL::MCU::delayUntil(&isHSERDY))
	{
		/* Timed out instead of getting a stable signal. */
		return false;
	}

	/* Activate the PLL in much the same way. Configure the PLL to take
	 * HSE as an input without dividing down, and output HSEx9 */
	MRCC.CFGR.B.PLLMUL = 0b111;

	/* THIS IS CORRECT, PLLSRC IS ONLY ONE BIT */
	MRCC.CFGR.B.PLLSRC = 1U;

	MRCC.CR.B.PLLON = 1U;
	/* Wait for stable clock */
	if (!HAL::MCU::delayUntil(&isPLLRDY))
	{
		/* Timed out instead of getting a stable signal. */
		return false;
	}

	/* Scale the HCLK frequency to 36 for the low speed bus */
	MRCC.CFGR.B.PPRE1 = 0b11;

	/* Finally, set the source of the system clock to the newly stable PLL.*/
	MRCC.CFGR.B.SW = 2U;

	HAL::MCU::delayUntil(&isPLLSYSCLK);

	MRCC.AHB_CLKEN.B.IOPE_EN = 1U;
	MRCC.AHB_CLKEN.B.DMA1_EN = 1U;
	MRCC.AHB_CLKEN.B.DMA2_EN = 1U;

	return true;
}
}
}
