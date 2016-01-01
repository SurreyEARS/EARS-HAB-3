/*
 * ssm.cpp
 *
 *  Created on: Dec 22, 2015
 *      Author: James
 */

#include <apl/ssm.hpp>
#include <hal/gio.hpp>

namespace APL
{
namespace SSM
{

static SafetyErrorFlags safetyFlags;
static State currentState;

constexpr const static HAL::GIO::Port hotStartPort = HAL::GIO::Port::PORTA;
constexpr const static uint32_t hotStartPin = 0;

constexpr const static HAL::GIO::Port faultPort = HAL::GIO::Port::PORTE;
constexpr const static uint32_t faultPin = 9;

void init()
{
	currentState = State::INIT;

	safetyFlags.overallCondition = 0x0U;
	safetyFlags.flags.processorInit = 1U;
	safetyFlags.flags.watchdog = 1U;
}

State getState()
{
	return currentState;
}

const SafetyErrorFlags& getSafetyCondition()
{
	return safetyFlags;
}

void clearCondition(Fault fault)
{
	switch (fault)
	{
	case Fault::PROCESSOR_INIT:
		safetyFlags.flags.processorInit = 0;
		break;
	case Fault::SOFTWARE_FAILURE:
		safetyFlags.flags.softwareFailure = 0;
		break;
	case Fault::HARDWARE_FAILURE:
		safetyFlags.flags.hardwareFailure = 0;
		break;
	case Fault::TIMEOUT:
		safetyFlags.flags.timeout = 0;
		break;
	case Fault::WATCHDOG:
		safetyFlags.flags.watchdog = 0;
		break;
	case Fault::ERROR_UNKNOWN:
		safetyFlags.flags.errorUnknown = 0;
		break;
	}

	reviewState();
}

void raiseCondition(Fault fault)
{
	switch (fault)
	{
	case Fault::PROCESSOR_INIT:
		safetyFlags.flags.processorInit = 1;
		break;
	case Fault::SOFTWARE_FAILURE:
		safetyFlags.flags.softwareFailure = 1;
		break;
	case Fault::HARDWARE_FAILURE:
		safetyFlags.flags.hardwareFailure = 1;
		break;
	case Fault::TIMEOUT:
		safetyFlags.flags.timeout = 1;
		break;
	case Fault::WATCHDOG:
		safetyFlags.flags.watchdog = 1;
		break;
	case Fault::ERROR_UNKNOWN:
		safetyFlags.flags.errorUnknown = 1;
		break;
	}

	reviewState();
}

void reviewState()
{
	if (0 != safetyFlags.overallCondition)
	{
		set(faultPort, faultPin);
	}
	else
	{
		reset(faultPort, faultPin);
	}
}

State checkHotStart()
{
	if (0U == HAL::GIO::get(hotStartPort, hotStartPin))
	{
		currentState = State::COLD_START;
	}
	else
	{
		currentState = State::HOT_START;
	}

	reviewState();
	return currentState;
}

}
}
