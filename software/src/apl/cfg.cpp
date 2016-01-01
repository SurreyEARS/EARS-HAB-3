/*
 * cgm_data.cpp
 *
 *  Created on: Dec 24, 2015
 *      Author: James
 */
#include <apl/cfg.hpp>

/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 * DO NOT AUTO-FORMAT THIS FILE
 * !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/

namespace APL
{
namespace CFG
{

const ASL::CGM::InitStruct _cfgdata initLib =
{
	HAL::CRC::InitStruct {
		{
			{ HAL::CRC::DefaultPolynomial::CRC16_CCITT, 0x1021U, 0xFFFFU, HAL::CRC::PolynomialSize::BITS_16},
			{ HAL::CRC::DefaultPolynomial::CRC32C, 0x1EDC6F41U, 0xFFFFFFFFU, HAL::CRC::PolynomialSize::BITS_32}
		}
	},

	HAL::DMA::InitStruct {
		{
			/* DMA1 Initialisation */
			{ HAL::DMA::Source::ADC1, HAL::DMA::Channel::DMA1_CH1, 0, ((volatile void*) 0) },
			{ HAL::DMA::Source::SPI1_RX, HAL::DMA::Channel::DMA1_CH2, 0, ((volatile void*) 0) },
			{ HAL::DMA::Source::SPI1_TX, HAL::DMA::Channel::DMA1_CH3, 0, ((volatile void*) 0) },
			{ HAL::DMA::Source::UART1_TX, HAL::DMA::Channel::DMA1_CH4, 0, ((volatile void*) 0) },
			{ HAL::DMA::Source::UART1_RX, HAL::DMA::Channel::DMA1_CH5, 0, ((volatile void*) 0) },
			{ HAL::DMA::Source::I2C1_TX, HAL::DMA::Channel::DMA1_CH6, 0, ((volatile void*) 0) },
			{ HAL::DMA::Source::I2C1_RX, HAL::DMA::Channel::DMA1_CH7, 0, ((volatile void*) 0) },
			/* DMA2 Initialisation */
			/* Not enabled, TCI, TEI, reverse direction, increment both, size 8 bits, medium priority, MEM2MEM */
			{ HAL::DMA::Source::MEM2MEM8, HAL::DMA::Channel::DMA2_CH1, 0x50DA, ((volatile void*) 0) },
			/* Not enabled, TCI, TEI, reverse direction, increment both, size 32 bits, medium priority, MEM2MEM */
			{ HAL::DMA::Source::MEM2MEM32, HAL::DMA::Channel::DMA2_CH2, 0x5ADA, ((volatile void*) 0) },
			/* Not enabled, TCI, TEI, from memory, not circ, incr mem, size 16, med priority */
			{ HAL::DMA::Source::DAC1_CH1, HAL::DMA::Channel::DMA2_CH3, 0x159A, ((volatile void*) 0) }
		}
	},

	HAL::GIO::InitStruct {
		// PORT A  PORT B  PORT C  PORT D  PORT E  PORT F
		{ 0xA80001C0, 0x00000280, 0x00000000, 0x00000000, 0x55550000, 0x00000000 }, // MODER
		{ 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 }, // OTYPER
		{ 0xC00003C0, 0x000000C0, 0x00000000, 0x00000000, 0xFFFF0000, 0x00000000 }, // OSPEEDR
		{ 0x64000002, 0x00000100, 0x00000000, 0x00000000, 0x55550000, 0x00000000 }, // PUPDR
		{ 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 }, // ODR
		{ 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000 }, // AFLR
		{ 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000 }, // AFHR
	},
};


}
}

