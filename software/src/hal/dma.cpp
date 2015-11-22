/*
 * dma.cpp
 *
 *  Created on: Nov 21, 2015
 *      Author: James
 */

#include <hal/dma.hpp>
#include <mal/stm32f303vc.hpp>

namespace HAL
{
namespace DMA
{

/* Channel assignments */
const Channel memToMemPrimary = Channel::DMA2_CH1;
const Channel memToMemSecondary = Channel::DMA2_CH2;

/* Not enabled, TCI, TEI, reverse direction, increment both, size 8/32 bits, medium priority, MEM2MEM */
static const volatile uint32_t memToMemConfigControl8 = 0b101000011011010;
static const volatile uint32_t memToMemConfigControl32 = 0b101101011011010;

/* Helper function to turn a Channel enum value into a DMA_CHANNEL_t&, and typedef to match */
#define GET_CHAN(chan) (*MAL::F3C::DMA_CHANNELS[uint32_t(chan)])
typedef volatile MAL::F3C::DMA_CHANNEL_t& ChannelRef;

/* MODULE INTERNAL FUNCTIONS */

static void start(ChannelRef ch, void* source, void* destination, uint32_t cndtr)
{
	ch.CMAR = (v32t) source;
	ch.CPAR = (v32t) destination;
	ch.CNDTR.B.NDT = cndtr;

	ch.CCR.B.EN = 1U;
}

static Channel getClearM2MChannel()
{
	Channel selected = memToMemPrimary;
	auto& chan_p = GET_CHAN(memToMemPrimary);

	if (chan_p.CNDTR.R != 0U)
	{
		/* If the primary channel is currently transferring, try the secondary.
		 * Note that "number of bytes left" is the best way of detecting a
		 * DMA channel activity - the EN bit is not hardware cleared.
		 */
		auto& chan_s = GET_CHAN(memToMemPrimary);
		selected = memToMemSecondary;

		if (chan_s.CNDTR.R != 0U)
		{
			//TODO: Replace this with a queue of requests.
			// Non-critical as we're unlikely to fully utilise two M2M channels on HAB3
			selected = Channel::DMA_CH_ERROR;
		}
	}

	return selected;
}

Channel startM2M(void* source, void* destination, uint32_t numBytes)
{
	Channel selected = getClearM2MChannel();
	auto& chan = GET_CHAN(selected);

	if (Channel::DMA_CH_ERROR != selected)
	{
		chan.CCR.R = memToMemConfigControl8;
		start(chan, source, destination, numBytes);
	}

	return selected;
}

Channel startM2M_32(void* source, void* destination, uint32_t numWords)
{
	Channel selected = getClearM2MChannel();
	auto& chan = GET_CHAN(selected);

	if (Channel::DMA_CH_ERROR != selected)
	{
		chan.CCR.R = memToMemConfigControl32;
		start(chan, source, destination, numWords);
	}

	return selected;
}

}
}
