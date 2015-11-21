/*
 * dma.hpp
 *
 *  Created on: Nov 21, 2015
 *      Author: James
 */

#pragma once

#include <HAL/generics.hpp>

namespace HAL {
namespace DMA {

enum class Channel {
	DMA1_CH1,
	DMA1_CH2,
	DMA1_CH3,
	DMA1_CH4,
	DMA1_CH5,
	DMA1_CH6,
	DMA1_CH7,

	DMA2_CH1,
	DMA2_CH2,
	DMA2_CH3,
	DMA2_CH4,
	DMA2_CH5,
};

Channel configureMemMem (void* source, void* destination, uint32_t numBytes);


}
}
