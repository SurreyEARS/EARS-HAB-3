/*
 * dma.hpp
 *
 *  Created on: Nov 21, 2015
 *      Author: James
 */

#pragma once

#include <hal/generics.hpp>

namespace HAL {
namespace DMA {

/* Current channel allocations:
 * DMA1_CH1: ADC1
 * DMA1_CH2: SPI1_RX
 * DMA1_CH3:
 * DMA1_CH7: Memory to Memory
 */

enum class Channel {
	DMA1_CH1, // ADC1
	DMA1_CH2, // SPI1_RX
	DMA1_CH3, // SPI1_TX
	DMA1_CH4, // UART1_TX
	DMA1_CH5, // UART1_RX
	DMA1_CH6, // I2C1_TX
	DMA1_CH7, // I2C1_RX

	DMA2_CH1, // MEM2MEM - primary
	DMA2_CH2, // MEM2MEM - secondary
	DMA2_CH3,
	DMA2_CH4,
	DMA2_CH5,

	DMA_CH_ERROR, // Returned if MEM2MEM channel cannot be allocated.
};

void init();

/* Configured to flash bytes for maximum granularity. startM2M_32 is a word-aligned version. */
Channel startM2M (void* source, void* destination, uint32_t numBytes);
Channel startM2M_32 (void* source, void* destination, uint32_t numBytes);

}
}
