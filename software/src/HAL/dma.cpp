/*
 * dma.cpp
 *
 *  Created on: Nov 21, 2015
 *      Author: James
 */

#include <HAL/dma.hpp>

#include <MAL/stm32f303vc.hpp>

namespace HAL {
namespace DMA {

const Channel memToMemChannel = Channel::DMA1_CH7;

Channel configureMemMem (void* source, void* destination, uint32_t numBytes)
{
	volatile MAL::F3C::DMA_CHANNEL_t& chan = *MAL::F3C::DMA_CHANNELS[uint32_t(memToMemChannel)];

	chan.CMAR = (v32t)source;
	chan.CPAR = (v32t)destination;
	chan.CNDTR.B.NDT = numBytes;

	chan.CCR.B.MEM2MEM = 1U;
	chan.CCR.B.MINC = 1U;
	chan.CCR.B.PINC = 1U;
	chan.CCR.B.TCIE = 1U;
	chan.CCR.B.DIR = 1U;

	chan.CCR.B.EN = 1U;

	return memToMemChannel;
}

}
}
