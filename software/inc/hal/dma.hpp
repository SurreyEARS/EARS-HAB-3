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

	DMA_CH_ERROR,
};

enum class Source {
	ADC1,
	SPI1_RX,
	SPI1_TX,
	UART1_TX,
	UART1_RX,
	I2C1_TX,
	I2C1_RX,

	MEM2MEM8,
	MEM2MEM32,
	DAC1_CH1
};

/* Configure a channel to take data from dataSource and service src */
void configureSource(Source src, void* memory);

/* Configure a channel to take data from dataSource and service src - with custom destination */
void configureSource(Source src, void* memory, volatile void* peripheral);

/* Enable the channel servicing a DMA Source */
void enableSource(Source src, uint32_t count);

/* Begin a memory-to-memory transfer from source to dest.
 * Specify MEM2MEM8 or MEM2MEM32 to choose transfer size */
void startM2M(Source type, void* source, void* destination, uint32_t count);

}
}
