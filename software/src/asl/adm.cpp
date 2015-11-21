/*
 * adm.cpp
 *
 *  Created on: Nov 20, 2015
 *      Author: James
 */

#include <hal/generics.hpp>
#include <asl/adm.hpp>

namespace ASL {
namespace ADM {

Channel::Channel (ADCNum module, uint32_t channel)
	: module (module), channel (channel)
{ }

void Channel::configure (Operation op, uint32_t multiplier, int32_t constant)
{

}

Operation Channel::getOperation()
{
	return op;
}

uint32_t Channel::getMultiplier()
{
	return multiplier;
}

int32_t Channel::getConstant()
{
	return constant;
}

void Channel::setEnable (bool enable)
{
	enabled = enable;
}

bool Channel::getEnable ()
{
	return enabled;
}

uint32_t Channel::getValue()
{
	return value;
}

void setSample(Channel& ch, uint32_t newRaw)
{

}

void configureModule()
{

}

Channel& getChannelRef (uint32_t module, uint32_t channel)
{

}

}
}
