/*
 * dac.cpp
 *
 *  Created on: Nov 25, 2015
 *      Author: James
 */

#include <mal/device.hpp>

#include <hal/dma.hpp>
#include <hal/dac.hpp>

namespace HAL
{
namespace DAC
{

static bool inDualMode = false;
static Trigger trigger = Trigger::HARDWARE;
static bool usingDMA = false;
static bool bits12 = false;

/* For 8 bit mode, this would store 0000 0000 1111 1111. See setData. */
static uint16_t bitModeMask = 0;

void configure(Trigger trig, bool dualMode, bool use12Bits)
{
	/* Enable the output buffer */
	MAL::F3C::DAC.CR.B.BOFF_OUTEN1 = 1U;

	trigger = trig;
	if (trigger != Trigger::HARDWARE)
	{
		/* Enable non-hardware trigger */
		MAL::F3C::DAC.CR.B.TEN1 = 1U;

		if (trigger == Trigger::TIMER7)
		{
			/* Select timer 7 event for output trigger */
			MAL::F3C::DAC.CR.B.TSEL1 = 2U;
		}
		else if (trigger == Trigger::SOFTWARE)
		{
			MAL::F3C::DAC.CR.B.TSEL1 = 7U;
		}
	}

	inDualMode = dualMode;
	if (inDualMode)
	{
		//TODO Support dual mode
	}

	if (use12Bits)
	{
		bits12 = true;
		bitModeMask = 0xFFFU;
	}
	else
	{
		bits12 = false;
		bitModeMask = 0xFFU;
	}
}

namespace SINGLE
{

void enable()
{
	MAL::F3C::DAC.CR.B.EN1 = 1U;
}

void disable()
{
	MAL::F3C::DAC.CR.B.EN1 = 0U;
}

/* This also triggers the DAC if hardware triggering is set */
void setData(uint16_t data)
{
	/* Don't overrun, those bits are reserved! */
	data = data & bitModeMask;

	if (bits12)
	{
		MAL::F3C::DAC.DHR12R1.B.DACC1DHR = data;
	}
	else
	{
		MAL::F3C::DAC.DHR8R1.B.DACC1DHR = data;
	}
}

void startDMA(uint16_t* sourceBuffer, uint16_t count)
{
	usingDMA = true;

	if (bits12)
	{
		DMA::configureSource(DMA::Source::DAC1_CH1, sourceBuffer, &MAL::F3C::DAC.DHR12R1);
	}
	else
	{
		DMA::configureSource(DMA::Source::DAC1_CH1, sourceBuffer, &MAL::F3C::DAC.DHR8R1);
	}

	DMA::enableSource(DMA::Source::DAC1_CH1, count);

	MAL::F3C::DAC.CR.B.DMA_EN1 = 1U;
}

void swTrigger()
{
	MAL::F3C::DAC.SWTRIGR.B.SWTRIG1 = 1U;
}

}

namespace DUAL
{

void enable(bool enable)
{
	MAL::F3C::DAC.CR.B.EN2 = 1U;
}

void setData(uint32_t data)
{
}

void activateDMA()
{
}

}

}
}
