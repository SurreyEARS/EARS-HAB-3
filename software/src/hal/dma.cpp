/*
 * dma.cpp
 *
 *  Created on: Nov 21, 2015
 *      Author: James
 */

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * INCLUDED FILES
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include <hal/dma.hpp>
#include <mal/stm32f303vc.hpp>

namespace HAL
{
namespace DMA
{

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * INTERNAL CLASSES, STRUCTS, TYPEDEFS
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

struct DMA_Init_t
{
	Source src;
	Channel ch;
	uint32_t config;
	volatile void* per;
};

/* Helper function to turn a Channel enum value into a DMA_CHANNEL_t&, and typedef to match */
#define GET_CHAN(chan) (*MAL::F3C::DMA_CHANNELS[uint32_t(chan)])
typedef volatile MAL::F3C::DMA_CHANNEL_t& ChannelRef;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * CONSTANTS AND DEFINED DATA
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/* Not enabled, TCI, TEI, reverse direction, increment both, size 8/32 bits, medium priority, MEM2MEM */
static const volatile uint32_t memToMemConfigControl8 = 0b101000011011010;
static const volatile uint32_t memToMemConfigControl32 = 0b101101011011010;

/* Not enabled, TCI, TEI, from memory, not circ, incr mem, size 16, med priority */
static const volatile uint32_t dacConfigControl = 0b1010110011010;

/* This list is indexed by Source and depends on the order it is defined.
 * It will throw an error (TODO) if the wrong source is defined in the struct */
static const DMA_Init_t config[] =
{
/* DMA1 Initialisation */
{ Source::ADC1, Channel::DMA1_CH1, 0, ((volatile void*) 0) },
{ Source::SPI1_RX, Channel::DMA1_CH2, 0, ((volatile void*) 0) },
{ Source::SPI1_TX, Channel::DMA1_CH3, 0, ((volatile void*) 0) },
{ Source::UART1_TX, Channel::DMA1_CH4, 0, ((volatile void*) 0) },
{ Source::UART1_RX, Channel::DMA1_CH5, 0, ((volatile void*) 0) },
{ Source::I2C1_TX, Channel::DMA1_CH6, 0, ((volatile void*) 0) },
{ Source::I2C1_RX, Channel::DMA1_CH7, 0, ((volatile void*) 0) },
/* DMA2 Initialisation */
{ Source::MEM2MEM8, Channel::DMA2_CH1, memToMemConfigControl8, ((volatile void*) 0) },
{ Source::MEM2MEM32, Channel::DMA2_CH2, memToMemConfigControl32, ((volatile void*) 0) },
{ Source::DAC1_CH1, Channel::DMA2_CH3, dacConfigControl, ((volatile void*) 0) }, };

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * INTERNAL FUNCTION PROTOTYPES
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void configChan(Channel channel, uint32_t config, void* mem, volatile void* per);
static void startChan(Channel chan, uint32_t count);
static bool isChanFree(Channel chan);
static const DMA_Init_t& getSourceConfiguration(Source src);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * EXTERNAL FUNCTIONS
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void configureSource(Source src, void* mem)
{
	auto& cfg = getSourceConfiguration(src);
	configChan(cfg.ch, cfg.config, mem, cfg.per);
}

void configureSource(Source src, void* mem, volatile void* per)
{
	auto& cfg = getSourceConfiguration(src);
	configChan(cfg.ch, cfg.config, mem, per);
}

void enableSource(Source src, uint32_t count)
{
	auto& cfg = getSourceConfiguration(src);
	startChan(cfg.ch, count);
}

void startM2M(Source type, void* source, void* dest, uint32_t count)
{
	auto& m2mx = getSourceConfiguration(type);
	configChan(m2mx.ch, m2mx.config, source, dest);
	startChan(m2mx.ch, count);
}


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * INTERNAL FUNCTIONS
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void configChan(Channel channel, uint32_t config, void* mem, volatile void* per)
{
	auto& ch = GET_CHAN(channel);
	ch.CCR.B.EN = 0U;

	ch.CCR.R = config;
	ch.CMAR = (v32t) mem;
	ch.CPAR = (v32t) per;
}

static void startChan(Channel chan, uint32_t count)
{
	auto& ch = GET_CHAN(chan);
	ch.CCR.B.EN = 0U;

	ch.CNDTR.B.NDT = count;
	ch.CCR.B.EN = 1U;
}

static bool isChanFree(Channel chan)
{
	return 0U == GET_CHAN(chan).CNDTR.R;
}

static const DMA_Init_t& getSourceConfiguration(Source src)
{
	const DMA_Init_t& cfg = config[int(src)];

	if ((cfg.src != src) || (Channel::DMA_CH_ERROR == cfg.ch) || !isChanFree(cfg.ch))
	{
		// TODO Add useful fault handling to MCU
		while (1)
			;
	}

	return cfg;
}

}
}
