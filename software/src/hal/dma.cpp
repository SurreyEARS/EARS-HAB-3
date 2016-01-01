/**
 * \brief Data Movement Engine
 *
 * Provides access to the DMA channels. Primarily used for configuration
 * as it is assumed most DMA requests are hardware-triggered. Also provides
 * memory-to-memory transfers
 *
 * \date Created on: Nov 21, 2015
 * \author James Telfer
 */

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * 1 INCLUDES
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* This file's header: */
#include <hal/dma.hpp>
/* APL/ASL/HAL files, sorted alphabetically */
#include <apl/ssm.hpp>
/* MAL, EXT and standard library files */
#include <mal/device.hpp>
#include <cstring>

namespace HAL
{
namespace DMA
{

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * 2 CONSTANTS AND DEFINED DATA
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Filled in by CGM. */
static InitStruct config;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * 3 INTERNAL CLASSES, STRUCTS, TYPEDEFS, DEFINES
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Helper function to turn a Channel enum value into a DMA_CHANNEL_t&, and typedef to match */
#define GET_CHAN(chan) (*MAL::F3C::DMA_CHANNELS[uint32_t(chan)])
typedef volatile MAL::F3C::DMA_CHANNEL_t& ChannelRef;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * 4 INTERNAL FUNCTION PROTOTYPES
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
static void configChan(Channel channel, uint32_t config, void* mem, volatile void* per);
static void startChan(Channel chan, uint32_t count);
static bool isChanFree(Channel chan);
static const ChannelDefinition& getSourceConfiguration(Source src);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * 5 MODULE FUNCTIONS
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
 * 6 OPERATIONAL FUNCTIONS
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void configure(const InitStruct& cfg)
{
	memcpy(&config, &cfg, sizeof(InitStruct));
}

bool test()
{
	uint32_t dataSource = 0xDEADBEEF;
	uint32_t dataSink = 0x0;
	startM2M(Source::MEM2MEM32, &dataSource, &dataSink, 1);
	return (dataSource == dataSink);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * 7 INTERNAL FUNCTIONS
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

static const ChannelDefinition& getSourceConfiguration(Source src)
{
	const ChannelDefinition& cfg = config.channelDefs[int(src)];

	if ((cfg.src != src) || (Channel::DMA_CH_ERROR == cfg.ch) || !isChanFree(cfg.ch))
	{
		APL::SSM::raiseCondition(APL::SSM::Fault::PROCESSOR_INIT);
	}

	return cfg;
}

}
}
