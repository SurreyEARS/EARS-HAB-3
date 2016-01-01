/*
 * rcc.cpp
 *
 *  Created on: Nov 21, 2015
 *      Author: James
 */

#include <hal/rcc.hpp>

#include <mal/device.hpp>
#include <mal/device_rcc.hpp>
#include <hal/mcu.hpp>

#define MRCC (MAL::F3C::RCCMOD)

namespace HAL
{
namespace RCCM
{

static const uint32_t HSE_FREQ = 8000000U;
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
	//TODO Fix this so it works with things other than the default settings!
}

bool initClocks(void)
{
	/* We should probably check before destroying ALL THE CLOCKS, so if the PLL
	 * is activated (a side effect of this method), fail. PLL should never be
	 * set on reset unless someone is really messing around in startup.s.
	 */

	if (1U == MRCC.CR.B.PLLON)
	{
		return false;
	}

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
	MRCC.AHB_CLKEN.B.IOPA_EN = 1U;

	MRCC.AHB_CLKEN.B.DMA1_EN = 1U;
	MRCC.AHB_CLKEN.B.DMA2_EN = 1U;
	MRCC.AHB_CLKEN.B.CRC_EN = 1U;

	MRCC.APB1_CLKEN.B.DAC1_EN = 1U;
	MRCC.APB1_CLKEN.B.USB_EN = 1U;

	return true;
}
}
}
