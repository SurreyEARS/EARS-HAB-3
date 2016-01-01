/*
 * ssm.hpp
 *
 *  Created on: Dec 22, 2015
 *      Author: James
 */

#pragma once

#include <hal/generics.hpp>

namespace APL
{
namespace SSM
{

enum class State
{
	INIT, COLD_START, HOT_START, RUN
};

enum class Fault
{
	PROCESSOR_INIT, SOFTWARE_FAILURE, HARDWARE_FAILURE, TIMEOUT, WATCHDOG,

	ERROR_UNKNOWN
};

union SafetyErrorFlags
{
	struct
	{
		uint32_t processorInit :1;
		uint32_t softwareFailure :1;
		uint32_t hardwareFailure :1;
		uint32_t timeout :1;
		uint32_t watchdog :1;

		uint32_t errorUnknown :1;
	} flags;

	uint32_t overallCondition;
};

void init();

State getState();
void reviewState();

State checkHotStart();

const SafetyErrorFlags& getSafetyCondition();
void raiseCondition(Fault fault);
void clearCondition(Fault fault);

}
}
